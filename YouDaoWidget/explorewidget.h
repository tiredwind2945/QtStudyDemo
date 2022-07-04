#ifndef EXPLOREWIDGET_H
#define EXPLOREWIDGET_H

#include <QWidget>

namespace Ui {
class ExploreWidget;
}

class QToolButton;
class ExploreWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ExploreWidget(QWidget *parent = 0);
    ~ExploreWidget();

signals:
    void sigShowWidget(int index);

private:
    void initExplore();
    QList< QPair<QString, QIcon> > getButtonTextAndIcons() const;
    QToolButton* createExploreButton(const QString &text, const QIcon &icon) const;

private:
    Ui::ExploreWidget *ui;
};

#endif // EXPLOREWIDGET_H
