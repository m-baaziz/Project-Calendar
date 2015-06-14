/****************************************************************************
** Meta object code from reading C++ file 'GUI-Task.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ProjectCalendar/GUI-Task.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GUI-Task.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_NewTaskB_t {
    QByteArrayData data[3];
    char stringdata[23];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_NewTaskB_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_NewTaskB_t qt_meta_stringdata_NewTaskB = {
    {
QT_MOC_LITERAL(0, 0, 8),
QT_MOC_LITERAL(1, 9, 11),
QT_MOC_LITERAL(2, 21, 0)
    },
    "NewTaskB\0popTaskForm\0\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NewTaskB[] = {

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

void NewTaskB::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NewTaskB *_t = static_cast<NewTaskB *>(_o);
        switch (_id) {
        case 0: _t->popTaskForm(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject NewTaskB::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_NewTaskB.data,
      qt_meta_data_NewTaskB,  qt_static_metacall, 0, 0}
};


const QMetaObject *NewTaskB::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NewTaskB::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NewTaskB.stringdata))
        return static_cast<void*>(const_cast< NewTaskB*>(this));
    return QPushButton::qt_metacast(_clname);
}

int NewTaskB::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
struct qt_meta_stringdata_NewTaskForm_t {
    QByteArrayData data[5];
    char stringdata[46];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_NewTaskForm_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_NewTaskForm_t qt_meta_stringdata_NewTaskForm = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 7),
QT_MOC_LITERAL(2, 20, 0),
QT_MOC_LITERAL(3, 21, 17),
QT_MOC_LITERAL(4, 39, 5)
    },
    "NewTaskForm\0addTask\0\0showTasksToChoose\0"
    "index\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NewTaskForm[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x0a,
       3,    1,   25,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,

       0        // eod
};

void NewTaskForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NewTaskForm *_t = static_cast<NewTaskForm *>(_o);
        switch (_id) {
        case 0: _t->addTask(); break;
        case 1: _t->showTasksToChoose((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject NewTaskForm::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_NewTaskForm.data,
      qt_meta_data_NewTaskForm,  qt_static_metacall, 0, 0}
};


const QMetaObject *NewTaskForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NewTaskForm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NewTaskForm.stringdata))
        return static_cast<void*>(const_cast< NewTaskForm*>(this));
    return QDialog::qt_metacast(_clname);
}

int NewTaskForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
struct qt_meta_stringdata_AddTaskForm_t {
    QByteArrayData data[3];
    char stringdata[22];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_AddTaskForm_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_AddTaskForm_t qt_meta_stringdata_AddTaskForm = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 7),
QT_MOC_LITERAL(2, 20, 0)
    },
    "AddTaskForm\0addTask\0\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AddTaskForm[] = {

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

void AddTaskForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AddTaskForm *_t = static_cast<AddTaskForm *>(_o);
        switch (_id) {
        case 0: _t->addTask(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject AddTaskForm::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_AddTaskForm.data,
      qt_meta_data_AddTaskForm,  qt_static_metacall, 0, 0}
};


const QMetaObject *AddTaskForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AddTaskForm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AddTaskForm.stringdata))
        return static_cast<void*>(const_cast< AddTaskForm*>(this));
    return QDialog::qt_metacast(_clname);
}

int AddTaskForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
struct qt_meta_stringdata_AddTaskToProjectForm_t {
    QByteArrayData data[3];
    char stringdata[31];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_AddTaskToProjectForm_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_AddTaskToProjectForm_t qt_meta_stringdata_AddTaskToProjectForm = {
    {
QT_MOC_LITERAL(0, 0, 20),
QT_MOC_LITERAL(1, 21, 7),
QT_MOC_LITERAL(2, 29, 0)
    },
    "AddTaskToProjectForm\0addTask\0\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AddTaskToProjectForm[] = {

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

void AddTaskToProjectForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AddTaskToProjectForm *_t = static_cast<AddTaskToProjectForm *>(_o);
        switch (_id) {
        case 0: _t->addTask(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject AddTaskToProjectForm::staticMetaObject = {
    { &AddTaskForm::staticMetaObject, qt_meta_stringdata_AddTaskToProjectForm.data,
      qt_meta_data_AddTaskToProjectForm,  qt_static_metacall, 0, 0}
};


const QMetaObject *AddTaskToProjectForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AddTaskToProjectForm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AddTaskToProjectForm.stringdata))
        return static_cast<void*>(const_cast< AddTaskToProjectForm*>(this));
    return AddTaskForm::qt_metacast(_clname);
}

int AddTaskToProjectForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AddTaskForm::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_AddTaskToCompositeTaskForm_t {
    QByteArrayData data[3];
    char stringdata[37];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_AddTaskToCompositeTaskForm_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_AddTaskToCompositeTaskForm_t qt_meta_stringdata_AddTaskToCompositeTaskForm = {
    {
QT_MOC_LITERAL(0, 0, 26),
QT_MOC_LITERAL(1, 27, 7),
QT_MOC_LITERAL(2, 35, 0)
    },
    "AddTaskToCompositeTaskForm\0addTask\0\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AddTaskToCompositeTaskForm[] = {

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

void AddTaskToCompositeTaskForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AddTaskToCompositeTaskForm *_t = static_cast<AddTaskToCompositeTaskForm *>(_o);
        switch (_id) {
        case 0: _t->addTask(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject AddTaskToCompositeTaskForm::staticMetaObject = {
    { &AddTaskForm::staticMetaObject, qt_meta_stringdata_AddTaskToCompositeTaskForm.data,
      qt_meta_data_AddTaskToCompositeTaskForm,  qt_static_metacall, 0, 0}
};


const QMetaObject *AddTaskToCompositeTaskForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AddTaskToCompositeTaskForm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AddTaskToCompositeTaskForm.stringdata))
        return static_cast<void*>(const_cast< AddTaskToCompositeTaskForm*>(this));
    return AddTaskForm::qt_metacast(_clname);
}

int AddTaskToCompositeTaskForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AddTaskForm::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_TaskInfo_t {
    QByteArrayData data[1];
    char stringdata[10];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_TaskInfo_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_TaskInfo_t qt_meta_stringdata_TaskInfo = {
    {
QT_MOC_LITERAL(0, 0, 8)
    },
    "TaskInfo\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TaskInfo[] = {

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

void TaskInfo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject TaskInfo::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_TaskInfo.data,
      qt_meta_data_TaskInfo,  qt_static_metacall, 0, 0}
};


const QMetaObject *TaskInfo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TaskInfo::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TaskInfo.stringdata))
        return static_cast<void*>(const_cast< TaskInfo*>(this));
    return QDialog::qt_metacast(_clname);
}

int TaskInfo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
