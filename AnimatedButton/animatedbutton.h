#ifndef ANIMATEDBUTTON_H
#define ANIMATEDBUTTON_H

#include <QPointer>
#include <QPaintEvent>
#include <QEvent>
#include <QPushButton>
#include <QPropertyAnimation>

class AnimatedButton : public QPushButton
{
    Q_OBJECT
public:
    AnimatedButton(QString pixenter, QString pixleave, QWidget*parent);
    ~AnimatedButton();

protected:
    virtual void enterEvent(QEvent*);
    virtual void leaveEvent(QEvent*);
    virtual void paintEvent(QPaintEvent*);

public slots:
    void entervaluechange(QVariant var);
    void leavevaluechange(QVariant var);

private:
    QPointer<QPropertyAnimation> m_enteranimation, m_leaveanimation;
    QList<QPixmap> m_enterlist, m_leavelist;
    int m_enterIndex, m_leaveIndex;
    bool m_enter, m_leave;
};

#endif // ANIMATEDBUTTON_H
