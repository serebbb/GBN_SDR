/****************************************************************************
** Meta object code from reading C++ file 'tcpclient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../tcpclient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tcpclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_tcpclient_t {
    QByteArrayData data[12];
    char stringdata0[100];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_tcpclient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_tcpclient_t qt_meta_stringdata_tcpclient = {
    {
QT_MOC_LITERAL(0, 0, 9), // "tcpclient"
QT_MOC_LITERAL(1, 10, 12), // "dataRecieved"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 7), // "Message"
QT_MOC_LITERAL(4, 32, 3), // "mes"
QT_MOC_LITERAL(5, 36, 14), // "finish_recieve"
QT_MOC_LITERAL(6, 51, 13), // "write_to_file"
QT_MOC_LITERAL(7, 65, 3), // "dat"
QT_MOC_LITERAL(8, 69, 8), // "rec_prog"
QT_MOC_LITERAL(9, 78, 2), // "pr"
QT_MOC_LITERAL(10, 81, 13), // "slotReadyRead"
QT_MOC_LITERAL(11, 95, 4) // "prog"

    },
    "tcpclient\0dataRecieved\0\0Message\0mes\0"
    "finish_recieve\0write_to_file\0dat\0"
    "rec_prog\0pr\0slotReadyRead\0prog"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_tcpclient[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       5,    0,   47,    2, 0x06 /* Public */,
       6,    1,   48,    2, 0x06 /* Public */,
       8,    1,   51,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,   54,    2, 0x0a /* Public */,
      11,    0,   55,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    7,
    QMetaType::Void, QMetaType::Int,    9,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void tcpclient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<tcpclient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->dataRecieved((*reinterpret_cast< Message(*)>(_a[1]))); break;
        case 1: _t->finish_recieve(); break;
        case 2: _t->write_to_file((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 3: _t->rec_prog((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->slotReadyRead(); break;
        case 5: _t->prog(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (tcpclient::*)(Message );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&tcpclient::dataRecieved)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (tcpclient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&tcpclient::finish_recieve)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (tcpclient::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&tcpclient::write_to_file)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (tcpclient::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&tcpclient::rec_prog)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject tcpclient::staticMetaObject = { {
    QMetaObject::SuperData::link<QTcpSocket::staticMetaObject>(),
    qt_meta_stringdata_tcpclient.data,
    qt_meta_data_tcpclient,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *tcpclient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *tcpclient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_tcpclient.stringdata0))
        return static_cast<void*>(this);
    return QTcpSocket::qt_metacast(_clname);
}

int tcpclient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpSocket::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void tcpclient::dataRecieved(Message _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void tcpclient::finish_recieve()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void tcpclient::write_to_file(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void tcpclient::rec_prog(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
