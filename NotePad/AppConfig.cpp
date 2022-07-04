#include "AppConfig.h"

AppConfig::AppConfig(QObject *parent) : QObject(parent)
{
    m_isValid = restore();
}

AppConfig::AppConfig(QFont editorfont, bool isautowrap, bool istoolbarvisible, bool isstatusbarvisible, QObject *parent)
{
    m_editorFont = editorfont;
    m_isAutoWrap = isautowrap;
    m_isToolBarVisible = istoolbarvisible;
    m_isStatusBarVisible = isstatusbarvisible;
    m_isValid = true;
}

QFont AppConfig::editorFont()
{
    return m_editorFont;
}

bool AppConfig::isAutoWrap()
{
    return m_isAutoWrap;
}

bool AppConfig::isStatusBarVisible()
{
    return m_isStatusBarVisible;
}

bool AppConfig::isToolBarVisible()
{
    return m_isToolBarVisible;
}

bool AppConfig::isValid()
{
    return m_isValid;
}

bool AppConfig::store()
{
    bool ret = true;
    QFile file(QApplication::applicationDirPath() + "/config.dat");
    if(file.open(QIODevice::WriteOnly))
    {
        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_5_6);
        out << m_editorFont;
        out << m_isAutoWrap;
        out << m_isToolBarVisible;
        out << m_isStatusBarVisible;
        file.close();
    }
    else
    {
        ret = false;
    }
    return ret;
}

bool AppConfig::restore()
{
    bool ret = true;
    QFile file(QApplication::applicationDirPath() + "/config.dat");
    if(file.open(QIODevice::ReadOnly))
    {
        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_5_6);

        in >> m_editorFont;
        in >> m_isAutoWrap;
        in >> m_isToolBarVisible;
        in >> m_isStatusBarVisible;
        file.close();
    }
    else
    {
        ret = false;
    }
    return ret;
}
