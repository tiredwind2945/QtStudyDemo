#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "animatedbutton.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    AnimatedButton *m_btn = new AnimatedButton(":/clean_Hover.png",":/clean_Leave.png",this);
    m_btn->setGeometry(30,30,95,95);
}

MainWindow::~MainWindow()
{
    delete ui;
}
