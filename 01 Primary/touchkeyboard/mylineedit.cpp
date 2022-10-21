#include "mylineedit.h"


MyLineEdit::MyLineEdit(QWidget *parent) : QLineEdit(parent)
{
}


MyLineEdit::~MyLineEdit()
{
}


void MyLineEdit::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        emit clicked();
    }
}
