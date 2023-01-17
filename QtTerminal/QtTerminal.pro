QT                  += core gui widgets xml printsupport
QMAKE_CXXFLAGS      += -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function
CONFIG              += c++11
TARGET              =  QtTerminal
TEMPLATE            =  app
UI_DIR              += .ui
RCC_DIR             += .rcc
MOC_DIR             += .moc
OBJECTS_DIR         += .obj

SOURCES += \
    QtTerminal.cpp \
    main.cpp \
    qcommandedit.cpp \
    qcommandtokenizer.cpp

HEADERS += \
    QtTerminal.h \
    qcommandedit.h \
    qcommandtokenizer.h

FORMS += \
    QtTerminal.ui

DEFINES += \
    QT_DISABLE_DEPRECATED_BEFORE=0x060000 \
    QT_RESTRICTED_CAST_FROM_ASCII \
    QT_NO_KEYWORDS
