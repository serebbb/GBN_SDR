/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "mTaPlot/mTaPlot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *act_admin_connect;
    QAction *act_client_connect;
    QAction *act_disconnect;
    QAction *act_get_signals;
    QAction *act_set_ip;
    QAction *act_set_port;
    QAction *act_local_host;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QComboBox *cb_device;
    QHBoxLayout *freq_layout;
    QPushButton *pb_set_cent_freq;
    QGroupBox *gb_server;
    QVBoxLayout *verticalLayout_4;
    QTextEdit *te_server_info;
    QLineEdit *le_msg;
    QPushButton *pb_send_msg;
    QGroupBox *gb_save_signal;
    QVBoxLayout *verticalLayout_3;
    QLabel *lb_dropped_buffer;
    QLabel *label_4;
    QLineEdit *le_signal_filename;
    QPushButton *bp_set_signal_filename;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QVBoxLayout *verticalLayout_6;
    TaPlot *widAmlSpecTop;
    TaPlot *widSonogramBottom;
    QGroupBox *gb_spec_param;
    QGridLayout *gridLayout;
    QComboBox *cb_fftsize;
    QLabel *label_7;
    QLabel *label_6;
    QLabel *label_5;
    QSpinBox *spb_accum_sono;
    QComboBox *cb_accum_spec;
    QCheckBox *chb_spec_enable;
    QCheckBox *chb_log_spec;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1233, 639);
        MainWindow->setMinimumSize(QSize(871, 639));
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        act_admin_connect = new QAction(MainWindow);
        act_admin_connect->setObjectName(QString::fromUtf8("act_admin_connect"));
        act_client_connect = new QAction(MainWindow);
        act_client_connect->setObjectName(QString::fromUtf8("act_client_connect"));
        act_disconnect = new QAction(MainWindow);
        act_disconnect->setObjectName(QString::fromUtf8("act_disconnect"));
        act_get_signals = new QAction(MainWindow);
        act_get_signals->setObjectName(QString::fromUtf8("act_get_signals"));
        act_set_ip = new QAction(MainWindow);
        act_set_ip->setObjectName(QString::fromUtf8("act_set_ip"));
        act_set_port = new QAction(MainWindow);
        act_set_port->setObjectName(QString::fromUtf8("act_set_port"));
        act_local_host = new QAction(MainWindow);
        act_local_host->setObjectName(QString::fromUtf8("act_local_host"));
        act_local_host->setCheckable(true);
        act_local_host->setChecked(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(4);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(2, 2, 2, 2);
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy);
        scrollArea->setMinimumSize(QSize(0, 0));
        scrollArea->setStyleSheet(QString::fromUtf8(""));
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 274, 580));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setSpacing(4);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(4, 4, 4, 4);
        cb_device = new QComboBox(scrollAreaWidgetContents);
        cb_device->setObjectName(QString::fromUtf8("cb_device"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(cb_device->sizePolicy().hasHeightForWidth());
        cb_device->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(cb_device);

        freq_layout = new QHBoxLayout();
        freq_layout->setSpacing(0);
        freq_layout->setObjectName(QString::fromUtf8("freq_layout"));

        verticalLayout->addLayout(freq_layout);

        pb_set_cent_freq = new QPushButton(scrollAreaWidgetContents);
        pb_set_cent_freq->setObjectName(QString::fromUtf8("pb_set_cent_freq"));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        font.setStrikeOut(false);
        font.setKerning(true);
        pb_set_cent_freq->setFont(font);

        verticalLayout->addWidget(pb_set_cent_freq);

        gb_server = new QGroupBox(scrollAreaWidgetContents);
        gb_server->setObjectName(QString::fromUtf8("gb_server"));
        gb_server->setEnabled(false);
        sizePolicy1.setHeightForWidth(gb_server->sizePolicy().hasHeightForWidth());
        gb_server->setSizePolicy(sizePolicy1);
        gb_server->setMinimumSize(QSize(0, 150));
        QFont font1;
        font1.setBold(false);
        font1.setWeight(50);
        gb_server->setFont(font1);
        gb_server->setMouseTracking(false);
        verticalLayout_4 = new QVBoxLayout(gb_server);
        verticalLayout_4->setSpacing(5);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(4, 4, 4, 4);
        te_server_info = new QTextEdit(gb_server);
        te_server_info->setObjectName(QString::fromUtf8("te_server_info"));
        te_server_info->setReadOnly(true);

        verticalLayout_4->addWidget(te_server_info);

        le_msg = new QLineEdit(gb_server);
        le_msg->setObjectName(QString::fromUtf8("le_msg"));

        verticalLayout_4->addWidget(le_msg);

        pb_send_msg = new QPushButton(gb_server);
        pb_send_msg->setObjectName(QString::fromUtf8("pb_send_msg"));

        verticalLayout_4->addWidget(pb_send_msg);

        verticalLayout_4->setStretch(1, 1);
        verticalLayout_4->setStretch(2, 5);

        verticalLayout->addWidget(gb_server);

        gb_save_signal = new QGroupBox(scrollAreaWidgetContents);
        gb_save_signal->setObjectName(QString::fromUtf8("gb_save_signal"));
        sizePolicy1.setHeightForWidth(gb_save_signal->sizePolicy().hasHeightForWidth());
        gb_save_signal->setSizePolicy(sizePolicy1);
        verticalLayout_3 = new QVBoxLayout(gb_save_signal);
        verticalLayout_3->setSpacing(5);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(4, 4, 4, 4);
        lb_dropped_buffer = new QLabel(gb_save_signal);
        lb_dropped_buffer->setObjectName(QString::fromUtf8("lb_dropped_buffer"));

        verticalLayout_3->addWidget(lb_dropped_buffer);

        label_4 = new QLabel(gb_save_signal);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_3->addWidget(label_4);

        le_signal_filename = new QLineEdit(gb_save_signal);
        le_signal_filename->setObjectName(QString::fromUtf8("le_signal_filename"));

        verticalLayout_3->addWidget(le_signal_filename);

        bp_set_signal_filename = new QPushButton(gb_save_signal);
        bp_set_signal_filename->setObjectName(QString::fromUtf8("bp_set_signal_filename"));

        verticalLayout_3->addWidget(bp_set_signal_filename);


        verticalLayout->addWidget(gb_save_signal);

        scrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout->addWidget(scrollArea);

        scrollArea_2 = new QScrollArea(centralWidget);
        scrollArea_2->setObjectName(QString::fromUtf8("scrollArea_2"));
        scrollArea_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 947, 580));
        verticalLayout_6 = new QVBoxLayout(scrollAreaWidgetContents_2);
        verticalLayout_6->setSpacing(4);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(4, 2, 4, 2);
        widAmlSpecTop = new TaPlot(scrollAreaWidgetContents_2);
        widAmlSpecTop->setObjectName(QString::fromUtf8("widAmlSpecTop"));

        verticalLayout_6->addWidget(widAmlSpecTop);

        widSonogramBottom = new TaPlot(scrollAreaWidgetContents_2);
        widSonogramBottom->setObjectName(QString::fromUtf8("widSonogramBottom"));

        verticalLayout_6->addWidget(widSonogramBottom);

        gb_spec_param = new QGroupBox(scrollAreaWidgetContents_2);
        gb_spec_param->setObjectName(QString::fromUtf8("gb_spec_param"));
        gb_spec_param->setFlat(false);
        gb_spec_param->setCheckable(false);
        gridLayout = new QGridLayout(gb_spec_param);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(4, 4, 4, 4);
        cb_fftsize = new QComboBox(gb_spec_param);
        cb_fftsize->addItem(QString());
        cb_fftsize->addItem(QString());
        cb_fftsize->addItem(QString());
        cb_fftsize->addItem(QString());
        cb_fftsize->setObjectName(QString::fromUtf8("cb_fftsize"));

        gridLayout->addWidget(cb_fftsize, 0, 1, 2, 1);

        label_7 = new QLabel(gb_spec_param);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 0, 0, 2, 1);

        label_6 = new QLabel(gb_spec_param);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 0, 2, 1, 1);

        label_5 = new QLabel(gb_spec_param);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 2, 0, 1, 1);

        spb_accum_sono = new QSpinBox(gb_spec_param);
        spb_accum_sono->setObjectName(QString::fromUtf8("spb_accum_sono"));
        spb_accum_sono->setMinimum(75);
        spb_accum_sono->setMaximum(225);
        spb_accum_sono->setSingleStep(25);
        spb_accum_sono->setValue(75);

        gridLayout->addWidget(spb_accum_sono, 0, 3, 1, 1);

        cb_accum_spec = new QComboBox(gb_spec_param);
        cb_accum_spec->addItem(QString());
        cb_accum_spec->addItem(QString());
        cb_accum_spec->addItem(QString());
        cb_accum_spec->addItem(QString());
        cb_accum_spec->addItem(QString());
        cb_accum_spec->addItem(QString());
        cb_accum_spec->addItem(QString());
        cb_accum_spec->addItem(QString());
        cb_accum_spec->setObjectName(QString::fromUtf8("cb_accum_spec"));

        gridLayout->addWidget(cb_accum_spec, 2, 1, 1, 1);

        chb_spec_enable = new QCheckBox(gb_spec_param);
        chb_spec_enable->setObjectName(QString::fromUtf8("chb_spec_enable"));

        gridLayout->addWidget(chb_spec_enable, 2, 2, 1, 1);

        chb_log_spec = new QCheckBox(gb_spec_param);
        chb_log_spec->setObjectName(QString::fromUtf8("chb_log_spec"));

        gridLayout->addWidget(chb_log_spec, 2, 3, 1, 1);


        verticalLayout_6->addWidget(gb_spec_param);

        scrollArea_2->setWidget(scrollAreaWidgetContents_2);

        horizontalLayout->addWidget(scrollArea_2);

        horizontalLayout->setStretch(1, 1);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1233, 21));
        sizePolicy1.setHeightForWidth(menuBar->sizePolicy().hasHeightForWidth());
        menuBar->setSizePolicy(sizePolicy1);
        QFont font2;
        font2.setBold(true);
        font2.setWeight(75);
        menuBar->setFont(font2);
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menu);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu_3 = new QMenu(menu);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        sizePolicy1.setHeightForWidth(mainToolBar->sizePolicy().hasHeightForWidth());
        mainToolBar->setSizePolicy(sizePolicy1);
        mainToolBar->setMinimumSize(QSize(0, 0));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(menu_3->menuAction());
        menu->addAction(menu_2->menuAction());
        menu->addAction(act_disconnect);
        menu->addSeparator();
        menu->addAction(act_get_signals);
        menu_2->addAction(act_admin_connect);
        menu_2->addAction(act_client_connect);
        menu_3->addAction(act_local_host);
        menu_3->addAction(act_set_ip);
        menu_3->addAction(act_set_port);

        retranslateUi(MainWindow);

        cb_fftsize->setCurrentIndex(3);
        cb_accum_spec->setCurrentIndex(5);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        act_admin_connect->setText(QCoreApplication::translate("MainWindow", "\320\220\320\264\320\274\320\270\320\275\320\270\321\201\321\202\321\200\320\260\321\202\320\276\321\200", nullptr));
