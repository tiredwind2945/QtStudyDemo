#include "searchedit.h"
#include "ui_searchedit.h"

SearchEdit::SearchEdit(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SearchEdit)
{
    ui->setupUi(this);
    init();
}


SearchEdit::~SearchEdit()
{
    delete ui;
}


void SearchEdit::init()
{
    //1. 设置查询edit
    ui->line_search->setProperty("frame", false);
    //2. 设置左右侧半圆
    ui->label_left->setProperty("style", "left-semicircle");
    ui->label_right->setProperty("style", "right-semicircle");

    //3. 设置翻译模式 英汉互译
    ui->label_model->setProperty("style", "bg-white");

    //4. 设置间隔性
    ui->label_vline->setProperty("style", "bg-white");

    //5. 设置向下按钮
    ui->btn_drop->setProperty("style", "bg-white");

    //6. 设置查询按钮
    ui->btn_search->setProperty("style", "bg-white");
}
