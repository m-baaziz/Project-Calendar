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
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[6];
    char stringdata[109];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 20),
QT_MOC_LITERAL(2, 32, 0),
QT_MOC_LITERAL(3, 33, 28),
QT_MOC_LITERAL(4, 62, 18),
QT_MOC_LITERAL(5, 81, 26)
    },
    "MainWindow\0refreshProjectsModel\0\0"
    "refreshIndependentTasksModel\0"
    "showProjectsInMenu\0showIndependentTasksInMenu\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x0a,
       3,    0,   35,    2, 0x0a,
       4,    0,   36,    2, 0x0a,
       5,    0,   37,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->refreshProjectsModel(); break;
        case 1: _t->refreshIndependentTasksModel(); break;
        case 2: _t->showProjectsInMenu(); break;
        case 3: _t->showIndependentTasksInMenu(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
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
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
