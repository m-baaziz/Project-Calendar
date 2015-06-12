/****************************************************************************
** Meta object code from reading C++ file 'GUI-Architecture.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ProjectCalendar/GUI-Architecture.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GUI-Architecture.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ManageWeeks_t {
    QByteArrayData data[4];
    char stringdata[36];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_ManageWeeks_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_ManageWeeks_t qt_meta_stringdata_ManageWeeks = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 8),
QT_MOC_LITERAL(2, 21, 0),
QT_MOC_LITERAL(3, 22, 12)
    },
    "ManageWeeks\0nextWeek\0\0previousWeek\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ManageWeeks[] = {

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
       3,    0,   25,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ManageWeeks::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ManageWeeks *_t = static_cast<ManageWeeks *>(_o);
        switch (_id) {
        case 0: _t->nextWeek(); break;
        case 1: _t->previousWeek(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject ManageWeeks::staticMetaObject = {
    { &QDateEdit::staticMetaObject, qt_meta_stringdata_ManageWeeks.data,
      qt_meta_data_ManageWeeks,  qt_static_metacall, 0, 0}
};


const QMetaObject *ManageWeeks::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ManageWeeks::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ManageWeeks.stringdata))
        return static_cast<void*>(const_cast< ManageWeeks*>(this));
    return QDateEdit::qt_metacast(_clname);
}

int ManageWeeks::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDateEdit::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_Week_t {
    QByteArrayData data[3];
    char stringdata[18];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Week_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Week_t qt_meta_stringdata_Week = {
    {
QT_MOC_LITERAL(0, 0, 4),
QT_MOC_LITERAL(1, 5, 10),
QT_MOC_LITERAL(2, 16, 0)
    },
    "Week\0updateWeek\0\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Week[] = {

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

void Week::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Week *_t = static_cast<Week *>(_o);
        switch (_id) {
        case 0: _t->updateWeek(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Week::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Week.data,
      qt_meta_data_Week,  qt_static_metacall, 0, 0}
};


const QMetaObject *Week::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Week::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Week.stringdata))
        return static_cast<void*>(const_cast< Week*>(this));
    return QWidget::qt_metacast(_clname);
}

int Week::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_MyComboBox_t {
    QByteArrayData data[4];
    char stringdata[42];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_MyComboBox_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_MyComboBox_t qt_meta_stringdata_MyComboBox = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 22),
QT_MOC_LITERAL(2, 34, 0),
QT_MOC_LITERAL(3, 35, 5)
    },
    "MyComboBox\0handleSelectionChanged\0\0"
    "index\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyComboBox[] = {

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
       1,    1,   19,    2, 0x0a,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void MyComboBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MyComboBox *_t = static_cast<MyComboBox *>(_o);
        switch (_id) {
        case 0: _t->handleSelectionChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MyComboBox::staticMetaObject = {
    { &QComboBox::staticMetaObject, qt_meta_stringdata_MyComboBox.data,
      qt_meta_data_MyComboBox,  qt_static_metacall, 0, 0}
};


const QMetaObject *MyComboBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyComboBox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MyComboBox.stringdata))
        return static_cast<void*>(const_cast< MyComboBox*>(this));
    return QComboBox::qt_metacast(_clname);
}

int MyComboBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QComboBox::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_EventForm_t {
    QByteArrayData data[5];
    char stringdata[52];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_EventForm_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_EventForm_t qt_meta_stringdata_EventForm = {
    {
QT_MOC_LITERAL(0, 0, 9),
QT_MOC_LITERAL(1, 10, 10),
QT_MOC_LITERAL(2, 21, 0),
QT_MOC_LITERAL(3, 22, 22),
QT_MOC_LITERAL(4, 45, 5)
    },
    "EventForm\0addElement\0\0handleSelectionChanged\0"
    "index\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EventForm[] = {

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
    QMetaType::Void, QMetaType::Int,    4,

       0        // eod
};

void EventForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EventForm *_t = static_cast<EventForm *>(_o);
        switch (_id) {
        case 0: _t->addElement(); break;
        case 1: _t->handleSelectionChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject EventForm::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_EventForm.data,
      qt_meta_data_EventForm,  qt_static_metacall, 0, 0}
};


const QMetaObject *EventForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EventForm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EventForm.stringdata))
        return static_cast<void*>(const_cast< EventForm*>(this));
    return QWidget::qt_metacast(_clname);
}

int EventForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[13];
    char stringdata[235];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 17),
QT_MOC_LITERAL(2, 29, 0),
QT_MOC_LITERAL(3, 30, 20),
QT_MOC_LITERAL(4, 51, 28),
QT_MOC_LITERAL(5, 80, 24),
QT_MOC_LITERAL(6, 105, 18),
QT_MOC_LITERAL(7, 124, 26),
QT_MOC_LITERAL(8, 151, 22),
QT_MOC_LITERAL(9, 174, 22),
QT_MOC_LITERAL(10, 197, 3),
QT_MOC_LITERAL(11, 201, 19),
QT_MOC_LITERAL(12, 221, 12)
    },
    "MainWindow\0refreshTasksModel\0\0"
    "refreshProjectsModel\0refreshIndependentTasksModel\0"
    "refreshProjectsTreeModel\0showProjectsInMenu\0"
    "showIndependentTasksInMenu\0"
    "showProjectsTreeInMenu\0showProjectContextMenu\0"
    "pos\0showTaskContextMenu\0showCalendar\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x0a,
       3,    0,   65,    2, 0x0a,
       4,    0,   66,    2, 0x0a,
       5,    0,   67,    2, 0x0a,
       6,    0,   68,    2, 0x0a,
       7,    0,   69,    2, 0x0a,
       8,    0,   70,    2, 0x0a,
       9,    1,   71,    2, 0x0a,
      11,    1,   74,    2, 0x0a,
      12,    0,   77,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,   10,
    QMetaType::Void, QMetaType::QPoint,   10,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->refreshTasksModel(); break;
        case 1: _t->refreshProjectsModel(); break;
        case 2: _t->refreshIndependentTasksModel(); break;
        case 3: _t->refreshProjectsTreeModel(); break;
        case 4: _t->showProjectsInMenu(); break;
        case 5: _t->showIndependentTasksInMenu(); break;
        case 6: _t->showProjectsTreeInMenu(); break;
        case 7: _t->showProjectContextMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 8: _t->showTaskContextMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 9: _t->showCalendar(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
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
struct qt_meta_stringdata_EditAssociationConstraint_t {
    QByteArrayData data[4];
    char stringdata[61];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_EditAssociationConstraint_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_EditAssociationConstraint_t qt_meta_stringdata_EditAssociationConstraint = {
    {
QT_MOC_LITERAL(0, 0, 25),
QT_MOC_LITERAL(1, 26, 14),
QT_MOC_LITERAL(2, 41, 0),
QT_MOC_LITERAL(3, 42, 17)
    },
    "EditAssociationConstraint\0addAssociation\0"
    "\0removeAssociation\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EditAssociationConstraint[] = {

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
       3,    0,   25,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void EditAssociationConstraint::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EditAssociationConstraint *_t = static_cast<EditAssociationConstraint *>(_o);
        switch (_id) {
        case 0: _t->addAssociation(); break;
        case 1: _t->removeAssociation(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject EditAssociationConstraint::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_EditAssociationConstraint.data,
      qt_meta_data_EditAssociationConstraint,  qt_static_metacall, 0, 0}
};


const QMetaObject *EditAssociationConstraint::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EditAssociationConstraint::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EditAssociationConstraint.stringdata))
        return static_cast<void*>(const_cast< EditAssociationConstraint*>(this));
    return QDialog::qt_metacast(_clname);
}

int EditAssociationConstraint::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
