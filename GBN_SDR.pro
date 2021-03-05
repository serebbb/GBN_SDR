#-------------------------------------------------
#
# Project created by QtCreator 2020-10-31T10:59:57
#
#-------------------------------------------------

QT += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

RESOURCES += \
    bin/qdarkstyle/style.qrc

TARGET = GBN_SDR
TEMPLATE = app

DESTDIR  = $$PWD/bin

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#CONFIG += c++11

INCLUDEPATH += .\

SOURCES += \
    UI/hackrf_controller.cpp \
    UI/spinWidget.cpp \
    Ui/graphics.cpp \
    main.cpp \
    mainwindow.cpp \
    network.cpp \
    other_functions.cpp \
    proc_thread.cpp \
    sdr.cpp \
    sdr_thread.cpp \
    settings.cpp \
    mTaClass/circbuffer.cpp \
    mTaClass/medFilter1d.cpp \
    mTaClass/taclass.cpp \
    myconvert.cpp \
    signals_and_slots.cpp \
    tcpclient.cpp

HEADERS += \
    UI/hackrf_controller.h \
    UI/spinWidget.h \
    mainwindow.h \
    proc_thread.h \
    mysettings.h \
    mTaClass/circbuffer.h \
    mTaClass/medFilter1d.h \
    mTaClass/mediator.h \
    mTaClass/taclass.h \
    mTaClass/TaDefs.h \
    myconvert.h \
    sdr_thread.h \
    tcpclient.h \
    tuner_state.h

FORMS += \
        UI/hackrf_controller.ui \
        mainwindow.ui

if (!debug_and_release|build_pass):CONFIG(debug, debug|release) {
    win32:LIBS = $$member(LIBS, 0) \
        $$member(LIBS, 1)d
}

#unix:{
#include(qwt.pri)
#LIBS += -lfftw3
#LIBS += -lfftw3f
#}

# Подключение библиотек
INCLUDEPATH += $$PWD\qwt_win
#INCLUDEPATH += $$PWD\libhackrf
INCLUDEPATH += $$PWD\SoapySDR
INCLUDEPATH += $$PWD\fftw3

LIBS += -L$$PWD\bin\lib -lqwt
#LIBS += -L$$PWD\bin\lib -lhackrf
LIBS += -L$$PWD\bin\lib -lSoapySDR
LIBS += -L$$PWD\bin\lib -llibfftw3-3
LIBS += -L$$PWD\bin\lib -llibfftw3f-3

