#ifndef HACKRF_CONTROLLER_H
#define HACKRF_CONTROLLER_H

#include <QWidget>

namespace Ui {
class HackRF_Controller;
}

class HackRF_Controller : public QWidget
{
    Q_OBJECT

public:
    explicit HackRF_Controller(QWidget *parent = nullptr);
    ~HackRF_Controller();

    void addItemToSampleRateList(double val);
    double getSampleRateCurrentVal();
    int getLnaGainCurrentVal();
    int getVgaGainCurrentVal();
    int getAmpCurStatus();

    Ui::HackRF_Controller *ui;

signals:
    void lna_gain_changed(int);
    void vga_gain_changed(int);
    void sampleRate_changed(double);
    void amp_gain_stateChanged(bool);

private slots:
    void on_pb_close_clicked();
    void on_lna_gain_valueChanged(int value);
    void on_vga_gain_valueChanged(int value);
    void on_cb_amp_gain_stateChanged(int arg1);
    void on_cb_sampleRate_currentTextChanged(const QString &arg1);
};

#endif // HACKRF_CONTROLLER_H
