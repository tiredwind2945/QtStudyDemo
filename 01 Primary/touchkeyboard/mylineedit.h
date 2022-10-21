/*---------------------------------------------------------
*
* ABSTRACT: This file is the header file of MyLineEdit
* Class

* AUTHOR: wangjun
* E-MAIL: wangjun@efort.com.cn

* Copyright (c) RnD, Efort Intelligent Equipment Ltd. Corp.
* 2010 - 2019 All rights reserved

* Project created by QtCreator 2019-06-26T13:38:47
*
----------------------------------------------------------*/


#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H
#include <QLineEdit>
#include <QMouseEvent>

class MyLineEdit : public QLineEdit
{
Q_OBJECT

public:
    explicit MyLineEdit(QWidget *parent = nullptr);
    ~MyLineEdit();

protected:
    virtual void mousePressEvent(QMouseEvent *e);

signals:
    void clicked();
};

#endif // MYLINEEDIT_H