RC_FILE += icon.rc
OTHER_FILES += icon.rc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    bin/qdarkstyle/rc/arrow_down.png \
    bin/qdarkstyle/rc/arrow_down@2x.png \
    bin/qdarkstyle/rc/arrow_down_disabled.png \
    bin/qdarkstyle/rc/arrow_down_disabled@2x.png \
    bin/qdarkstyle/rc/arrow_down_focus.png \
    bin/qdarkstyle/rc/arrow_down_focus@2x.png \
    bin/qdarkstyle/rc/arrow_down_pressed.png \
    bin/qdarkstyle/rc/arrow_down_pressed@2x.png \
    bin/qdarkstyle/rc/arrow_left.png \
    bin/qdarkstyle/rc/arrow_left@2x.png \
    bin/qdarkstyle/rc/arrow_left_disabled.png \
    bin/qdarkstyle/rc/arrow_left_disabled@2x.png \
    bin/qdarkstyle/rc/arrow_left_focus.png \
    bin/qdarkstyle/rc/arrow_left_focus@2x.png \
    bin/qdarkstyle/rc/arrow_left_pressed.png \
    bin/qdarkstyle/rc/arrow_left_pressed@2x.png \
    bin/qdarkstyle/rc/arrow_right.png \
    bin/qdarkstyle/rc/arrow_right@2x.png \
    bin/qdarkstyle/rc/arrow_right_disabled.png \
    bin/qdarkstyle/rc/arrow_right_disabled@2x.png \
    bin/qdarkstyle/rc/arrow_right_focus.png \
    bin/qdarkstyle/rc/arrow_right_focus@2x.png \
    bin/qdarkstyle/rc/arrow_right_pressed.png \
    bin/qdarkstyle/rc/arrow_right_pressed@2x.png \
    bin/qdarkstyle/rc/arrow_up.png \
    bin/qdarkstyle/rc/arrow_up@2x.png \
    bin/qdarkstyle/rc/arrow_up_disabled.png \
    bin/qdarkstyle/rc/arrow_up_disabled@2x.png \
    bin/qdarkstyle/rc/arrow_up_focus.png \
    bin/qdarkstyle/rc/arrow_up_focus@2x.png \
    bin/qdarkstyle/rc/arrow_up_pressed.png \
    bin/qdarkstyle/rc/arrow_up_pressed@2x.png \
    bin/qdarkstyle/rc/base_icon.png \
    bin/qdarkstyle/rc/base_icon@2x.png \
    bin/qdarkstyle/rc/base_icon_disabled.png \
    bin/qdarkstyle/rc/base_icon_disabled@2x.png \
    bin/qdarkstyle/rc/base_icon_focus.png \
    bin/qdarkstyle/rc/base_icon_focus@2x.png \
    bin/qdarkstyle/rc/base_icon_pressed.png \
    bin/qdarkstyle/rc/base_icon_pressed@2x.png \
    bin/qdarkstyle/rc/branch_closed.png \
    bin/qdarkstyle/rc/branch_closed@2x.png \
    bin/qdarkstyle/rc/branch_closed_disabled.png \
    bin/qdarkstyle/rc/branch_closed_disabled@2x.png \
    bin/qdarkstyle/rc/branch_closed_focus.png \
    bin/qdarkstyle/rc/branch_closed_focus@2x.png \
    bin/qdarkstyle/rc/branch_closed_pressed.png \
    bin/qdarkstyle/rc/branch_closed_pressed@2x.png \
    bin/qdarkstyle/rc/branch_end.png \
    bin/qdarkstyle/rc/branch_end@2x.png \
    bin/qdarkstyle/rc/branch_end_disabled.png \
    bin/qdarkstyle/rc/branch_end_disabled@2x.png \
    bin/qdarkstyle/rc/branch_end_focus.png \
    bin/qdarkstyle/rc/branch_end_focus@2x.png \
    bin/qdarkstyle/rc/branch_end_pressed.png \
    bin/qdarkstyle/rc/branch_end_pressed@2x.png \
    bin/qdarkstyle/rc/branch_line.png \
    bin/qdarkstyle/rc/branch_line@2x.png \
    bin/qdarkstyle/rc/branch_line_disabled.png \
    bin/qdarkstyle/rc/branch_line_disabled@2x.png \
    bin/qdarkstyle/rc/branch_line_focus.png \
    bin/qdarkstyle/rc/branch_line_focus@2x.png \
    bin/qdarkstyle/rc/branch_line_pressed.png \
    bin/qdarkstyle/rc/branch_line_pressed@2x.png \
    bin/qdarkstyle/rc/branch_more.png \
    bin/qdarkstyle/rc/branch_more@2x.png \
    bin/qdarkstyle/rc/branch_more_disabled.png \
    bin/qdarkstyle/rc/branch_more_disabled@2x.png \
    bin/qdarkstyle/rc/branch_more_focus.png \
    bin/qdarkstyle/rc/branch_more_focus@2x.png \
    bin/qdarkstyle/rc/branch_more_pressed.png \
    bin/qdarkstyle/rc/branch_more_pressed@2x.png \
    bin/qdarkstyle/rc/branch_open.png \
    bin/qdarkstyle/rc/branch_open@2x.png \
    bin/qdarkstyle/rc/branch_open_disabled.png \
    bin/qdarkstyle/rc/branch_open_disabled@2x.png \
    bin/qdarkstyle/rc/branch_open_focus.png \
    bin/qdarkstyle/rc/branch_open_focus@2x.png \
    bin/qdarkstyle/rc/branch_open_pressed.png \
    bin/qdarkstyle/rc/branch_open_pressed@2x.png \
    bin/qdarkstyle/rc/checkbox_checked.png \
    bin/qdarkstyle/rc/checkbox_checked@2x.png \
    bin/qdarkstyle/rc/checkbox_checked_disabled.png \
    bin/qdarkstyle/rc/checkbox_checked_disabled@2x.png \
    bin/qdarkstyle/rc/checkbox_checked_focus.png \
    bin/qdarkstyle/rc/checkbox_checked_focus@2x.png \
    bin/qdarkstyle/rc/checkbox_checked_pressed.png \
    bin/qdarkstyle/rc/checkbox_checked_pressed@2x.png \
    bin/qdarkstyle/rc/checkbox_indeterminate.png \
    bin/qdarkstyle/rc/checkbox_indeterminate@2x.png \
    bin/qdarkstyle/rc/checkbox_indeterminate_disabled.png \
    bin/qdarkstyle/rc/checkbox_indeterminate_disabled@2x.png \
    bin/qdarkstyle/rc/checkbox_indeterminate_focus.png \
    bin/qdarkstyle/rc/checkbox_indeterminate_focus@2x.png \
    bin/qdarkstyle/rc/checkbox_indeterminate_pressed.png \
    bin/qdarkstyle/rc/checkbox_indeterminate_pressed@2x.png \
    bin/qdarkstyle/rc/checkbox_unchecked.png \
    bin/qdarkstyle/rc/checkbox_unchecked@2x.png \
    bin/qdarkstyle/rc/checkbox_unchecked_disabled.png \
    bin/qdarkstyle/rc/checkbox_unchecked_disabled@2x.png \
    bin/qdarkstyle/rc/checkbox_unchecked_focus.png \
    bin/qdarkstyle/rc/checkbox_unchecked_focus@2x.png \
    bin/qdarkstyle/rc/checkbox_unchecked_pressed.png \
    bin/qdarkstyle/rc/checkbox_unchecked_pressed@2x.png \
    bin/qdarkstyle/rc/line_horizontal.png \
    bin/qdarkstyle/rc/line_horizontal@2x.png \
    bin/qdarkstyle/rc/line_horizontal_disabled.png \
    bin/qdarkstyle/rc/line_horizontal_disabled@2x.png \
    bin/qdarkstyle/rc/line_horizontal_focus.png \
    bin/qdarkstyle/rc/line_horizontal_focus@2x.png \
    bin/qdarkstyle/rc/line_horizontal_pressed.png \
    bin/qdarkstyle/rc/line_horizontal_pressed@2x.png \
    bin/qdarkstyle/rc/line_vertical.png \
    bin/qdarkstyle/rc/line_vertical@2x.png \
    bin/qdarkstyle/rc/line_vertical_disabled.png \
    bin/qdarkstyle/rc/line_vertical_disabled@2x.png \
    bin/qdarkstyle/rc/line_vertical_focus.png \
    bin/qdarkstyle/rc/line_vertical_focus@2x.png \
    bin/qdarkstyle/rc/line_vertical_pressed.png \
    bin/qdarkstyle/rc/line_vertical_pressed@2x.png \
    bin/qdarkstyle/rc/radio_checked.png \
    bin/qdarkstyle/rc/radio_checked@2x.png \
    bin/qdarkstyle/rc/radio_checked_disabled.png \
    bin/qdarkstyle/rc/radio_checked_disabled@2x.png \
    bin/qdarkstyle/rc/radio_checked_focus.png \
    bin/qdarkstyle/rc/radio_checked_focus@2x.png \
    bin/qdarkstyle/rc/radio_checked_pressed.png \
    bin/qdarkstyle/rc/radio_checked_pressed@2x.png \
    bin/qdarkstyle/rc/radio_unchecked.png \
    bin/qdarkstyle/rc/radio_unchecked@2x.png \
    bin/qdarkstyle/rc/radio_unchecked_disabled.png \
    bin/qdarkstyle/rc/radio_unchecked_disabled@2x.png \
    bin/qdarkstyle/rc/radio_unchecked_focus.png \
    bin/qdarkstyle/rc/radio_unchecked_focus@2x.png \
    bin/qdarkstyle/rc/radio_unchecked_pressed.png \
    bin/qdarkstyle/rc/radio_unchecked_pressed@2x.png \
    bin/qdarkstyle/rc/toolbar_move_horizontal.png \
    bin/qdarkstyle/rc/toolbar_move_horizontal@2x.png \
    bin/qdarkstyle/rc/toolbar_move_horizontal_disabled.png \
    bin/qdarkstyle/rc/toolbar_move_horizontal_disabled@2x.png \
    bin/qdarkstyle/rc/toolbar_move_horizontal_focus.png \
    bin/qdarkstyle/rc/toolbar_move_horizontal_focus@2x.png \
    bin/qdarkstyle/rc/toolbar_move_horizontal_pressed.png \
    bin/qdarkstyle/rc/toolbar_move_horizontal_pressed@2x.png \
    bin/qdarkstyle/rc/toolbar_move_vertical.png \
    bin/qdarkstyle/rc/toolbar_move_vertical@2x.png \
    bin/qdarkstyle/rc/toolbar_move_vertical_disabled.png \
    bin/qdarkstyle/rc/toolbar_move_vertical_disabled@2x.png \
    bin/qdarkstyle/rc/toolbar_move_vertical_focus.png \
    bin/qdarkstyle/rc/toolbar_move_vertical_focus@2x.png \
    bin/qdarkstyle/rc/toolbar_move_vertical_pressed.png \
    bin/qdarkstyle/rc/toolbar_move_vertical_pressed@2x.png \
    bin/qdarkstyle/rc/toolbar_separator_horizontal.png \
    bin/qdarkstyle/rc/toolbar_separator_horizontal@2x.png \
    bin/qdarkstyle/rc/toolbar_separator_horizontal_disabled.png \
    bin/qdarkstyle/rc/toolbar_separator_horizontal_disabled@2x.png \
    bin/qdarkstyle/rc/toolbar_separator_horizontal_focus.png \
    bin/qdarkstyle/rc/toolbar_separator_horizontal_focus@2x.png \
    bin/qdarkstyle/rc/toolbar_separator_horizontal_pressed.png \
    bin/qdarkstyle/rc/toolbar_separator_horizontal_pressed@2x.png \
    bin/qdarkstyle/rc/toolbar_separator_vertical.png \
    bin/qdarkstyle/rc/toolbar_separator_vertical@2x.png \
    bin/qdarkstyle/rc/toolbar_separator_vertical_disabled.png \
    bin/qdarkstyle/rc/toolbar_separator_vertical_disabled@2x.png \
    bin/qdarkstyle/rc/toolbar_separator_vertical_focus.png \
    bin/qdarkstyle/rc/toolbar_separator_vertical_focus@2x.png \
    bin/qdarkstyle/rc/toolbar_separator_vertical_pressed.png \
    bin/qdarkstyle/rc/toolbar_separator_vertical_pressed@2x.png \
    bin/qdarkstyle/rc/transparent.png \
    bin/qdarkstyle/rc/transparent@2x.png \
    bin/qdarkstyle/rc/transparent_disabled.png \
    bin/qdarkstyle/rc/transparent_disabled@2x.png \
    bin/qdarkstyle/rc/transparent_focus.png \
    bin/qdarkstyle/rc/transparent_focus@2x.png \
    bin/qdarkstyle/rc/transparent_pressed.png \
    bin/qdarkstyle/rc/transparent_pressed@2x.png \
    bin/qdarkstyle/rc/window_close.png \
    bin/qdarkstyle/rc/window_close@2x.png \
    bin/qdarkstyle/rc/window_close_disabled.png \
    bin/qdarkstyle/rc/window_close_disabled@2x.png \
    bin/qdarkstyle/rc/window_close_focus.png \
    bin/qdarkstyle/rc/window_close_focus@2x.png \
    bin/qdarkstyle/rc/window_close_pressed.png \
    bin/qdarkstyle/rc/window_close_pressed@2x.png \
    bin/qdarkstyle/rc/window_grip.png \
    bin/qdarkstyle/rc/window_grip@2x.png \
    bin/qdarkstyle/rc/window_grip_disabled.png \
    bin/qdarkstyle/rc/window_grip_disabled@2x.png \
    bin/qdarkstyle/rc/window_grip_focus.png \
    bin/qdarkstyle/rc/window_grip_focus@2x.png \
    bin/qdarkstyle/rc/window_grip_pressed.png \
    bin/qdarkstyle/rc/window_grip_pressed@2x.png \
    bin/qdarkstyle/rc/window_minimize.png \
    bin/qdarkstyle/rc/window_minimize@2x.png \
    bin/qdarkstyle/rc/window_minimize_disabled.png \
    bin/qdarkstyle/rc/window_minimize_disabled@2x.png \
    bin/qdarkstyle/rc/window_minimize_focus.png \
    bin/qdarkstyle/rc/window_minimize_focus@2x.png \
    bin/qdarkstyle/rc/window_minimize_pressed.png \
    bin/qdarkstyle/rc/window_minimize_pressed@2x.png \
    bin/qdarkstyle/rc/window_undock.png \
    bin/qdarkstyle/rc/window_undock@2x.png \
    bin/qdarkstyle/rc/window_undock_disabled.png \
    bin/qdarkstyle/rc/window_undock_disabled@2x.png \
    bin/qdarkstyle/rc/window_undock_focus.png \
    bin/qdarkstyle/rc/window_undock_focus@2x.png \
    bin/qdarkstyle/rc/window_undock_pressed.png \
    bin/qdarkstyle/rc/window_undock_pressed@2x.png \
    bin/qdarkstyle/svg/arrow_down.svg \
    bin/qdarkstyle/svg/arrow_left.svg \
    bin/qdarkstyle/svg/arrow_right.svg \
    bin/qdarkstyle/svg/arrow_up.svg \
    bin/qdarkstyle/svg/base_icon.svg \
    bin/qdarkstyle/svg/base_palette.svg \
    bin/qdarkstyle/svg/branch_closed.svg \
    bin/qdarkstyle/svg/branch_end.svg \
    bin/qdarkstyle/svg/branch_line.svg \
    bin/qdarkstyle/svg/branch_more.svg \
    bin/qdarkstyle/svg/branch_open.svg \
    bin/qdarkstyle/svg/checkbox_checked.svg \
    bin/qdarkstyle/svg/checkbox_indeterminate.svg \
    bin/qdarkstyle/svg/checkbox_unchecked.svg \
    bin/qdarkstyle/svg/line_horizontal.svg \
    bin/qdarkstyle/svg/line_vertical.svg \
    bin/qdarkstyle/svg/radio_checked.svg \
    bin/qdarkstyle/svg/radio_unchecked.svg \
    bin/qdarkstyle/svg/toolbar_move_horizontal.svg \
    bin/qdarkstyle/svg/toolbar_move_vertical.svg \
    bin/qdarkstyle/svg/toolbar_separator_horizontal.svg \
    bin/qdarkstyle/svg/toolbar_separator_vertical.svg \
    bin/qdarkstyle/svg/transparent.svg \
    bin/qdarkstyle/svg/window_close.svg \
    bin/qdarkstyle/svg/window_grip.svg \
    bin/qdarkstyle/svg/window_minimize.svg \
    bin/qdarkstyle/svg/window_undock.svg \
    bin/qdarkstyle/mystyle.qss \
    bin/qdarkstyle/style.qss
