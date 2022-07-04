#include "graphicssetform.h"
#include "yylistwidget.h"

#include <QApplication>
#include <QDrag>
#include <QKeyEvent>
#include <QMimeData>
#include "QDebug"

YYListWidget::YYListWidget(QWidget *parent) : QListWidget(parent)
{

   this->setAcceptDrops(true);
   this->setDragEnabled(true);
}

YYListWidget::~YYListWidget()
{

}

void YYListWidget::dragMoveEvent(QDragMoveEvent *event)
{

        oldHighlightedRow = theHighlightedRow;
        theHighlightedRow = indexAt(event->pos() - QPoint(0, 50)).row();

        //offset() = 19 = 40 / 2 - 1，其中40是行高
        if(event->pos().y() >= 50){

            if(oldHighlightedRow != theHighlightedRow){
                //刷新旧区域使dropIndicator消失
                update(model()->index(oldHighlightedRow, 0));
                update(model()->index(oldHighlightedRow + 1, 0));

                //刷新新区域使dropIndicator显示
                update(model()->index(theHighlightedRow, 0));
                update(model()->index(theHighlightedRow + 1, 0));
            }else{
                update(model()->index(theHighlightedRow, 0));
                update(model()->index(theHighlightedRow + 1, 0));
            }

            theInsertRow = theHighlightedRow + 1;
        }else{
            theHighlightedRow = -1;
            update(model()->index(0, 0));
            update(model()->index(1, 0));
            theInsertRow = 0;
        }

        event->setDropAction(Qt::MoveAction);
        event->accept();

}

// 接收放置后添加一项
void YYListWidget::dropEvent(QDropEvent *event)

{
     qDebug()<<"dropEvent";
     GraphicsSetForm *w=(GraphicsSetForm *)this->itemWidget(this->item(this->currentRow()));

     QPoint  endPos = event->pos();//得到鼠标移动到的坐标
     QListWidgetItem *itemRow = itemAt(endPos);//通过endPos获取鼠标位置所在的行
     int rowCount = row(itemRow);
     qDebug()<<rowCount<<"theInsertRow:"<<theInsertRow<<"总共数量："<<this->count();
     QListWidgetItem *newitem = new QListWidgetItem();
     newitem->setSizeHint(QSize(200,50));
     if(rowCount == -1 || rowCount == this->count()-1)
     {
         addItem(newitem);
     }
     else {
         insertItem(rowCount,newitem);
     }
     this->setItemWidget(newitem,w);


    QListWidgetItem *currentitem = this->takeItem(this->currentRow());
    delete currentitem;

}
