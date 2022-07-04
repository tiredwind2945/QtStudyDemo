#ifndef REPLACEDIALOG_H
#define REPLACEDIALOG_H

#include "FindDialog.h"

class ReplaceDialog : public FindDialog
{
    Q_OBJECT
public:
    ReplaceDialog(QWidget* parent = 0, QPlainTextEdit* ptext = 0);

protected:

    QLabel m_replacelabel;
    QLineEdit m_replaceedit;
    QPushButton m_replacebutton;
    QPushButton m_replaceallbutton;

protected slots:
    void onReplace();
    void onRepalceAll();

};

#endif // REPLACEDIALOG_H
