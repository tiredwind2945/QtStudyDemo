#include "graphicssetform.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   GraphicsSetForm *w1 = new GraphicsSetForm();
   w1->setName("test1");
   QListWidgetItem *item1 = new QListWidgetItem();
   item1->setSizeHint(QSize(200,50));
   ui->listWidget->addItem(item1);
   ui->listWidget->setItemWidget(item1,w1);


   GraphicsSetForm *w2 = new GraphicsSetForm();
   w2->setName("test2");
   QListWidgetItem *item2 = new QListWidgetItem();
   item2->setSizeHint(QSize(200,50));
   ui->listWidget->addItem(item2);
   ui->listWidget->setItemWidget(item2,w2);



   GraphicsSetForm *w3= new GraphicsSetForm();
   w3->setName("test3");
   QListWidgetItem *item3 = new QListWidgetItem();
   item3->setSizeHint(QSize(200,50));
   ui->listWidget->addItem(item3);
   ui->listWidget->setItemWidget(item3,w3);


   GraphicsSetForm *w4 = new GraphicsSetForm();
   w4->setName("test4");
   QListWidgetItem *item4 = new QListWidgetItem();
   item4->setSizeHint(QSize(200,50));
   ui->listWidget->addItem(item4);
   ui->listWidget->setItemWidget(item4,w4);

   GraphicsSetForm *w5 = new GraphicsSetForm();
   w5->setName("test5");
   QListWidgetItem *item5 = new QListWidgetItem();
   item5->setSizeHint(QSize(200,50));
   ui->listWidget->addItem(item5);
   ui->listWidget->setItemWidget(item5,w5);








}

MainWindow::~MainWindow()
{
    delete ui;
}
