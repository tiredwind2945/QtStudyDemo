#include "skyplotwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SkyplotWidget w;
    w.show();

    return a.exec();
}