#if QT_CONFIG(tooltip)
        act_admin_connect->setToolTip(QCoreApplication::translate("MainWindow", "\320\220\320\264\320\274\320\270\320\275\320\270\321\201\321\202\321\200\320\260\321\202\320\276\321\200", nullptr));
#endif // QT_CONFIG(tooltip)
        act_client_connect->setText(QCoreApplication::translate("MainWindow", "\320\232\320\273\320\270\320\265\320\275\321\202", nullptr));
        act_disconnect->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\320\273\321\216\321\207\320\270\321\202\321\214\321\201\321\217 \320\276\321\202 \321\201\320\265\321\200\320\262\320\265\321\200\320\260", nullptr));
#if QT_CONFIG(tooltip)
        act_disconnect->setToolTip(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\320\273\321\216\321\207\320\270\321\202\321\214\321\201\321\217 \320\276\321\202 \321\201\320\265\321\200\320\262\320\265\321\200\320\260", nullptr));
#endif // QT_CONFIG(tooltip)
        act_get_signals->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\273\321\203\321\207\320\270\321\202\321\214 \320\267\320\260\320\277\320\270\321\201\320\270 ", nullptr));
        act_set_ip->setText(QCoreApplication::translate("MainWindow", "\320\243\320\272\320\260\320\267\320\260\321\202\321\214 IP \320\260\320\264\321\200\320\265\321\201 \321\201\320\265\321\200\320\262\320\265\321\200\320\260", nullptr));
        act_set_port->setText(QCoreApplication::translate("MainWindow", "\320\243\320\272\320\260\320\267\320\260\321\202\321\214 \320\277\320\276\321\200\321\202 \321\201\320\265\321\200\320\262\320\265\321\200\320\260", nullptr));
        act_local_host->setText(QCoreApplication::translate("MainWindow", "\320\233\320\276\320\272\320\260\320\273\321\214\320\275\320\260\321\217 \321\201\320\265\321\202\321\214", nullptr));
        pb_set_cent_freq->setText(QCoreApplication::translate("MainWindow", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214 \321\207\320\260\321\201\321\202\320\276\321\202\321\203", nullptr));
        gb_server->setTitle(QCoreApplication::translate("MainWindow", "\320\241\320\265\321\200\320\262\320\265\321\200", nullptr));
        le_msg->setInputMask(QString());
        le_msg->setText(QString());
        pb_send_msg->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214", nullptr));
        gb_save_signal->setTitle(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\277\320\270\321\201\321\214 \321\201\320\270\320\263\320\275\320\260\320\273\320\260", nullptr));
        lb_dropped_buffer->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\321\202\320\265\321\200\321\217\320\275\320\276 \320\277\320\260\320\272\320\265\321\202\320\276\320\262: 0", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\320\237\321\203\321\202\321\214 \320\272 \321\204\320\260\320\271\320\273\321\203", nullptr));
        bp_set_signal_filename->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \320\264\321\200\321\203\320\263\320\276\320\271 \320\277\321\203\321\202\321\214", nullptr));
        gb_spec_param->setTitle(QCoreApplication::translate("MainWindow", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 \321\201\320\277\320\265\320\272\321\202\321\200\320\260", nullptr));
        cb_fftsize->setItemText(0, QCoreApplication::translate("MainWindow", "16384", nullptr));
        cb_fftsize->setItemText(1, QCoreApplication::translate("MainWindow", "8192", nullptr));
        cb_fftsize->setItemText(2, QCoreApplication::translate("MainWindow", "4096", nullptr));
        cb_fftsize->setItemText(3, QCoreApplication::translate("MainWindow", "2048", nullptr));

        cb_fftsize->setCurrentText(QCoreApplication::translate("MainWindow", "2048", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\320\267\320\274\320\265\321\200 \320\221\320\237\320\244", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\320\267\320\274\320\265\321\200 \321\201\320\277\320\265\320\272\321\202\321\200\320\276\320\263\321\200\320\260\320\274\320\274\321\213", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\320\267\320\274\320\265\321\200 \320\261\321\203\321\204\320\265\321\200\320\260 \320\275\320\260\320\272\320\276\320\277\320\273\320\265\320\275\320\270\321\217", nullptr));
        cb_accum_spec->setItemText(0, QCoreApplication::translate("MainWindow", "256", nullptr));
        cb_accum_spec->setItemText(1, QCoreApplication::translate("MainWindow", "224", nullptr));
        cb_accum_spec->setItemText(2, QCoreApplication::translate("MainWindow", "192", nullptr));
        cb_accum_spec->setItemText(3, QCoreApplication::translate("MainWindow", "160", nullptr));
        cb_accum_spec->setItemText(4, QCoreApplication::translate("MainWindow", "128", nullptr));
        cb_accum_spec->setItemText(5, QCoreApplication::translate("MainWindow", "96", nullptr));
        cb_accum_spec->setItemText(6, QCoreApplication::translate("MainWindow", "64", nullptr));
        cb_accum_spec->setItemText(7, QCoreApplication::translate("MainWindow", "32", nullptr));

        cb_accum_spec->setCurrentText(QCoreApplication::translate("MainWindow", "96", nullptr));
        chb_spec_enable->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\276\320\261\321\200\320\260\320\266\320\260\321\202\321\214 \321\201\320\277\320\265\320\272\321\202\321\200", nullptr));
        chb_log_spec->setText(QCoreApplication::translate("MainWindow", "\320\233\320\276\320\263\320\260\321\200\320\270\321\204\320\274\320\270\321\207\320\265\321\201\320\272\320\270\320\271 \321\201\320\277\320\265\320\272\321\202\321\200", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\320\241\320\265\321\200\320\262\320\265\321\200", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\264\320\272\320\273\321\216\321\207\320\265\320\275\320\270\320\265 \320\272 \321\201\320\265\321\200\320\262\320\265\321\200\321\203", nullptr));
        menu_3->setTitle(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270 \320\277\320\276\320\264\320\272\320\273\321\216\321\207\320\265\320\275\320\270\321\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
