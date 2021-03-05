#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_hackrf_controller.h"
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("GBN SDR");
    tuner_state = new Tuner_state;
    circBuffer = new CircBuffer<char>;

    centFreqEdit = new SpinWidget(this);
    ui->freq_layout->addWidget(centFreqEdit);

    st = App::theApp()->settings();

    bar_buf_fullness = new QProgressBar();
    bar_buf_fullness->setMaximumWidth(220);
    lb_buf_fullness = new QLabel("Заполнение буфера");
    msg_status_bar = new QLabel();
    ui->statusBar->addWidget(lb_buf_fullness);
    ui->statusBar->addWidget(bar_buf_fullness);
    ui->statusBar->addWidget(msg_status_bar);

    //Добавление иконок в панель инструментов
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(QPixmap("resource/connect_sdr.png"), "Подключение приемника", this, SLOT(pb_open_tuner_clicked()));
    ui->mainToolBar->addAction(QPixmap("resource/settings.png"), "Настройки приемника",this, SLOT(open_settings_window()));
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(QPixmap("resource/play.png"), "Начать запись", this, SLOT(pb_start_clicked()));
    ui->mainToolBar->addAction(QPixmap("resource/stop.png"), "Остановить запись", this, SLOT(pb_stop_clicked()));
    ui->mainToolBar->addAction(QPixmap("resource/link.png"), "Установить параметры сети", this, SLOT(set_network_ts()));
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(QPixmap("resource/download.png"), "Получить записи сигналов", this, SLOT(get_signals()));
    ui->mainToolBar->setIconSize(QSize(33, 33));
    ui->mainToolBar->setMovable(false);

    tmr = new QTimer();
    connect(tmr, SIGNAL(timeout()), this, SLOT(refreshProg()));
    tmr_2 = new QTimer();
    connect(tmr_2, SIGNAL(timeout()), this, SLOT(set_send_progress()));

    ui->le_msg->setPlaceholderText("Введите сообщение");

    pprd_rec = new QProgressDialog(" ", "&Отмена", 0, 100, this);
    pprd_rec->setMinimumDuration(1);
    pprd_rec->setWindowTitle("Получение файлов");

    pprd_send = new QProgressDialog("Прогресс отправки", "&Отмена", 0, 100, this);
    pprd_send->setMinimumDuration(1);
    pprd_send->setWindowTitle("Отправление сигнала");
    pprd_rec->close();
    pprd_send->close();
    //st->clear(); //Если не запускается, нужно стерень настройки
    read_settings();
    init_sdr();
    openTuner();
    create_plot();
    create_sig_file();

    thread_proc = new QThread;
    ProcThread = new proc_thread(tuner_state, circBuffer);
    ProcThread->moveToThread(thread_proc);
    connect(thread_proc, SIGNAL(started()), ProcThread, SLOT(run()));
    connect(ProcThread, SIGNAL(finished()), thread_proc, SLOT(terminate()));

    thread_sdr = new QThread;
    SdrThread = new sdr_thread(tuner_state, circBuffer);
    SdrThread->moveToThread(thread_sdr);
    connect(thread_sdr, SIGNAL(started()), SdrThread, SLOT(run()));
    connect(SdrThread, SIGNAL(finished()), thread_sdr, SLOT(terminate()));

    connect(&TCPclient, SIGNAL(error(QAbstractSocket::SocketError)), SLOT(slotError(QAbstractSocket::SocketError)));
    connect(&TCPclient, SIGNAL(connected()), SLOT(show_connect_message()));
    connect(&TCPclient, SIGNAL(dataRecieved(Message)), SLOT(parsing(Message)));
    connect(&TCPclient, SIGNAL(disconnected()),SLOT(discon()));
    connect(&TCPclient, SIGNAL(write_to_file(QByteArray)), SLOT(write_to_file(QByteArray)));
    connect(ui->act_get_signals, SIGNAL(triggered(bool)), SLOT(get_signals()));
    connect(&TCPclient, SIGNAL(finish_recieve()), SLOT(close_file()));
    connect(&TCPclient, SIGNAL(rec_prog(int)), pprd_rec, SLOT(setValue(int)));
}

MainWindow::~MainWindow()
{
    SoapySDR::Device::unmake(tuner_state->device);
    hackrfSetWin.close();
    write_settings();
    delete ui;
}

//парсинг принятого сообщения
void MainWindow::parsing(Message message)
{
    QString str;
    Tuner_state *ts;
    switch(message.command)
    {
    case 2:
        str = QTime::currentTime().toString() + " Server: " + conv.ByteToStr(message.data);
        ui->te_server_info->append(str);
        break;

    case 3:
        str = QTime::currentTime().toString() + " " + conv.ByteToStr(message.data);
        ui->te_server_info->append(str);
        break;

    case 6:
        ts = conv.ByteToTS(message.data);
        set_tuner_state(ts);
        show_StB_msg("Принята команда на установку параметров", 1000);
        break;

        /*case 13:
        memcpy(clientSpecData, message.data, message.data.size());
        widAmlSpecTopClients->plot->showData32f_2os(osx, clientSpecData, 2048, blueFilled);
        break;*/

    case 14:
        openTuner();
        break;

    case 15:
        start_read();
        break;

    case 16:
        stop_read();
        break;

    case 18:
        send_sig();
        break;

    case 19: //установка имени принимаемого файла
        str = QDir::currentPath()+"/Recieved_sig/"+conv.ByteToStr(message.data);
        qDebug()<<sig_file.fileName()<<conv.ByteToStr(message.data);
        if (sig_file.fileName() != conv.ByteToStr(message.data))
            sig_file.setFileName(str);
        if(sig_file.exists())
            sig_file.remove();
        if(!sig_file.isOpen())
        {
            if(!sig_file.open(QIODevice::Append))
                show_StB_msg("Ошибка открытия файла");
        }
        else
            show_StB_msg("Принимаемый файл "+ conv.ByteToStr(message.data) +" создан!");
        pprd_rec->show();
        break;

    default:
        qDebug()<<"Unknown command "<<message.command<<" was recieved";
    }
}
