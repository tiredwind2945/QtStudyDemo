QT                  += core gui widgets
QMAKE_CXXFLAGS      += -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function
CONFIG              += c++11
TARGET              =  AnimatedButton
TEMPLATE            =  app
UI_DIR              += .ui
RCC_DIR             += .rcc
MOC_DIR             += .moc
OBJECTS_DIR         += .obj

SOURCES += \
        main.cpp \
        animatedbutton.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h \
        animatedbutton.h

FORMS += \
        mainwindow.ui

RESOURCES += \
        image.qrc
