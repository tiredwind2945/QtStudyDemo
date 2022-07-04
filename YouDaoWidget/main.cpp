#include "youdaowidget.h"
#include "stylesheetmanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    YouDaoWidget w;
    w.show();

    StyleSheetManager manager;
    manager.loadDir(":/style/");

    return a.exec();
}
