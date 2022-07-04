#ifndef YYLISTWIDGET_H
#define YYLISTWIDGET_H

#include <QWidget>
#include "QListWidget"

class YYListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit YYListWidget(QWidget *parent = Q_NULLPTR);
    ~YYListWidget();

    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);

signals:

public slots:

private:
    QPoint startPos;

private:
    bool IsDraging = false;
    int theHighlightedRow = -2;
    int oldHighlightedRow = -2;
    int theDragRow = -1;
    int theInsertRow = -1;

};

#endif // YYLISTWIDGET_H
