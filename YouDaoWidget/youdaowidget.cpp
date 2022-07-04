#include "youdaowidget.h"
#include "ui_youdaowidget.h"

const static int pos_min_x = 0;
const static int pos_max_x = 654+184;
const static int pos_min_y = 0;
const static int pos_max_y = 60;

YouDaoWidget::YouDaoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::YouDaoWidget)
{
    ui->setupUi(this);

    //设置标题栏隐藏
    setWindowFlags(Qt::FramelessWindowHint);
    resize(800, 600);
}


YouDaoWidget::~YouDaoWidget()
{
    delete ui;
}


void YouDaoWidget::mousePressEvent(QMouseEvent *event)
{
    mousePosition = event->pos();
    //只对标题栏范围内的鼠标事件进行处理
    if (mousePosition.x()<=pos_min_x)
    return;
    if ( mousePosition.x()>=pos_max_x)
    return;
    if (mousePosition.y()<=pos_min_y )
    return;
    if (mousePosition.y()>=pos_max_y)
    return;
    isMousePressed = true;

}


void YouDaoWidget::mouseMoveEvent(QMouseEvent *event)
{
    if ( isMousePressed==true )
    {
    QPoint movePot = event->globalPos() - mousePosition;
    move(movePot);
    }
}


void YouDaoWidget::mouseReleaseEvent(QMouseEvent *)
{
    isMousePressed = false;
}


void YouDaoWidget::on_btn_close_clicked()
{
    close();
}


void YouDaoWidget::on_btn_min_clicked()
{
    showMinimized();
}
