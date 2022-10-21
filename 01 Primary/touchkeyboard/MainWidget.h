/*---------------------------------------------------------
*
* ABSTRACT: This file is the header file of MainWidget
* Class

* AUTHOR: wangjun
* E-MAIL: wangjun@efort.com.cn

* Copyright (c) RnD, Efort Intelligent Equipment Ltd. Corp.
* 2010 - 2019 All rights reserved

* Project created by QtCreator 2019-06-26T13:38:47
*
----------------------------------------------------------*/


#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "numerickeyboard.h"
#include "fullkeyboard.h"

namespace Ui {
class mainwidget;
}

class mainwidget : public QWidget
{
    Q_OBJECT

public:
    explicit mainwidget(QWidget *parent = nullptr);
    ~mainwidget();
    void initialize();

protected:
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);

private slots:
    void pageSwitch();
    void lineEditClicked();
    void btnCancelClicked();
    void sendText(QString text);
    void onClicked();

private:
    Ui::mainwidget *ui;

    NumericKeyboard *numkey;
    FullKeyboard *fullkey;
    QPoint mousePos;

signals:
    void blankClick();
};

#endif // MAINWIDGET_H
