#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_hackrf_controller.h"
using namespace std;

void MainWindow::write_settings()
{
    st->setValue("CentFreq", centFreqEdit->getNumber());
    st->setValue("AccumCnt", ui->cb_accum_spec->currentText());
    st->setValue("ShowSpecBool", ui->chb_spec_enable->isChecked());
    //st->setValue("AutoGainMode", ui->chb_auto_gain_mode->isChecked());
    st->setValue("AccumSono", ui->spb_accum_sono->value());
    //    st->setValue("GainLevel", ui->cb_gain->currentText());
    st->setValue("fftsize", ui->cb_fftsize->currentText());
    //    st->setValue("BufferSize", ui->cb_buffer_size->currentText());
    st->setValue("LogSpec", ui->chb_log_spec->isChecked());
    st->setValue("IP", IP);
    st->setValue("port", port);
    st->setValue("ActLocalState", ui->act_local_host->isChecked());
    st->setValue("ActSetIpEnabled", ui->act_set_ip->isEnabled());
    st->setValue("IsFirstLaunch", false);
    //    st->setValue("SampleRate", ui->cb_sample_rate->currentText());
}

void MainWindow::read_settings()
{
    if(st->value("IsFirstLaunch",true).toBool())
        st->clear();

    centFreqEdit->setNumber(st->value("CentFreq", 100000000).toInt());
    ui->cb_accum_spec->setCurrentText(st->value("AccumCnt", "96").toString());
    ui->chb_spec_enable->setChecked(st->value("ShowSpecBool", true).toBool());
    //    ui->chb_auto_gain_mode->setChecked(st->value("AutoGainMode", false).toBool());
    ui->spb_accum_sono->setValue(st->value("AccumSono", 75).toInt());
    //    ui->cb_gain->setCurrentText(st->value("GainLevel", "434").toString());
    ui->cb_fftsize->setCurrentText(st->value("fftsize", "2048").toString());
    //    ui->cb_buffer_size->setCurrentText(st->value("BufferSize", "4096").toString());
    ui->chb_log_spec->setChecked(st->value("LogSpec", true).toBool());
    IP=st->value("IP","188.242.15.139").toString();
    port=st->value("port","8080").toString();
    ui->act_local_host->setChecked(st->value("ActLocalState", false).toBool());
    ui->act_set_ip->setEnabled(st->value("ActSetIpEnabled", true).toBool());
    //ui->cb_sample_rate->setCurrentText(st->value("SampleRate", "3200000").toString());

    tuner_state->centFreq = st->value("CentFreq", 100000000).toInt();
    tuner_state->accumCnt = st->value("AccumCnt", "96").toInt();
    //tuner_state->agcMode = st->value("AutoGainMode", false).toBool();
    tuner_state->accumSono = st->value("AccumSono", 75).toInt();
    tuner_state->gainLevel = st->value("GainLevel", "434").toInt();
    tuner_state->fftSize = st->value("fftsize", "2048").toInt();
    tuner_state->adcBufSize = st->value("BufferSize", "4096").toInt();
    tuner_state->LogSpec = st->value("LogSpec", true).toBool();
    tuner_state->sampleRate = st->value("SampleRate", "3200000").toInt();
}
