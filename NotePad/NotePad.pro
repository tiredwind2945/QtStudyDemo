QT       += core gui printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Note
TEMPLATE = app

SOURCES += \
    main.cpp\
    MainWindowUI.cpp \
    MainwWindowSlots.cpp \
    FindDialog.cpp \
    ReplaceDialog.cpp \
    AboutDialog.cpp \
    AppConfig.cpp

HEADERS  += \
    MainWindow.h \
    FindDialog.h \
    ReplaceDialog.h \
    AboutDialog.h \
    AppConfig.h

RESOURCES += \
    res.qrc

# Add icon to application
 RC_ICONS = icon.ico
