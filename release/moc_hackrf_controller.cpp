/****************************************************************************
** Meta object code from reading C++ file 'hackrf_controller.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../UI/hackrf_controller.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'hackrf_controller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_HackRF_Controller_t {
    QByteArrayData data[13];
    char stringdata0[239];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HackRF_Controller_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HackRF_Controller_t qt_meta_stringdata_HackRF_Controller = {
    {
QT_MOC_LITERAL(0, 0, 17), // "HackRF_Controller"
QT_MOC_LITERAL(1, 18, 16), // "lna_gain_changed"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 16), // "vga_gain_changed"
QT_MOC_LITERAL(4, 53, 18), // "sampleRate_changed"
QT_MOC_LITERAL(5, 72, 21), // "amp_gain_stateChanged"
QT_MOC_LITERAL(6, 94, 19), // "on_pb_close_clicked"
QT_MOC_LITERAL(7, 114, 24), // "on_lna_gain_valueChanged"
QT_MOC_LITERAL(8, 139, 5), // "value"
QT_MOC_LITERAL(9, 145, 24), // "on_vga_gain_valueChanged"
QT_MOC_LITERAL(10, 170, 27), // "on_cb_amp_gain_stateChanged"
QT_MOC_LITERAL(11, 198, 4), // "arg1"
QT_MOC_LITERAL(12, 203, 35) // "on_cb_sampleRate_currentTextC..."

    },
    "HackRF_Controller\0lna_gain_changed\0\0"
    "vga_gain_changed\0sampleRate_changed\0"
    "amp_gain_stateChanged\0on_pb_close_clicked\0"
    "on_lna_gain_valueChanged\0value\0"
    "on_vga_gain_valueChanged\0"
    "on_cb_amp_gain_stateChanged\0arg1\0"
    "on_cb_sampleRate_currentTextChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HackRF_Controller[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       3,    1,   62,    2, 0x06 /* Public */,
       4,    1,   65,    2, 0x06 /* Public */,
       5,    1,   68,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   71,    2, 0x08 /* Private */,
       7,    1,   72,    2, 0x08 /* Private */,
       9,    1,   75,    2, 0x08 /* Private */,
      10,    1,   78,    2, 0x08 /* Private */,
      12,    1,   81,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Bool,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::QString,   11,

       0        // eod
};

void HackRF_Controller::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<HackRF_Controller *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->lna_gain_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->vga_gain_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->sampleRate_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->amp_gain_stateChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->on_pb_close_clicked(); break;
        case 5: _t->on_lna_gain_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_vga_gain_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_cb_amp_gain_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_cb_sampleRate_currentTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (HackRF_Controller::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HackRF_Controller::lna_gain_changed)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (HackRF_Controller::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HackRF_Controller::vga_gain_changed)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (HackRF_Controller::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HackRF_Controller::sampleRate_changed)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (HackRF_Controller::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HackRF_Controller::amp_gain_stateChanged)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject HackRF_Controller::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_HackRF_Controller.data,
    qt_meta_data_HackRF_Controller,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *HackRF_Controller::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HackRF_Controller::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_HackRF_Controller.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int HackRF_Controller::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void HackRF_Controller::lna_gain_changed(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void HackRF_Controller::vga_gain_changed(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void HackRF_Controller::sampleRate_changed(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void HackRF_Controller::amp_gain_stateChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
