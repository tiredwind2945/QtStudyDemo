#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QPixmap>
#include <QPalette>

class AboutDialog : public QDialog
{
    Q_OBJECT
public:
    AboutDialog(QWidget* parent = 0);

private slots:
    void onClose();

private:
    QLabel m_logo;
    QPlainTextEdit m_info;
    QPushButton m_close;
};

#endif // ABOUTDIALOG_H
