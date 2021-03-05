#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_hackrf_controller.h"
using namespace std;

void MainWindow::showSpecData(float *xData, float *yData, int size, int garmonicId)
{
    double       begTime     = 0;
    double       endTime     = 20;
    for(int i=0; i<size; i++)
        sono.enqueue(yData[i]);

    if(!tuner_state->isNeedToExit && ui->chb_spec_enable->isChecked())
    {
        //        ui->widAmlSpecTop->plot->showData32f_2os(xData, yData, size, blueFilled);
        /*if(time.elapsed() >= 150 && !admin_enable)
        {
            QByteArray data;
            data.resize(sizeof(float)*size);
            memcpy(data.data(), yData, size*sizeof(float));
           if(TCPclient.isOpen())
                TCPclient.sendToServer(data, 13);
            time.restart();
        }*/
        /*else if(admin_enable)
        {
            widAmlSpecTopClients->plot->showData32f_2os(xData, clientSpecData, size, blueFilled);
        }*/


        //        ui->widSonogramBottom->plot->setSpectrogramParams(tuner_state->fftSize, xData[0], xData[size-1],
        //                begTime, endTime, false);

        QQueue<double>::iterator i;
        int j;
        for(i = sono.begin(),  j = 0; i!= sono.end() && j < sonoWindow; i++, j++)
        {
            //            ui->widSonogramBottom->plot->specData->matrix[j] = *i;
        }
        //        ui->widSonogramBottom->plot->replot();
        while(sono.size() >= sonoWindow+size)
        {
            for(int i=0; i<size; i++)
                sono.dequeue();
        }
    }
}

void MainWindow::create_plot()
{
    qDebug()<<"(create_plot())";
    spectrogram = new QwtPlotSpectrogram();
    spectrogram->testDisplayMode(QwtPlotSpectrogram::ImageMode);
    spectrogram->show();
    //ui->layout_graph->addWidget(spectrogram);
    //    ui->widAmlSpecTop->plot->installPlot(false);
    //    ui->widAmlSpecTop->setMeasurePanelVisible(false);
    //    ui->widAmlSpecTop->setDataTimeEditsVisible(false);

    //    ui->widSonogramBottom->plot->installPlot(true);
    //    ui->widSonogramBottom->setMeasurePanelVisible(false);
    //    ui->widSonogramBottom->setDataTimeEditsVisible(false);

    //    QFont font;
    //    font.setPointSize(9);
    //    QwtText text;
    //    text.setFont(font);  // font with desired size, etc.

    //    text.setText("дБ В/Гц");
    //    ui->widAmlSpecTop->plot->setAxisTitle(QwtPlot::yLeft, text);
    //    text.setText("Частота, МГц");
    //    ui->widAmlSpecTop->plot->setAxisTitle(QwtPlot::xBottom, text);

    //    text.setText("Время, с");
    //    ui->widSonogramBottom->plot->setAxisTitle(QwtPlot::yLeft, text);
    //    text.setText("Частота, МГц");
    //    ui->widSonogramBottom->plot->setAxisTitle(QwtPlot::xBottom, text);

    //    text.setText("Панорамный амплитудный спектр");
    //    ui->widAmlSpecTop->plot->setTitle(text);
    //    text.setText("Спектрограмма");
    //    ui->widSonogramBottom->plot->setTitle(text);

    //    ui->widSonogramBottom->plot->specData->matrix.resize(sonoWindow);
}
