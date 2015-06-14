/****************************************************************************
** Meta object code from reading C++ file 'GUI-Project.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ProjectCalendar/GUI-Project.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GUI-Project.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_NewProjectForm_t {
    QByteArrayData data[3];
    char stringdata[28];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_NewProjectForm_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_NewProjectForm_t qt_meta_stringdata_NewProjectForm = {
    {
QT_MOC_LITERAL(0, 0, 14),
QT_MOC_LITERAL(1, 15, 10),
QT_MOC_LITERAL(2, 26, 0)
    },
    "NewProjectForm\0addProject\0\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NewProjectForm[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void NewProjectForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NewProjectForm *_t = static_cast<NewProjectForm *>(_o);
        switch (_id) {
        case 0: _t->addProject(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject NewProjectForm::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_NewProjectForm.data,
      qt_meta_data_NewProjectForm,  qt_static_metacall, 0, 0}
};


const QMetaObject *NewProjectForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NewProjectForm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NewProjectForm.stringdata))
        return static_cast<void*>(const_cast< NewProjectForm*>(this));
    return QDialog::qt_metacast(_clname);
}

int NewProjectForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_NewProjectB_t {
    QByteArrayData data[3];
    char stringdata[29];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_NewProjectB_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_NewProjectB_t qt_meta_stringdata_NewProjectB = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 14),
QT_MOC_LITERAL(2, 27, 0)
    },
    "NewProjectB\0popProjectForm\0\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NewProjectB[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void NewProjectB::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NewProjectB *_t = static_cast<NewProjectB *>(_o);
        switch (_id) {
        case 0: _t->popProjectForm(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject NewProjectB::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_NewProjectB.data,
      qt_meta_data_NewProjectB,  qt_static_metacall, 0, 0}
};


const QMetaObject *NewProjectB::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NewProjectB::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NewProjectB.stringdata))
        return static_cast<void*>(const_cast< NewProjectB*>(this));
    return QPushButton::qt_metacast(_clname);
}

int NewProjectB::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_ProjectInfo_t {
    QByteArrayData data[1];
    char stringdata[13];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_ProjectInfo_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_ProjectInfo_t qt_meta_stringdata_ProjectInfo = {
    {
QT_MOC_LITERAL(0, 0, 11)
    },
    "ProjectInfo\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ProjectInfo[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void ProjectInfo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject ProjectInfo::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ProjectInfo.data,
      qt_meta_data_ProjectInfo,  qt_static_metacall, 0, 0}
};


const QMetaObject *ProjectInfo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ProjectInfo::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ProjectInfo.stringdata))
        return static_cast<void*>(const_cast< ProjectInfo*>(this));
    return QDialog::qt_metacast(_clname);
}

int ProjectInfo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
