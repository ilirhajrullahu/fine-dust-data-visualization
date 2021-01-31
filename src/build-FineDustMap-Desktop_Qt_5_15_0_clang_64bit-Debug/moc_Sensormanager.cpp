/****************************************************************************
** Meta object code from reading C++ file 'Sensormanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../FineDustMap/Sensormanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Sensormanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SensorManager_t {
    QByteArrayData data[18];
    char stringdata0[204];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SensorManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SensorManager_t qt_meta_stringdata_SensorManager = {
    {
QT_MOC_LITERAL(0, 0, 13), // "SensorManager"
QT_MOC_LITERAL(1, 14, 12), // "avgCityValue"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 8), // "cityName"
QT_MOC_LITERAL(4, 37, 7), // "measure"
QT_MOC_LITERAL(5, 45, 8), // "timeFrom"
QT_MOC_LITERAL(6, 54, 9), // "timeUntil"
QT_MOC_LITERAL(7, 64, 11), // "getLocation"
QT_MOC_LITERAL(8, 76, 12), // "QGeoLocation"
QT_MOC_LITERAL(9, 89, 16), // "getCityRectangle"
QT_MOC_LITERAL(10, 106, 13), // "QGeoRectangle"
QT_MOC_LITERAL(11, 120, 13), // "getCityCenter"
QT_MOC_LITERAL(12, 134, 14), // "QGeoCoordinate"
QT_MOC_LITERAL(13, 149, 22), // "getAveragePolygonValue"
QT_MOC_LITERAL(14, 172, 9), // "double[6]"
QT_MOC_LITERAL(15, 182, 5), // "polyY"
QT_MOC_LITERAL(16, 188, 5), // "polyX"
QT_MOC_LITERAL(17, 194, 9) // "dataValue"

    },
    "SensorManager\0avgCityValue\0\0cityName\0"
    "measure\0timeFrom\0timeUntil\0getLocation\0"
    "QGeoLocation\0getCityRectangle\0"
    "QGeoRectangle\0getCityCenter\0QGeoCoordinate\0"
    "getAveragePolygonValue\0double[6]\0polyY\0"
    "polyX\0dataValue"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SensorManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    4,   39,    2, 0x02 /* Public */,
       7,    1,   48,    2, 0x02 /* Public */,
       9,    1,   51,    2, 0x02 /* Public */,
      11,    1,   54,    2, 0x02 /* Public */,
      13,    3,   57,    2, 0x02 /* Public */,

 // methods: parameters
    QMetaType::Double, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,    3,    4,    5,    6,
    0x80000000 | 8, QMetaType::QString,    3,
    0x80000000 | 10, QMetaType::QString,    3,
    0x80000000 | 12, QMetaType::QString,    3,
    QMetaType::Double, 0x80000000 | 14, 0x80000000 | 14, QMetaType::QString,   15,   16,   17,

       0        // eod
};

void SensorManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SensorManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { double _r = _t->avgCityValue((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 1: { QGeoLocation _r = _t->getLocation((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QGeoLocation*>(_a[0]) = std::move(_r); }  break;
        case 2: { QGeoRectangle _r = _t->getCityRectangle((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QGeoRectangle*>(_a[0]) = std::move(_r); }  break;
        case 3: { QGeoCoordinate _r = _t->getCityCenter((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QGeoCoordinate*>(_a[0]) = std::move(_r); }  break;
        case 4: { double _r = _t->getAveragePolygonValue((*reinterpret_cast< double(*)[6]>(_a[1])),(*reinterpret_cast< double(*)[6]>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SensorManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_SensorManager.data,
    qt_meta_data_SensorManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SensorManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SensorManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SensorManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SensorManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
