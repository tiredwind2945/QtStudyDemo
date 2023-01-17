#include "animatedbutton.h""
#include <QPainter>
#include <QDebug>
#include <QBoxLayout>
#include <QFontMetrics>

AnimatedButton::AnimatedButton(QString strpixenter, QString strpixleave, QWidget*parent) : QPushButton(parent),
    m_leave(false),
    m_enter(true),
    m_leaveIndex(0),
    m_enterIndex(0)
{
    QPixmap pixenter(strpixenter);
    QPixmap pixleave(strpixleave);

    for(int i = 0; i<10; i++)   // enter
        m_enterlist << pixenter.copy(i*(pixenter.width()/10),0,pixenter.width()/10,pixenter.height());
    for(int j=0; j<8; j++)      // leave
        m_leavelist << pixleave.copy(j*(pixleave.width()/8),0,pixleave.width()/8,pixleave.height());
    m_enteranimation = new QPropertyAnimation(this, "");
    m_enteranimation->setStartValue(0);
    m_enteranimation->setEndValue(9);
    m_enteranimation->setDuration(600);
    connect(m_enteranimation, SIGNAL(valueChanged(QVariant)), this, SLOT(entervaluechange(QVariant)));

    m_leaveanimation = new QPropertyAnimation(this,"");
    m_leaveanimation->setStartValue(0);
    m_leaveanimation->setEndValue(7);
    m_leaveanimation->setDuration(600);
    connect(m_leaveanimation, SIGNAL(valueChanged(QVariant)), this, SLOT(leavevaluechange(QVariant)));
}

AnimatedButton::~AnimatedButton()
{
}

void AnimatedButton::enterEvent(QEvent *)
{
    m_enter=true;
    m_leave=false;
    m_enteranimation->start();
}

void AnimatedButton::leaveEvent(QEvent *)
{
    m_enter=false;
    m_leave=true;
    m_leaveanimation->start();
}

void AnimatedButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if(m_enter) painter.drawPixmap(rect(), m_enterlist.at(m_enterIndex));
    if(m_leave) painter.drawPixmap(rect(), m_leavelist.at(m_leaveIndex));
}

void AnimatedButton::entervaluechange(QVariant var)
{
    m_enterIndex=var.toInt();
    update();
}

void AnimatedButton::leavevaluechange(QVariant var)
{
    m_leaveIndex=var.toInt();
    update();
}
