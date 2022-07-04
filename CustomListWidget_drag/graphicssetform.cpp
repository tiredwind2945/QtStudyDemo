#include "graphicssetform.h"
#include "ui_graphicssetform.h"

GraphicsSetForm::GraphicsSetForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GraphicsSetForm)
{
    ui->setupUi(this);
}

GraphicsSetForm::~GraphicsSetForm()
{
    delete ui;
}

void GraphicsSetForm::setName(QString text)
{
    ui->setBt->setText(text);
}

void GraphicsSetForm::on_setBt_clicked()
{

}


