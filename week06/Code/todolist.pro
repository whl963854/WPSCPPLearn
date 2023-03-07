QT       += core gui
QT += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addnewgroupdialog.cpp \
    deadlinecalendar.cpp \
    descriptionedit.cpp \
    editlabel.cpp \
    groupitemwidget.cpp \
    grouplistwidget.cpp \
    itemgroupwidget.cpp \
    linewidget.cpp \
    main.cpp \
    newcalendar.cpp \
    newlineedit.cpp \
    noticecalendar.cpp \
    savelocate.cpp \
    tododata.cpp \
    todoitemsets.cpp \
    todoitemwidget.cpp \
    todolist.cpp \
    todolistwidget.cpp \
    todoutils.cpp

HEADERS += \
    addnewgroupdialog.h \
    deadlinecalendar.h \
    descriptionedit.h \
    editlabel.h \
    groupitemwidget.h \
    grouplistwidget.h \
    itemgroupwidget.h \
    linewidget.h \
    newcalendar.h \
    newlineedit.h \
    noticecalendar.h \
    savelocate.h \
    tododata.h \
    todoitemsets.h \
    todoitemwidget.h \
    todolist.h \
    todolistwidget.h \
    todoutils.h

FORMS += \
    addnewgroupdialog.ui \
    descriptionedit.ui \
    groupitemwidget.ui \
    itemgroupwidget.ui \
    linewidget.ui \
    noticecalendar.ui \
    todolist.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc \
    res.qrc

DISTFILES += \
    QSS/scrollbar.qss \
    todolist.pro.user
