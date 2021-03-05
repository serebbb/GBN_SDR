/****************************************************************************
** Meta object code from reading C++ file 'taclass.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../mTaClass/taclass.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'taclass.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TaClass_t {
    QByteArrayData data[19];
    char stringdata0[216];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TaClass_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TaClass_t qt_meta_stringdata_TaClass = {
    {
QT_MOC_LITERAL(0, 0, 7), // "TaClass"
QT_MOC_LITERAL(1, 8, 18), // "sendGraficsSpec2os"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 6), // "float*"
QT_MOC_LITERAL(4, 35, 3), // "ost"
QT_MOC_LITERAL(5, 39, 6), // "values"
QT_MOC_LITERAL(6, 46, 4), // "size"
QT_MOC_LITERAL(7, 51, 5), // "grNum"
QT_MOC_LITERAL(8, 57, 18), // "sendGraficsSpec1os"
QT_MOC_LITERAL(9, 76, 18), // "sendGraficsTime2os"
QT_MOC_LITERAL(10, 95, 12), // "const float*"
QT_MOC_LITERAL(11, 108, 18), // "sendGraficsTime1os"
QT_MOC_LITERAL(12, 127, 12), // "sendProgress"
QT_MOC_LITERAL(13, 140, 8), // "progress"
QT_MOC_LITERAL(14, 149, 7), // "double*"
QT_MOC_LITERAL(15, 157, 16), // "sendDetectedSigs"
QT_MOC_LITERAL(16, 174, 22), // "QVector<SignDetStruct>"
QT_MOC_LITERAL(17, 197, 7), // "sigList"
QT_MOC_LITERAL(18, 205, 10) // "cancelProc"

    },
    "TaClass\0sendGraficsSpec2os\0\0float*\0"
    "ost\0values\0size\0grNum\0sendGraficsSpec1os\0"
    "sendGraficsTime2os\0const float*\0"
    "sendGraficsTime1os\0sendProgress\0"
    "progress\0double*\0sendDetectedSigs\0"
    "QVector<SignDetStruct>\0sigList\0"
    "cancelProc"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TaClass[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,   54,    2, 0x06 /* Public */,
       8,    3,   63,    2, 0x06 /* Public */,
       9,    4,   70,    2, 0x06 /* Public */,
      11,    3,   79,    2, 0x06 /* Public */,
      12,    1,   86,    2, 0x06 /* Public */,
       8,    3,   89,    2, 0x06 /* Public */,
      15,    1,   96,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      18,    0,   99,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, QMetaType::Int, QMetaType::Int,    4,    5,    6,    7,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, QMetaType::Int,    5,    6,    7,
    QMetaType::Void, 0x80000000 | 10, 0x80000000 | 10, QMetaType::Int, QMetaType::Int,    4,    5,    6,    7,
    QMetaType::Void, 0x80000000 | 10, QMetaType::Int, QMetaType::Int,    5,    6,    7,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void, 0x80000000 | 14, QMetaType::Int, QMetaType::Int,    5,    6,    7,
    QMetaType::Void, 0x80000000 | 16,   17,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void TaClass::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TaClass *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendGraficsSpec2os((*reinterpret_cast< float*(*)>(_a[1])),(*reinterpret_cast< float*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 1: _t->sendGraficsSpec1os((*reinterpret_cast< float*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 2: _t->sendGraficsTime2os((*reinterpret_cast< const float*(*)>(_a[1])),(*reinterpret_cast< const float*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 3: _t->sendGraficsTime1os((*reinterpret_cast< const float*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 4: _t->sendProgress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->sendGraficsSpec1os((*reinterpret_cast< double*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 6: _t->sendDetectedSigs((*reinterpret_cast< QVector<SignDetStruct>(*)>(_a[1]))); break;
        case 7: _t->cancelProc(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TaClass::*)(float * , float * , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TaClass::sendGraficsSpec2os)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TaClass::*)(float * , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TaClass::sendGraficsSpec1os)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (TaClass::*)(const float * , const float * , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TaClass::sendGraficsTime2os)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (TaClass::*)(const float * , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TaClass::sendGraficsTime1os)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (TaClass::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TaClass::sendProgress)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (TaClass::*)(double * , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TaClass::sendGraficsSpec1os)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (TaClass::*)(QVector<SignDetStruct> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TaClass::sendDetectedSigs)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TaClass::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_TaClass.data,
    qt_meta_data_TaClass,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TaClass::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TaClass::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TaClass.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int TaClass::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void TaClass::sendGraficsSpec2os(float * _t1, float * _t2, int _t3, int _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TaClass::sendGraficsSpec1os(float * _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TaClass::sendGraficsTime2os(const float * _t1, const float * _t2, int _t3, int _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void TaClass::sendGraficsTime1os(const float * _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void TaClass::sendProgress(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void TaClass::sendGraficsSpec1os(double * _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void TaClass::sendDetectedSigs(QVector<SignDetStruct> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
