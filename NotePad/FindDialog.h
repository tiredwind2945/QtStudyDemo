#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QRadioButton>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QEvent>
#include <QPointer>
#include <QPlainTextEdit>
#include <QString>
#include <QTextCursor>
#include <QMessageBox>

class FindDialog : public QDialog
{
    Q_OBJECT
public:
    FindDialog(QWidget *parent = 0, QPlainTextEdit* ptext = 0);
    bool event(QEvent *event);
    void setPlainTextEdit(QPlainTextEdit *ptext);
    QPlainTextEdit* getPlainTextEdit();

protected slots:
    void onFind();
    void onCancel();

protected:
    QGridLayout m_layout;
    QHBoxLayout m_hblayout;

    QLabel m_label;
    QLineEdit m_edit;
    QPushButton m_findbutton;
    QPushButton m_cancelbutton;
    QCheckBox m_check;
    QRadioButton m_forward;
    QRadioButton m_back;

    QGroupBox m_radiogroup;

    QPointer<QPlainTextEdit> m_textedit;
};

#endif // FINDDIALOG_H
