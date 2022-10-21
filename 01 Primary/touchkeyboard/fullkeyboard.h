/*---------------------------------------------------------
*
* ABSTRACT: This file is the header file of FullKeyboard
* Class

* AUTHOR: wangjun
* E-MAIL: wangjun@efort.com.cn

* Copyright (c) RnD, Efort Intelligent Equipment Ltd. Corp.
* 2010 - 2019 All rights reserved

* Project created by QtCreator 2019-06-26T13:38:47
*
----------------------------------------------------------*/

#ifndef FULLKEYBOARD_H
#define FULLKEYBOARD_H

#include <QWidget>

static bool isCap = false;

namespace Ui {
class FullKeyboard;
}

class  FullKeyboard : public QWidget
{
    Q_OBJECT

public:
    explicit FullKeyboard(QWidget *parent = nullptr);
    ~FullKeyboard();

    void inputLetters();

private slots:
    void on_btnSwitch_clicked();
    void on_btnShift_clicked();
    void onClicked();
    void on_btnCancel_clicked();
    void on_lineEdit_textChanged(const QString &arg1);
    void on_btnOk_clicked();
    void on_btnLeft_clicked();
    void on_btnRight_clicked();
    void on_btnClr_clicked();
    void on_btnDelete_clicked();

private:
    Ui::FullKeyboard *ui;
    int pageNum;    // mark keyborads as 0 and 1
    QString inputText;
    int cursorPosition;

signals:
    void pageNumChange(int num);    // when keyboard is change to another
    void cancelDisplay();
    void sendText(QString text);
};

#endif // FULLKEYBOARD_H
