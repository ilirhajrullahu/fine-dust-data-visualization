/****************************************************************************
** Meta object code from reading C++ file 'HexagonModel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../FineDustMap/HexagonModel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'HexagonModel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_HexagonModel_t {
    QByteArrayData data[18];
    char stringdata0[233];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HexagonModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HexagonModel_t qt_meta_stringdata_HexagonModel = {
    {
QT_MOC_LITERAL(0, 0, 12), // "HexagonModel"
QT_MOC_LITERAL(1, 13, 14), // "removeHexagons"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 16), // "getTempTileColor"
QT_MOC_LITERAL(4, 46, 16), // "getPm25TileColor"
QT_MOC_LITERAL(5, 63, 16), // "getPm10TileColor"
QT_MOC_LITERAL(6, 80, 20), // "getHumidityTileColor"
QT_MOC_LITERAL(7, 101, 16), // "currentZoomLevel"
QT_MOC_LITERAL(8, 118, 9), // "zoomLevel"
QT_MOC_LITERAL(9, 128, 12), // "zoomLevelBT0"
QT_MOC_LITERAL(10, 141, 13), // "HexagonModel&"
QT_MOC_LITERAL(11, 155, 5), // "model"
QT_MOC_LITERAL(12, 161, 12), // "QQmlContext*"
QT_MOC_LITERAL(13, 174, 4), // "ctxt"
QT_MOC_LITERAL(14, 179, 12), // "zoomLevelBT7"
QT_MOC_LITERAL(15, 192, 12), // "zoomLevelBT9"
QT_MOC_LITERAL(16, 205, 13), // "zoomLevelBT10"
QT_MOC_LITERAL(17, 219, 13) // "zoomLevelBT12"

    },
    "HexagonModel\0removeHexagons\0\0"
    "getTempTileColor\0getPm25TileColor\0"
    "getPm10TileColor\0getHumidityTileColor\0"
    "currentZoomLevel\0zoomLevel\0zoomLevelBT0\0"
    "HexagonModel&\0model\0QQmlContext*\0ctxt\0"
    "zoomLevelBT7\0zoomLevelBT9\0zoomLevelBT10\0"
    "zoomLevelBT12"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HexagonModel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x02 /* Public */,
       3,    1,   70,    2, 0x02 /* Public */,
       4,    1,   73,    2, 0x02 /* Public */,
       5,    1,   76,    2, 0x02 /* Public */,
       6,    1,   79,    2, 0x02 /* Public */,
       7,    1,   82,    2, 0x02 /* Public */,
       9,    2,   85,    2, 0x02 /* Public */,
      14,    2,   90,    2, 0x02 /* Public */,
      15,    2,   95,    2, 0x02 /* Public */,
      16,    2,  100,    2, 0x02 /* Public */,
      17,    2,  105,    2, 0x02 /* Public */,

 // methods: parameters
    QMetaType::Void,
    QMetaType::QColor, QMetaType::Double,    2,
    QMetaType::QColor, QMetaType::Double,    2,
    QMetaType::QColor, QMetaType::Double,    2,
    QMetaType::QColor, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::QVariant,    8,
    QMetaType::Void, 0x80000000 | 10, 0x80000000 | 12,   11,   13,
    QMetaType::Void, 0x80000000 | 10, 0x80000000 | 12,   11,   13,
    QMetaType::Void, 0x80000000 | 10, 0x80000000 | 12,   11,   13,
    QMetaType::Void, 0x80000000 | 10, 0x80000000 | 12,   11,   13,
    QMetaType::Void, 0x80000000 | 10, 0x80000000 | 12,   11,   13,

       0        // eod
};

void HexagonModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<HexagonModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->removeHexagons(); break;
        case 1: { QColor _r = _t->getTempTileColor((*reinterpret_cast< double(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QColor*>(_a[0]) = std::move(_r); }  break;
        case 2: { QColor _r = _t->getPm25TileColor((*reinterpret_cast< double(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QColor*>(_a[0]) = std::move(_r); }  break;
        case 3: { QColor _r = _t->getPm10TileColor((*reinterpret_cast< double(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QColor*>(_a[0]) = std::move(_r); }  break;
        case 4: { QColor _r = _t->getHumidityTileColor((*reinterpret_cast< double(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QColor*>(_a[0]) = std::move(_r); }  break;
        case 5: _t->currentZoomLevel((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 6: _t->zoomLevelBT0((*reinterpret_cast< HexagonModel(*)>(_a[1])),(*reinterpret_cast< QQmlContext*(*)>(_a[2]))); break;
        case 7: _t->zoomLevelBT7((*reinterpret_cast< HexagonModel(*)>(_a[1])),(*reinterpret_cast< QQmlContext*(*)>(_a[2]))); break;
        case 8: _t->zoomLevelBT9((*reinterpret_cast< HexagonModel(*)>(_a[1])),(*reinterpret_cast< QQmlContext*(*)>(_a[2]))); break;
        case 9: _t->zoomLevelBT10((*reinterpret_cast< HexagonModel(*)>(_a[1])),(*reinterpret_cast< QQmlContext*(*)>(_a[2]))); break;
        case 10: _t->zoomLevelBT12((*reinterpret_cast< HexagonModel(*)>(_a[1])),(*reinterpret_cast< QQmlContext*(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QQmlContext* >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QQmlContext* >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QQmlContext* >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QQmlContext* >(); break;
            }
            break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QQmlContext* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject HexagonModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractListModel::staticMetaObject>(),
    qt_meta_stringdata_HexagonModel.data,
    qt_meta_data_HexagonModel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *HexagonModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HexagonModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_HexagonModel.stringdata0))
        return static_cast<void*>(this);
    return QAbstractListModel::qt_metacast(_clname);
}

int HexagonModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
