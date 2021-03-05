#include "hackrf_controller.h"
#include "ui_hackrf_controller.h"
#include "QDebug"

HackRF_Controller::HackRF_Controller(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HackRF_Controller)
{
    ui->setupUi(this);
    setWindowTitle("HackRF settings");
    setEnabled(false);
}

HackRF_Controller::~HackRF_Controller()
{
    delete ui;
}

void HackRF_Controller::addItemToSampleRateList(double val)
{
    ui->cb_sampleRate->addItem(QString::number(val/1000000)+" МГц");
}

double HackRF_Controller::getSampleRateCurrentVal()
{
    QString str = ui->cb_sampleRate->currentText();
    return str.split(" ")[0].toDouble()*1000000;
}

int HackRF_Controller::getLnaGainCurrentVal()
{
    return ui->lna_gain->value();
}

int HackRF_Controller::getVgaGainCurrentVal()
{
    return ui->vga_gain->value();
}

int HackRF_Controller::getAmpCurStatus()
{
    return ui->cb_amp_gain->isChecked();
}

void HackRF_Controller::on_pb_close_clicked()
{
    hide();
}

void HackRF_Controller::on_lna_gain_valueChanged(int value)
{
    emit lna_gain_changed(value);
}

void HackRF_Controller::on_vga_gain_valueChanged(int value)
{
    emit vga_gain_changed(value);
}

void HackRF_Controller::on_cb_amp_gain_stateChanged(int arg1)
{
    emit amp_gain_stateChanged((bool)arg1);
}

void HackRF_Controller::on_cb_sampleRate_currentTextChanged(const QString &arg1)
{
    emit sampleRate_changed(double(arg1.split(" ")[0].toDouble()*1000000));
}
