#include "MainWidget.h"
#include "ui_mainwidget.h"


mainwidget::mainwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainwidget)
{
    ui->setupUi(this);

    initialize();
}


mainwidget::~mainwidget()
{
    delete ui;
}


void mainwidget::initialize()
{
    numkey = new NumericKeyboard(this);
    numkey->move(184,230);
    numkey->hide();
    fullkey = new FullKeyboard(this);
    fullkey->move(4,230);
    fullkey->hide();

    connect(numkey,SIGNAL(pageNumChange(int)),this,SLOT(pageSwitch()));
    connect(fullkey,SIGNAL(pageNumChange(int)),this,SLOT(pageSwitch()));
    connect(ui->lineEdit,SIGNAL(clicked()),this,SLOT(lineEditClicked()));
    connect(numkey,SIGNAL(cancelDisplay()),this,SLOT(btnCancelClicked()));
    connect(fullkey,SIGNAL(cancelDisplay()),this,SLOT(btnCancelClicked()));
    connect(numkey,SIGNAL(sendText(QString)),this,SLOT(sendText(QString)));
    connect(fullkey,SIGNAL(sendText(QString)),this,SLOT(sendText(QString)));
    connect(this, SIGNAL(clicked()), this, SLOT(onClicked()));
}


//Swicth keyboard
void mainwidget::pageSwitch()
{
    if(numkey->isHidden())
    {
        numkey->show();
        fullkey->hide();
    }
    else if (fullkey->isHidden())
    {
        fullkey->show();
        numkey->hide();
    }
}


// Display keyboard when click lineEdit
void mainwidget::lineEditClicked()
{
    numkey->show();
}


// Hide keyboard when click cancel button on each of the keyboards
void mainwidget::btnCancelClicked()
{
    if(numkey->isHidden())
    {
        fullkey->hide();
    }
    else{
        numkey->hide();
    }
}


// Send texts on keyboards to lineedit on mainwidget
void mainwidget::sendText(QString text)
{
    ui->lineEdit->setText(text);
}


// Hide keyboard when click blank space
void mainwidget::onClicked()
{
   numkey->hide();
   fullkey->hide();
}


void mainwidget::mousePressEvent(QMouseEvent *ev)
{
    mousePos = QPoint(ev->x(), ev->y());
}


void mainwidget::mouseReleaseEvent(QMouseEvent *ev)
{
    if(mousePos == QPoint(ev->x(), ev->y()) && ev->y()<230)
    {
        emit onClicked();
    }
}
