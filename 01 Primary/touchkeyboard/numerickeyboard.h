/*---------------------------------------------------------
*
* ABSTRACT: This file is the header file of NumericKeyboard
* Class

* AUTHOR: wangjun
* E-MAIL: wangjun@efort.com.cn

* Copyright (c) RnD, Efort Intelligent Equipment Ltd. Corp.
* 2010 - 2019 All rights reserved

* Project created by QtCreator 2019-06-26T13:38:47
*
----------------------------------------------------------*/

#ifndef NUMERICKEYBOARD_H
#define NUMERICKEYBOARD_H

#include <QWidget>

namespace Ui {
class NumericKeyboard;
}

class NumericKeyboard : public QWidget
{
    Q_OBJECT

public:
    explicit NumericKeyboard(QWidget *parent = nullptr);
    ~NumericKeyboard();
    void inputNums();


private slots:
    void on_btnSwitch_clicked();
    void onClicked();
    void on_lineEdit_textChanged(const QString &arg1);
    void on_btnCancel_clicked();
    void on_btnOk_clicked();
    void on_btnLeft_clicked();
    void on_btnRight_clicked();
    void on_btnClear_clicked();
    void on_btnDelete_clicked();

private:
    Ui::NumericKeyboard *ui;
    int pageNum;    // mark keyborads as 0 and 1
    QString inputText;
    int cursorPosition;

signals:
    void pageNumChange(int num);    // when keyboard is change to another
    void cancelDisplay();
    void sendText(QString text);
};

#endif // NUMERICKEYBOARD_H
