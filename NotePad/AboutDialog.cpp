#include "AboutDialog.h"

AboutDialog::AboutDialog(QWidget* parent)
    :QDialog(parent, Qt::WindowCloseButtonHint), m_logo(this), m_info(this), m_close(this)
{
    QPixmap pm(":/res/pic/dt.png");
    pm = pm.scaled(120,120, Qt::KeepAspectRatio);
    m_logo.setPixmap(pm);
    m_logo.move(20, 20);
    m_logo.resize(120, 120);

    QPalette p = m_info.palette();
    p.setColor(QPalette::Active, QPalette::Base, palette().color(QPalette::Active, QPalette::Background));
    p.setColor(QPalette::Inactive, QPalette::Base, palette().color(QPalette::Inactive, QPalette::Background));
    m_info.setPalette(p);
    m_info.move(200, 30);
    m_info.resize(180, 130);
    m_info.setFrameStyle(QPlainTextEdit::NoFrame);
    m_info.setReadOnly(true);
    m_info.insertPlainText("NotePad Project\n\nPlatform: Qt 5.6.2\n\nVersion: 1.0.0\n\nAuthor: Scorpio");

    m_close.setText("Close");
    m_close.move(273, 175);
    m_close.resize(100, 30);

    setWindowTitle("About NotePad");
    setFixedSize(395, 230);
    connect(&m_close, SIGNAL(clicked()), this, SLOT(onClose()));
}

void AboutDialog::onClose()
{
    close();
}
