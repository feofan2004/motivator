/****************************************************************************
** Meta object code from reading C++ file 'player.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../player.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'player.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Player_t {
    QByteArrayData data[15];
    char stringdata[235];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Player_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Player_t qt_meta_stringdata_Player = {
    {
QT_MOC_LITERAL(0, 0, 6),
QT_MOC_LITERAL(1, 7, 27),
QT_MOC_LITERAL(2, 35, 0),
QT_MOC_LITERAL(3, 36, 1),
QT_MOC_LITERAL(4, 38, 30),
QT_MOC_LITERAL(5, 69, 25),
QT_MOC_LITERAL(6, 95, 25),
QT_MOC_LITERAL(7, 121, 19),
QT_MOC_LITERAL(8, 141, 7),
QT_MOC_LITERAL(9, 149, 18),
QT_MOC_LITERAL(10, 168, 11),
QT_MOC_LITERAL(11, 180, 12),
QT_MOC_LITERAL(12, 193, 14),
QT_MOC_LITERAL(13, 208, 12),
QT_MOC_LITERAL(14, 221, 12)
    },
    "Player\0setCurrentSongDurationLabel\0\0"
    "a\0setCurrentSongCurrentTimeLabel\0"
    "nextSongInPlaylistManager\0"
    "prevSongInPlaylistManager\0openPlaylistsWidget\0"
    "addSong\0addFuckingPlaylist\0delPlaylist\0"
    "playThisSong\0deleteThisSong\0savePlaylist\0"
    "loadPlaylist\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Player[] = {

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
       1,    1,   74,    2, 0x0a,
       4,    1,   77,    2, 0x0a,
       5,    0,   80,    2, 0x0a,
       6,    0,   81,    2, 0x0a,
       7,    0,   82,    2, 0x0a,
       8,    0,   83,    2, 0x0a,
       9,    0,   84,    2, 0x0a,
      10,    0,   85,    2, 0x0a,
      11,    1,   86,    2, 0x0a,
      12,    0,   89,    2, 0x0a,
      13,    0,   90,    2, 0x0a,
      14,    0,   91,    2, 0x0a,

 // slots: parameters
    QMetaType::Void, QMetaType::LongLong,    3,
    QMetaType::Void, QMetaType::LongLong,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Player::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Player *_t = static_cast<Player *>(_o);
        switch (_id) {
        case 0: _t->setCurrentSongDurationLabel((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 1: _t->setCurrentSongCurrentTimeLabel((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 2: _t->nextSongInPlaylistManager(); break;
        case 3: _t->prevSongInPlaylistManager(); break;
        case 4: _t->openPlaylistsWidget(); break;
        case 5: _t->addSong(); break;
        case 6: _t->addFuckingPlaylist(); break;
        case 7: _t->delPlaylist(); break;
        case 8: _t->playThisSong((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 9: _t->deleteThisSong(); break;
        case 10: _t->savePlaylist(); break;
        case 11: _t->loadPlaylist(); break;
        default: ;
        }
    }
}

const QMetaObject Player::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Player.data,
      qt_meta_data_Player,  qt_static_metacall, 0, 0}
};


const QMetaObject *Player::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Player::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Player.stringdata))
        return static_cast<void*>(const_cast< Player*>(this));
    return QObject::qt_metacast(_clname);
}

int Player::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
