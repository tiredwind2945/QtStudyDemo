QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .

# Input
HEADERS += basewidget.h \
           bottomwidget.h \
           buttonwithname.h \
           centerwidget.h \
           closebutton.h \
           fontwidget.h \
           loginbutton.h \
           mainwindow.h \
           nunberwidget.h \
           titlebar.h \
    lowertopwidget.h \
    lowerbottomwidget.h \
    abslowercenterwidget.h \
    optimizecenterwidget.h \
    safecheckcenterwidget.h \
    cleancenterwidget.h \
    lowerspeedbutton.h \
    lowersafecheckbutton.h \
    common.h
FORMS +=
SOURCES += basewidget.cpp \
           bottomwidget.cpp \
           buttonwithname.cpp \
           centerwidget.cpp \
           closebutton.cpp \
           fontwidget.cpp \
           loginbutton.cpp \
           main.cpp \
           mainwindow.cpp \
           nunberwidget.cpp \
           titlebar.cpp \
    lowertopwidget.cpp \
    lowerbottomwidget.cpp \
    abslowercenterwidget.cpp \
    optimizecenterwidget.cpp \
    safecheckcenterwidget.cpp \
    cleancenterwidget.cpp \
    lowerspeedbutton.cpp \
    lowersafecheckbutton.cpp

RESOURCES += \
    ../resource/img.qrc
