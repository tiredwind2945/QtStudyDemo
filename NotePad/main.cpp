#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* w = MainWindow::newInstance();
    int ret = -1;
    if(w != nullptr)
    {
        w->show();;
        a.exec();
    }
    delete w;
    return ret;
}
