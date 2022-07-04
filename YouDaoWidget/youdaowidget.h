#ifndef YOUDAOWIDGET_H
#define YOUDAOWIDGET_H

#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class YouDaoWidget;
}

class YouDaoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit YouDaoWidget(QWidget *parent = 0);
    ~YouDaoWidget();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);

private slots:
    void on_btn_close_clicked();

    void on_btn_min_clicked();

private:
    Ui::YouDaoWidget *ui;
    QPoint mousePosition;
    bool isMousePressed;
};

#endif // YOUDAOWIDGET_H
