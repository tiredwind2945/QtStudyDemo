#include "FindDialog.h"

FindDialog::FindDialog(QWidget *parent, QPlainTextEdit* ptext):QDialog(parent, Qt::WindowCloseButtonHint | Qt::Drawer)
{
    m_label.setText("Find What:");
    m_findbutton.setText("Find Next");
    m_check.setText("Match Case");
    m_cancelbutton.setText("Cancel");
    m_forward.setText("Forward");
    m_back.setText("Back");
    m_forward.setChecked(true);
    m_radiogroup.setTitle("Direction");

    m_hblayout.addWidget(&m_forward);
    m_hblayout.addWidget(&m_back);

    m_radiogroup.setLayout(&m_hblayout);

    m_layout.setSpacing(10);
    m_layout.addWidget(&m_label, 0, 0);
    m_layout.addWidget(&m_edit, 0, 1);
    m_layout.addWidget(&m_findbutton, 0, 2);
    m_layout.addWidget(&m_check, 1, 0);
    m_layout.addWidget(&m_radiogroup, 1, 1);
    m_layout.addWidget(&m_cancelbutton, 1, 2);

    setLayout(&m_layout);
    setWindowTitle("Find");
    setPlainTextEdit(ptext);

    connect(&m_findbutton, SIGNAL(clicked()), this, SLOT(onFind()));
    connect(&m_cancelbutton, SIGNAL(clicked()), this, SLOT(onCancel()));
}

bool FindDialog::event(QEvent *event)
{
    if(event->type() == QEvent::Close)
    {
        hide();
        return true;
    }
   return QDialog::event(event);
}

void FindDialog::setPlainTextEdit(QPlainTextEdit *ptext)
{
    m_textedit = ptext;
}

QPlainTextEdit* FindDialog::getPlainTextEdit()
{
    return m_textedit;
}

void FindDialog::onFind()
{
    QString target = m_edit.text();
    if((m_textedit != NULL) && (target != ""))
    {
        QString text = m_textedit->toPlainText();
        QTextCursor cursor = m_textedit->textCursor();
        int index = -1;
        if(m_forward.isChecked())
        {
            index = text.indexOf(target, cursor.position(), m_check.isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);
            if(index >= 0)
            {
                cursor.setPosition(index);
                cursor.setPosition(index + target.length(), QTextCursor::KeepAnchor);
                m_textedit->setTextCursor(cursor);
            }
        }
        if(m_back.isChecked())
        {
            index = text.lastIndexOf(target, cursor.position() - text.length() - 1, m_check.isChecked() ? Qt::CaseSensitive:Qt::CaseInsensitive);
            if(index >= 0)
            {
                cursor.setPosition(index + target.length());
                cursor.setPosition(index, QTextCursor::KeepAnchor);
                m_textedit->setTextCursor(cursor);
            }
        }
        if(index < 0)
        {
            QMessageBox::information(this, "Find", "Can not find \"" + target + "\" any more", QMessageBox::Ok);
        }
    }

}

void FindDialog::onCancel()
{
    close();
}
