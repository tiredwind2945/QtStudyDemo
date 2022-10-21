/****************************************************************************
** Meta object code from reading C++ file 'searchlineEdit.h'
**
** Created: Tue Jan 19 11:27:49 2016
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "searchlineEdit.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'searchlineEdit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SearchLineEdit[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      48,   43,   15,   15, 0x08,
      68,   15,   15,   15, 0x08,
      82,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SearchLineEdit[] = {
    "SearchLineEdit\0\0searchTextChanged(QString)\0"
    "text\0textChange(QString)\0editClicked()\0"
    "btnClicked()\0"
};

const QMetaObject SearchLineEdit::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SearchLineEdit,
      qt_meta_data_SearchLineEdit, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SearchLineEdit::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SearchLineEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SearchLineEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SearchLineEdit))
        return static_cast<void*>(const_cast< SearchLineEdit*>(this));
    return QWidget::qt_metacast(_clname);
}

int SearchLineEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: searchTextChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: textChange((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: editClicked(); break;
        case 3: btnClicked(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void SearchLineEdit::searchTextChanged(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_InnerLineEdit[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      25,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_InnerLineEdit[] = {
    "InnerLineEdit\0\0pressed()\0editComplete()\0"
};

const QMetaObject InnerLineEdit::staticMetaObject = {
    { &QLineEdit::staticMetaObject, qt_meta_stringdata_InnerLineEdit,
      qt_meta_data_InnerLineEdit, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &InnerLineEdit::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *InnerLineEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *InnerLineEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_InnerLineEdit))
        return static_cast<void*>(const_cast< InnerLineEdit*>(this));
    return QLineEdit::qt_metacast(_clname);
}

int InnerLineEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLineEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: pressed(); break;
        case 1: editComplete(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void InnerLineEdit::pressed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
