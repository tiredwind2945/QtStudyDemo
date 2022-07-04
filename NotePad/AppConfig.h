#ifndef APPCONFIG_H
#define APPCONFIG_H

#include <QObject>
#include <QFont>
#include <QFile>
#include <QDataStream>
#include <QApplication>

class AppConfig : public QObject
{
    Q_OBJECT
public:
    explicit AppConfig(QObject *parent = 0);
    explicit AppConfig(QFont editorfont, bool isautowrap, bool istoolbarvisible, bool isstatusbarvisible, QObject *parent = 0);
    bool store();
    QFont editorFont();
    bool isAutoWrap();
    bool isToolBarVisible();
    bool isStatusBarVisible();
    bool isValid();
private:
    bool restore();
private:
    QFont m_editorFont;
    bool m_isAutoWrap;
    bool m_isToolBarVisible;
    bool m_isStatusBarVisible;

    bool m_isValid;
};
#endif // APPCONFIG_H
