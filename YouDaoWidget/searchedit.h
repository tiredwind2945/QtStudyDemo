#ifndef SEARCHEDIT_H
#define SEARCHEDIT_H

#include <QFrame>

namespace Ui {
class SearchEdit;
}

class SearchEdit : public QFrame
{
    Q_OBJECT

public:
    explicit SearchEdit(QWidget *parent = 0);
    ~SearchEdit();

private:
    void init();

private:
    Ui::SearchEdit *ui;
};

#endif // SEARCHEDIT_H
