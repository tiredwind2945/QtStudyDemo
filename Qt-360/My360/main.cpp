#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <tr1/memory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // set encoding
    QTextCodec *codec = QTextCodec::codecForName("utf8");
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);

    MainWindow* w(MainWindow::getInstance());
    w->show();
    MainWindow* w1(MainWindow::getInstance());
    MainWindow* w2(MainWindow::getInstance());

    w1->show();
    w2->show();

    return a.exec();
}
