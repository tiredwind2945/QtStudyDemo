#include "searchlineedit.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SearchLineEdit w;
    w.show();

    return a.exec();
}
