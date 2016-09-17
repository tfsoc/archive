/****************************************************************************
** Meta object code from reading C++ file 'mywindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mywindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mywindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MyWindow_t {
    QByteArrayData data[17];
    char stringdata0[172];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyWindow_t qt_meta_stringdata_MyWindow = {
    {
QT_MOC_LITERAL(0, 0, 8), // "MyWindow"
QT_MOC_LITERAL(1, 9, 7), // "koloruj"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 11), // "wstawPiksel"
QT_MOC_LITERAL(4, 30, 12), // "wstawPiksel1"
QT_MOC_LITERAL(5, 43, 10), // "paintEvent"
QT_MOC_LITERAL(6, 54, 12), // "QPaintEvent*"
QT_MOC_LITERAL(7, 67, 11), // "wstawKreske"
QT_MOC_LITERAL(8, 79, 12), // "wstawKreske1"
QT_MOC_LITERAL(9, 92, 10), // "wstawLinie"
QT_MOC_LITERAL(10, 103, 11), // "wstawLinie1"
QT_MOC_LITERAL(11, 115, 5), // "bryla"
QT_MOC_LITERAL(12, 121, 5), // "czysc"
QT_MOC_LITERAL(13, 127, 9), // "setLabels"
QT_MOC_LITERAL(14, 137, 15), // "mousePressEvent"
QT_MOC_LITERAL(15, 153, 12), // "QMouseEvent*"
QT_MOC_LITERAL(16, 166, 5) // "event"

    },
    "MyWindow\0koloruj\0\0wstawPiksel\0"
    "wstawPiksel1\0paintEvent\0QPaintEvent*\0"
    "wstawKreske\0wstawKreske1\0wstawLinie\0"
    "wstawLinie1\0bryla\0czysc\0setLabels\0"
    "mousePressEvent\0QMouseEvent*\0event"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    3,   74,    2, 0x08 /* Private */,
       3,    3,   81,    2, 0x08 /* Private */,
       4,    2,   88,    2, 0x08 /* Private */,
       5,    1,   93,    2, 0x08 /* Private */,
       7,    4,   96,    2, 0x08 /* Private */,
       8,    4,  105,    2, 0x08 /* Private */,
       9,    2,  114,    2, 0x08 /* Private */,
      10,    2,  119,    2, 0x08 /* Private */,
      11,    0,  124,    2, 0x08 /* Private */,
      12,    0,  125,    2, 0x08 /* Private */,
      13,    1,  126,    2, 0x08 /* Private */,
      14,    1,  129,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    2,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::QColor,    2,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 15,   16,

       0        // eod
};

void MyWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MyWindow *_t = static_cast<MyWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->koloruj((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->wstawPiksel((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QColor(*)>(_a[3]))); break;
        case 2: _t->wstawPiksel1((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->paintEvent((*reinterpret_cast< QPaintEvent*(*)>(_a[1]))); break;
        case 4: _t->wstawKreske((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 5: _t->wstawKreske1((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 6: _t->wstawLinie((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->wstawLinie1((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->bryla(); break;
        case 9: _t->czysc(); break;
        case 10: _t->setLabels((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->mousePressEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MyWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MyWindow.data,
      qt_meta_data_MyWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MyWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MyWindow.stringdata0))
        return static_cast<void*>(const_cast< MyWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int MyWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
