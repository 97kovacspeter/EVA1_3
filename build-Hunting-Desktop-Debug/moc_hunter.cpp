/****************************************************************************
** Meta object code from reading C++ file 'hunter.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Hunting/hunter.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'hunter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Hunter[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x08,
      23,    7,    7,    7, 0x08,
      53,   46,    7,    7, 0x08,
      94,    7,    7,    7, 0x08,
     110,    7,    7,    7, 0x08,
     123,    7,    7,    7, 0x08,
     134,    7,    7,    7, 0x08,
     154,  149,    7,    7, 0x08,
     170,    7,    7,    7, 0x0a,
     181,    7,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Hunter[] = {
    "Hunter\0\0startNewGame()\0gameManager_gameOver()\0"
    "player\0gameManager_gameWon(GameManager::Player)\0"
    "doTimerUpdate()\0viewUpdate()\0pauseMsg()\0"
    "clickDecider()\0size\0senderSize(int)\0"
    "loadGame()\0saveGame()\0"
};

void Hunter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Hunter *_t = static_cast<Hunter *>(_o);
        switch (_id) {
        case 0: _t->startNewGame(); break;
        case 1: _t->gameManager_gameOver(); break;
        case 2: _t->gameManager_gameWon((*reinterpret_cast< GameManager::Player(*)>(_a[1]))); break;
        case 3: _t->doTimerUpdate(); break;
        case 4: _t->viewUpdate(); break;
        case 5: _t->pauseMsg(); break;
        case 6: _t->clickDecider(); break;
        case 7: _t->senderSize((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->loadGame(); break;
        case 9: _t->saveGame(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Hunter::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Hunter::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Hunter,
      qt_meta_data_Hunter, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Hunter::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Hunter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Hunter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Hunter))
        return static_cast<void*>(const_cast< Hunter*>(this));
    return QWidget::qt_metacast(_clname);
}

int Hunter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
