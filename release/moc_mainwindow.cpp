/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[51];
    char stringdata0[829];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 10), // "start_read"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 9), // "stop_read"
QT_MOC_LITERAL(4, 33, 16), // "pb_start_clicked"
QT_MOC_LITERAL(5, 50, 15), // "pb_stop_clicked"
QT_MOC_LITERAL(6, 66, 21), // "pb_open_tuner_clicked"
QT_MOC_LITERAL(7, 88, 11), // "get_signals"
QT_MOC_LITERAL(8, 100, 20), // "open_settings_window"
QT_MOC_LITERAL(9, 121, 8), // "init_sdr"
QT_MOC_LITERAL(10, 130, 12), // "showSpecData"
QT_MOC_LITERAL(11, 143, 6), // "float*"
QT_MOC_LITERAL(12, 150, 5), // "xData"
QT_MOC_LITERAL(13, 156, 5), // "yData"
QT_MOC_LITERAL(14, 162, 4), // "size"
QT_MOC_LITERAL(15, 167, 10), // "garmonicId"
QT_MOC_LITERAL(16, 178, 9), // "slotError"
QT_MOC_LITERAL(17, 188, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(18, 217, 3), // "err"
QT_MOC_LITERAL(19, 221, 20), // "show_connect_message"
QT_MOC_LITERAL(20, 242, 7), // "parsing"
QT_MOC_LITERAL(21, 250, 7), // "Message"
QT_MOC_LITERAL(22, 258, 7), // "message"
QT_MOC_LITERAL(23, 266, 6), // "discon"
QT_MOC_LITERAL(24, 273, 13), // "write_to_file"
QT_MOC_LITERAL(25, 287, 4), // "data"
QT_MOC_LITERAL(26, 292, 10), // "close_file"
QT_MOC_LITERAL(27, 303, 17), // "set_send_progress"
QT_MOC_LITERAL(28, 321, 14), // "set_network_ts"
QT_MOC_LITERAL(29, 336, 11), // "refreshProg"
QT_MOC_LITERAL(30, 348, 9), // "openTuner"
QT_MOC_LITERAL(31, 358, 13), // "setSampleRate"
QT_MOC_LITERAL(32, 372, 3), // "val"
QT_MOC_LITERAL(33, 376, 10), // "setLnaGain"
QT_MOC_LITERAL(34, 387, 10), // "setVgaGain"
QT_MOC_LITERAL(35, 398, 10), // "setAmpGain"
QT_MOC_LITERAL(36, 409, 33), // "on_le_signal_filename_textCha..."
QT_MOC_LITERAL(37, 443, 4), // "arg1"
QT_MOC_LITERAL(38, 448, 33), // "on_bp_set_signal_filename_cli..."
QT_MOC_LITERAL(39, 482, 30), // "on_spb_accum_sono_valueChanged"
QT_MOC_LITERAL(40, 513, 27), // "on_pb_set_cent_freq_clicked"
QT_MOC_LITERAL(41, 541, 32), // "on_cb_fftsize_currentTextChanged"
QT_MOC_LITERAL(42, 574, 28), // "on_chb_log_spec_stateChanged"
QT_MOC_LITERAL(43, 603, 30), // "on_act_admin_connect_triggered"
QT_MOC_LITERAL(44, 634, 31), // "on_act_client_connect_triggered"
QT_MOC_LITERAL(45, 666, 23), // "on_act_set_ip_triggered"
QT_MOC_LITERAL(46, 690, 25), // "on_act_set_port_triggered"
QT_MOC_LITERAL(47, 716, 35), // "on_cb_accum_spec_currentTextC..."
QT_MOC_LITERAL(48, 752, 25), // "on_act_local_host_toggled"
QT_MOC_LITERAL(49, 778, 27), // "on_act_disconnect_triggered"
QT_MOC_LITERAL(50, 806, 22) // "on_pb_send_msg_clicked"

    },
    "MainWindow\0start_read\0\0stop_read\0"
    "pb_start_clicked\0pb_stop_clicked\0"
    "pb_open_tuner_clicked\0get_signals\0"
    "open_settings_window\0init_sdr\0"
    "showSpecData\0float*\0xData\0yData\0size\0"
    "garmonicId\0slotError\0QAbstractSocket::SocketError\0"
    "err\0show_connect_message\0parsing\0"
    "Message\0message\0discon\0write_to_file\0"
    "data\0close_file\0set_send_progress\0"
    "set_network_ts\0refreshProg\0openTuner\0"
    "setSampleRate\0val\0setLnaGain\0setVgaGain\0"
    "setAmpGain\0on_le_signal_filename_textChanged\0"
    "arg1\0on_bp_set_signal_filename_clicked\0"
    "on_spb_accum_sono_valueChanged\0"
    "on_pb_set_cent_freq_clicked\0"
    "on_cb_fftsize_currentTextChanged\0"
    "on_chb_log_spec_stateChanged\0"
    "on_act_admin_connect_triggered\0"
    "on_act_client_connect_triggered\0"
    "on_act_set_ip_triggered\0"
    "on_act_set_port_triggered\0"
    "on_cb_accum_spec_currentTextChanged\0"
    "on_act_local_host_toggled\0"
    "on_act_disconnect_triggered\0"
    "on_pb_send_msg_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      37,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  199,    2, 0x0a /* Public */,
       3,    0,  200,    2, 0x0a /* Public */,
       4,    0,  201,    2, 0x0a /* Public */,
       5,    0,  202,    2, 0x0a /* Public */,
       6,    0,  203,    2, 0x0a /* Public */,
       7,    0,  204,    2, 0x0a /* Public */,
       8,    0,  205,    2, 0x0a /* Public */,
       9,    0,  206,    2, 0x0a /* Public */,
      10,    4,  207,    2, 0x0a /* Public */,
      16,    1,  216,    2, 0x0a /* Public */,
      19,    0,  219,    2, 0x0a /* Public */,
      20,    1,  220,    2, 0x0a /* Public */,
      23,    0,  223,    2, 0x0a /* Public */,
      24,    1,  224,    2, 0x0a /* Public */,
      26,    0,  227,    2, 0x0a /* Public */,
      27,    0,  228,    2, 0x0a /* Public */,
      28,    0,  229,    2, 0x0a /* Public */,
      29,    0,  230,    2, 0x0a /* Public */,
      30,    0,  231,    2, 0x0a /* Public */,
      31,    1,  232,    2, 0x0a /* Public */,
      33,    1,  235,    2, 0x0a /* Public */,
      34,    1,  238,    2, 0x0a /* Public */,
      35,    1,  241,    2, 0x0a /* Public */,
      36,    1,  244,    2, 0x08 /* Private */,
      38,    0,  247,    2, 0x08 /* Private */,
      39,    1,  248,    2, 0x08 /* Private */,
      40,    0,  251,    2, 0x08 /* Private */,
      41,    1,  252,    2, 0x08 /* Private */,
      42,    1,  255,    2, 0x08 /* Private */,
      43,    0,  258,    2, 0x08 /* Private */,
      44,    0,  259,    2, 0x08 /* Private */,
      45,    0,  260,    2, 0x08 /* Private */,
      46,    0,  261,    2, 0x08 /* Private */,
      47,    1,  262,    2, 0x08 /* Private */,
      48,    1,  265,    2, 0x08 /* Private */,
      49,    0,  268,    2, 0x08 /* Private */,
      50,    0,  269,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11, 0x80000000 | 11, QMetaType::Int, QMetaType::Int,   12,   13,   14,   15,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 21,   22,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,   25,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int, QMetaType::Double,   32,
    QMetaType::Int, QMetaType::Int,   32,
    QMetaType::Int, QMetaType::Int,   32,
    QMetaType::Int, QMetaType::Bool,   32,
    QMetaType::Void, QMetaType::QString,   37,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   37,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   37,
    QMetaType::Void, QMetaType::Int,   37,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   37,
    QMetaType::Void, QMetaType::Bool,   37,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->start_read(); break;
        case 1: _t->stop_read(); break;
        case 2: _t->pb_start_clicked(); break;
        case 3: _t->pb_stop_clicked(); break;
        case 4: _t->pb_open_tuner_clicked(); break;
        case 5: _t->get_signals(); break;
        case 6: _t->open_settings_window(); break;
        case 7: _t->init_sdr(); break;
        case 8: _t->showSpecData((*reinterpret_cast< float*(*)>(_a[1])),(*reinterpret_cast< float*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 9: _t->slotError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 10: _t->show_connect_message(); break;
        case 11: _t->parsing((*reinterpret_cast< Message(*)>(_a[1]))); break;
        case 12: _t->discon(); break;
        case 13: _t->write_to_file((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 14: _t->close_file(); break;
        case 15: _t->set_send_progress(); break;
        case 16: _t->set_network_ts(); break;
        case 17: _t->refreshProg(); break;
        case 18: _t->openTuner(); break;
        case 19: { int _r = _t->setSampleRate((*reinterpret_cast< double(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 20: { int _r = _t->setLnaGain((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 21: { int _r = _t->setVgaGain((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 22: { int _r = _t->setAmpGain((*reinterpret_cast< bool(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 23: _t->on_le_signal_filename_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 24: _t->on_bp_set_signal_filename_clicked(); break;
        case 25: _t->on_spb_accum_sono_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 26: _t->on_pb_set_cent_freq_clicked(); break;
        case 27: _t->on_cb_fftsize_currentTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 28: _t->on_chb_log_spec_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 29: _t->on_act_admin_connect_triggered(); break;
        case 30: _t->on_act_client_connect_triggered(); break;
        case 31: _t->on_act_set_ip_triggered(); break;
        case 32: _t->on_act_set_port_triggered(); break;
        case 33: _t->on_cb_accum_spec_currentTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 34: _t->on_act_local_host_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 35: _t->on_act_disconnect_triggered(); break;
        case 36: _t->on_pb_send_msg_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 37)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 37;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 37)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 37;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
