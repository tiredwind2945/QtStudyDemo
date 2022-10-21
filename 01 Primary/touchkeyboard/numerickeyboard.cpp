#include "numerickeyboard.h"
#include "ui_numerickeyboard.h"


NumericKeyboard::NumericKeyboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NumericKeyboard)
{
    ui->setupUi(this);

     inputNums();

     ui->btnA->setEnabled(false);
     ui->btnB->setEnabled(false);
     ui->btnC->setEnabled(false);
     ui->btnD->setEnabled(false);
     ui->btnE->setEnabled(false);
     ui->btnF->setEnabled(false);
}


NumericKeyboard::~NumericKeyboard()
{
    delete ui;
}


// Signals and slots of bttons
void NumericKeyboard::inputNums()
{
    connect(ui->btn0,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btn1,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btn2,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btn3,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btn4,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btn5,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btn6,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btn7,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btn8,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btn9,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btnA,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btnB,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btnC,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btnD,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btnE,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btnF,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btnSign,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btnPoint,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btnHEX,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btnDEC,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btnBIN,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
}


// Emit signal of switching keyboard
void NumericKeyboard::on_btnSwitch_clicked()
{
   pageNum = 0;
   emit pageNumChange(pageNum);
}


// Implement function of buttons' click
void NumericKeyboard::onClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    QList<QAbstractButton*> buttonsList = ui->buttonGroup2->buttons();

    if(button->objectName()=="btnHEX")
    {
        foreach (QAbstractButton *btn, buttonsList)
        {
            ((QPushButton*)btn)->setEnabled(true);
        }
        ui->btnSign->setEnabled(false);
        ui->btnPoint->setEnabled(false);
    }
    else if(button->objectName()=="btnDEC")
    {
        foreach (QAbstractButton *btn, buttonsList)
        {
            ((QPushButton*)btn)->setEnabled(true);
        }
        ui->btnA->setEnabled(false);
        ui->btnB->setEnabled(false);
        ui->btnC->setEnabled(false);
        ui->btnD->setEnabled(false);
        ui->btnE->setEnabled(false);
        ui->btnF->setEnabled(false);
    }
    else if(button->objectName()=="btnBIN")
    {

        foreach (QAbstractButton *btn, buttonsList)
        {
            ((QPushButton*)btn)->setEnabled(true);
            if(btn->objectName()=="btn1" | btn->objectName()=="btn0")
            {
                continue;
            }
            ((QPushButton*)btn)->setEnabled(false);
        }
    }
    else
    {
        inputText.append(button->text());
        ui->lineEdit->setText(inputText);
    }
}


void NumericKeyboard::on_lineEdit_textChanged(const QString &arg1)
{
    if(ui->lineEdit->text().isEmpty())
    {
        ui->btnOk->setEnabled(false);
        ui->btnOk->setStyleSheet("background-color: rgba(204,204,204,50);");
    }
    else if(!(ui->lineEdit->text().isEmpty()))
    {
        ui->btnOk->setEnabled(true);
        ui->btnOk->setStyleSheet("background-color: #00BD00;");
    }
}


// Emit signal of canceling display keyboard
void NumericKeyboard::on_btnCancel_clicked()
{
    emit cancelDisplay();
}


// Emit signal of confirm button
void NumericKeyboard::on_btnOk_clicked()
{
    emit sendText(ui->lineEdit->text());
}


// Move the cursor position
void NumericKeyboard::on_btnLeft_clicked()
{
    cursorPosition = ui->lineEdit->cursorPosition();
    ui->lineEdit->setFocus();
    ui->lineEdit->setCursorPosition(--cursorPosition);
}


void NumericKeyboard::on_btnRight_clicked()
{
    cursorPosition = ui->lineEdit->cursorPosition();
    ui->lineEdit->setFocus();
    ui->lineEdit->setCursorPosition(++cursorPosition);
}


void NumericKeyboard::on_btnClear_clicked()
{
    inputText = "";
    ui->lineEdit->setText(inputText);
}


void NumericKeyboard::on_btnDelete_clicked()
{
    cursorPosition = ui->lineEdit->cursorPosition();
    ui->lineEdit->setFocus();
    inputText.remove(cursorPosition-1,1);
    ui->lineEdit->setText(inputText);
    ui->lineEdit->setCursorPosition(cursorPosition-1);
}
