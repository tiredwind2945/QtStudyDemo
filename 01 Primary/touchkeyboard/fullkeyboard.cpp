#include "fullkeyboard.h"
#include "ui_fullkeyboard.h"
#include <QDebug>


FullKeyboard::FullKeyboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FullKeyboard)
{
    ui->setupUi(this);

    inputLetters();
}


FullKeyboard::~FullKeyboard()
{
    delete ui;
}


// Signals and slots of buttons
void FullKeyboard::inputLetters()
{
    connect(ui->btnQ,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btnW,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btnE,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btnR,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btnT,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btnY,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btnU,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btnI,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btnO,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btnP,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btnA,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btnS,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btnD,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btnF,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btnG,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btnH,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btnJ,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btnK,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btnL,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btnZ,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btnX,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btnC,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btnV,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btnB,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btnN,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btnM,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btnSpace,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
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
    connect(ui->btnEqual,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btnHyphen,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btnLSquBra,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btnRSquBra,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btnComma,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btnPoint,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btnLBracket,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btnRBracket,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
    connect(ui->btnQuote,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
}


// Emit signal of switching keyboard
void FullKeyboard::on_btnSwitch_clicked()
{
    pageNum = 1;
    emit pageNumChange(pageNum);
}


// Switch another keyboard
void FullKeyboard::on_btnShift_clicked()
{
    //ui->btnShift->setIconSize(QSize(95,50));
    //ui->btnShift->setIcon(QIcon(":/icons/capSwitch.png"));
    QPushButton *button[26]
    {
        ui->btnA,ui->btnB,ui->btnC,ui->btnD,ui->btnE,ui->btnF,ui->btnG,ui->btnH,ui->btnI,ui->btnJ,
        ui->btnK,ui->btnL,ui->btnM,ui->btnN,ui->btnO,ui->btnP,ui->btnQ,ui->btnR,ui->btnS,ui->btnT,
        ui->btnU,ui->btnV,ui->btnW,ui->btnX,ui->btnY,ui->btnZ
    };

    if(isCap == false)
    {
        ui->btnShift->setStyleSheet("background-image: url(:/icons/capSwitch.png);background-color: #B3B3B3;");
        ui->btn0->setStyleSheet("background-image: url(:/icons/btnB0.png);");
        ui->btn1->setStyleSheet("background-image: url(:/icons/btnB1.png);");
        ui->btn2->setStyleSheet("background-image: url(:/icons/btnB2.png);");
        ui->btn3->setStyleSheet("background-image: url(:/icons/btnB3.png);");
        ui->btn4->setStyleSheet("background-image: url(:/icons/btnB4.png);");
        ui->btn5->setStyleSheet("background-image: url(:/icons/btnB5.png);");
        ui->btn6->setStyleSheet("background-image: url(:/icons/btnB6.png);");
        ui->btn7->setStyleSheet("background-image: url(:/icons/btnB7.png);");
        ui->btn8->setStyleSheet("background-image: url(:/icons/btnB8.png);");
        ui->btn9->setStyleSheet("background-image: url(:/icons/btnB9.png);");
        ui->btnEqual->setStyleSheet("background-image: url(:/icons/btnBEqual.png);");
        ui->btnHyphen->setStyleSheet("background-image: url(:/icons/btnBHyphen.png);");
        ui->btnLSquBra->setStyleSheet("background-image: url(:/icons/btnBLSquBra.png);");
        ui->btnRSquBra->setStyleSheet("background-image: url(:/icons/btnBRSquBra.png);");
        ui->btnLBracket->setStyleSheet("background-image: url(:/icons/btnBLBracket.png);");
        ui->btnRBracket->setStyleSheet("background-image: url(:/icons/btnBRBracket.png);");
        ui->btnComma->setStyleSheet("background-image: url(:/icons/btnBComma.png);");
        ui->btnPoint->setStyleSheet("background-image: url(:/icons/btnBPoint.png);");
        ui->btnQuote->setStyleSheet("background-image: url(:/icons/btnBQuote.png);");

        for(int i=0; i<26; i++)
        {
            button[i]->setText(button[i]->text().toUpper());
        }

        isCap = true;
    }
    else if (isCap == true)
    {
        ui->btnShift->setStyleSheet("background-image: url(:/icons/caseSwitch.png);background-color: #B3B3B3;");
        ui->btn0->setStyleSheet("background-image: url(:/icons/btnS0.png);");
        ui->btn1->setStyleSheet("background-image: url(:/icons/btnS1.png);");
        ui->btn2->setStyleSheet("background-image: url(:/icons/btnS2.png);");
        ui->btn3->setStyleSheet("background-image: url(:/icons/btnS3.png);");
        ui->btn4->setStyleSheet("background-image: url(:/icons/btnS4.png);");
        ui->btn5->setStyleSheet("background-image: url(:/icons/btnS5.png);");
        ui->btn6->setStyleSheet("background-image: url(:/icons/btnS6.png);");
        ui->btn7->setStyleSheet("background-image: url(:/icons/btnS7.png);");
        ui->btn8->setStyleSheet("background-image: url(:/icons/btnS8.png);");
        ui->btn9->setStyleSheet("background-image: url(:/icons/btnS9.png);");
        ui->btnEqual->setStyleSheet("background-image: url(:/icons/btnSEqual.png);");
        ui->btnHyphen->setStyleSheet("background-image: url(:/icons/btnSHyphen.png);");
        ui->btnLSquBra->setStyleSheet("background-image: url(:/icons/btnSLSquBra.png);");
        ui->btnRSquBra->setStyleSheet("background-image: url(:/icons/btnSRSquBra.png);");
        ui->btnLBracket->setStyleSheet("background-image: url(:/icons/btnSLBracket.png);");
        ui->btnRBracket->setStyleSheet("background-image: url(:/icons/btnSRBracket.png);");
        ui->btnComma->setStyleSheet("background-image: url(:/icons/btnSComma.png);");
        ui->btnPoint->setStyleSheet("background-image: url(:/icons/btnSPoint.png);");
        ui->btnQuote->setStyleSheet("background-image: url(:/icons/btnSQuote.png);");

        for(int i=0; i<26; i++)
        {
            button[i]->setText(button[i]->text().toLower());
        }

        isCap = false;
    }
}


// Implement function of buttons' click
void FullKeyboard::onClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    QString btn[20]
    {
        "btn0","btn1","btn2","btn3","btn4","btn5","btn6","btn7","btn8","btn9",
        "btnSpace","btnEqual","btnHyphen","btnLSquBra","btnRSquBra","btnComma",
        "btnPoint","btnLBracket","btnRBracket","btnQuote"
    };
    QString lowerCase[20]
    {
        "0","1","2","3","4","5","6","7","8","9"," ","=","_","[","]",",",".","(",")","\'"
    };
    QString upperCase[20]
    {
        "<","/","#","*","&","@","%","$","!","?"," ",">","\"","+","-",";",":","{","}","^"
    };

    if (button && button->text().isEmpty())
    {
        for(int i=0; i<20; i++)
        {
            if(button->objectName()==btn[i] && isCap==false)
            {
               inputText.append(lowerCase[i]);
            }
            else if(button->objectName()==btn[i] && isCap==true)
            {
                inputText.append(upperCase[i]);
            }
        }
    }else if(button){
        inputText.append(button->text());
    }
    ui->lineEdit->setText(inputText);
}


// Emit signal of canceling display keyboard
void FullKeyboard::on_btnCancel_clicked()
{
    emit cancelDisplay();
}


void FullKeyboard::on_lineEdit_textChanged(const QString &arg1)
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


// Emit signal of confirm button
void FullKeyboard::on_btnOk_clicked()
{
    emit sendText(ui->lineEdit->text());
}


// Move the cursor position
void FullKeyboard::on_btnLeft_clicked()
{
    cursorPosition = ui->lineEdit->cursorPosition();
    ui->lineEdit->setFocus();
    ui->lineEdit->setCursorPosition(--cursorPosition);
}


void FullKeyboard::on_btnRight_clicked()
{
    cursorPosition = ui->lineEdit->cursorPosition();
    ui->lineEdit->setFocus();
    ui->lineEdit->setCursorPosition(++cursorPosition);
}


void FullKeyboard::on_btnClr_clicked()
{
    inputText = "";
    ui->lineEdit->setText(inputText);
}


void FullKeyboard::on_btnDelete_clicked()
{
    cursorPosition = ui->lineEdit->cursorPosition();
    ui->lineEdit->setFocus();
    inputText.remove(cursorPosition-1,1);
    ui->lineEdit->setText(inputText);
    ui->lineEdit->setCursorPosition(cursorPosition-1);
}
