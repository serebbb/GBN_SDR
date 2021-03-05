/********************************************************************************
** Form generated from reading UI file 'hackrf_controller.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HACKRF_CONTROLLER_H
#define UI_HACKRF_CONTROLLER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HackRF_Controller
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QComboBox *cb_sampleRate;
    QLabel *label_2;
    QSlider *lna_gain;
    QLabel *label_3;
    QSlider *vga_gain;
    QCheckBox *cb_amp_gain;
    QPushButton *pb_close;

    void setupUi(QWidget *HackRF_Controller)
    {
        if (HackRF_Controller->objectName().isEmpty())
            HackRF_Controller->setObjectName(QString::fromUtf8("HackRF_Controller"));
        HackRF_Controller->resize(299, 213);
        verticalLayout = new QVBoxLayout(HackRF_Controller);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(HackRF_Controller);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        cb_sampleRate = new QComboBox(HackRF_Controller);
        cb_sampleRate->addItem(QString());
        cb_sampleRate->addItem(QString());
        cb_sampleRate->addItem(QString());
        cb_sampleRate->addItem(QString());
        cb_sampleRate->addItem(QString());
        cb_sampleRate->addItem(QString());
        cb_sampleRate->addItem(QString());
        cb_sampleRate->addItem(QString());
        cb_sampleRate->addItem(QString());
        cb_sampleRate->addItem(QString());
        cb_sampleRate->addItem(QString());
        cb_sampleRate->addItem(QString());
        cb_sampleRate->addItem(QString());
        cb_sampleRate->addItem(QString());
        cb_sampleRate->addItem(QString());
        cb_sampleRate->addItem(QString());
        cb_sampleRate->addItem(QString());
        cb_sampleRate->addItem(QString());
        cb_sampleRate->addItem(QString());
        cb_sampleRate->addItem(QString());
        cb_sampleRate->setObjectName(QString::fromUtf8("cb_sampleRate"));

        verticalLayout->addWidget(cb_sampleRate);

        label_2 = new QLabel(HackRF_Controller);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        lna_gain = new QSlider(HackRF_Controller);
        lna_gain->setObjectName(QString::fromUtf8("lna_gain"));
        lna_gain->setMaximum(40);
        lna_gain->setSingleStep(8);
        lna_gain->setPageStep(8);
        lna_gain->setValue(24);
        lna_gain->setTracking(true);
        lna_gain->setOrientation(Qt::Horizontal);
        lna_gain->setTickPosition(QSlider::TicksAbove);
        lna_gain->setTickInterval(8);

        verticalLayout->addWidget(lna_gain);

        label_3 = new QLabel(HackRF_Controller);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);

        vga_gain = new QSlider(HackRF_Controller);
        vga_gain->setObjectName(QString::fromUtf8("vga_gain"));
        vga_gain->setMaximum(62);
        vga_gain->setSingleStep(2);
        vga_gain->setPageStep(2);
        vga_gain->setValue(38);
        vga_gain->setOrientation(Qt::Horizontal);
        vga_gain->setTickPosition(QSlider::TicksAbove);
        vga_gain->setTickInterval(2);

        verticalLayout->addWidget(vga_gain);

        cb_amp_gain = new QCheckBox(HackRF_Controller);
        cb_amp_gain->setObjectName(QString::fromUtf8("cb_amp_gain"));

        verticalLayout->addWidget(cb_amp_gain);

        pb_close = new QPushButton(HackRF_Controller);
        pb_close->setObjectName(QString::fromUtf8("pb_close"));

        verticalLayout->addWidget(pb_close);


        retranslateUi(HackRF_Controller);

        cb_sampleRate->setCurrentIndex(10);


        QMetaObject::connectSlotsByName(HackRF_Controller);
    } // setupUi

    void retranslateUi(QWidget *HackRF_Controller)
    {
        HackRF_Controller->setWindowTitle(QCoreApplication::translate("HackRF_Controller", "Form", nullptr));
        label->setText(QCoreApplication::translate("HackRF_Controller", "\320\247\320\260\321\201\321\202\320\276\321\202\320\260 \320\264\320\270\321\201\320\272\321\200\320\265\321\202\320\270\320\267\320\260\321\206\320\270\320\270", nullptr));
        cb_sampleRate->setItemText(0, QCoreApplication::translate("HackRF_Controller", "20 \320\234\320\223\321\206", nullptr));
        cb_sampleRate->setItemText(1, QCoreApplication::translate("HackRF_Controller", "19 \320\234\320\223\321\206", nullptr));
        cb_sampleRate->setItemText(2, QCoreApplication::translate("HackRF_Controller", "18 \320\234\320\223\321\206", nullptr));
        cb_sampleRate->setItemText(3, QCoreApplication::translate("HackRF_Controller", "17 \320\234\320\223\321\206", nullptr));
        cb_sampleRate->setItemText(4, QCoreApplication::translate("HackRF_Controller", "16 \320\234\320\223\321\206", nullptr));
        cb_sampleRate->setItemText(5, QCoreApplication::translate("HackRF_Controller", "15 \320\234\320\223\321\206", nullptr));
        cb_sampleRate->setItemText(6, QCoreApplication::translate("HackRF_Controller", "14 \320\234\320\223\321\206", nullptr));
        cb_sampleRate->setItemText(7, QCoreApplication::translate("HackRF_Controller", "13 \320\234\320\223\321\206", nullptr));
        cb_sampleRate->setItemText(8, QCoreApplication::translate("HackRF_Controller", "12 \320\234\320\223\321\206", nullptr));
        cb_sampleRate->setItemText(9, QCoreApplication::translate("HackRF_Controller", "11 \320\234\320\223\321\206", nullptr));
        cb_sampleRate->setItemText(10, QCoreApplication::translate("HackRF_Controller", "10 \320\234\320\223\321\206", nullptr));
        cb_sampleRate->setItemText(11, QCoreApplication::translate("HackRF_Controller", "9 \320\234\320\223\321\206", nullptr));
        cb_sampleRate->setItemText(12, QCoreApplication::translate("HackRF_Controller", "8 \320\234\320\223\321\206", nullptr));
        cb_sampleRate->setItemText(13, QCoreApplication::translate("HackRF_Controller", "7 \320\234\320\223\321\206", nullptr));
        cb_sampleRate->setItemText(14, QCoreApplication::translate("HackRF_Controller", "6 \320\234\320\223\321\206", nullptr));
        cb_sampleRate->setItemText(15, QCoreApplication::translate("HackRF_Controller", "5 \320\234\320\223\321\206", nullptr));
        cb_sampleRate->setItemText(16, QCoreApplication::translate("HackRF_Controller", "4 \320\234\320\223\321\206", nullptr));
        cb_sampleRate->setItemText(17, QCoreApplication::translate("HackRF_Controller", "3 \320\234\320\223\321\206", nullptr));
        cb_sampleRate->setItemText(18, QCoreApplication::translate("HackRF_Controller", "2 \320\234\320\223\321\206", nullptr));
        cb_sampleRate->setItemText(19, QCoreApplication::translate("HackRF_Controller", "1 \320\234\320\263\321\206", nullptr));

        label_2->setText(QCoreApplication::translate("HackRF_Controller", "\320\234\320\250\320\243, \320\264\320\221", nullptr));
        label_3->setText(QCoreApplication::translate("HackRF_Controller", "\320\240\320\265\320\263\321\203\320\273\320\270\321\200\320\276\320\262\320\272\320\260 \321\203\321\201\320\270\320\273\320\265\320\275\320\270\321\217 (VGA), \320\264\320\221", nullptr));
        cb_amp_gain->setText(QCoreApplication::translate("HackRF_Controller", "Amp (0/14 \320\264\320\221)", nullptr));
        pb_close->setText(QCoreApplication::translate("HackRF_Controller", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HackRF_Controller: public Ui_HackRF_Controller {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HACKRF_CONTROLLER_H
