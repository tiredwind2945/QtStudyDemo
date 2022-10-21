#ifndef SEARCHLINEEDIT_H
#define SEARCHLINEEDIT_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QStringListModel>

class InnerLineEdit;
class SearchLineEdit : public QWidget
{
    Q_OBJECT

public:
    SearchLineEdit(QWidget *parent = nullptr);
    ~SearchLineEdit();

protected:
    void resizeEvent(QResizeEvent *event);

signals:
    void searchTextChanged(QString);

private slots:
    void textChange(QString text);
    void editClicked();
    void btnClicked();

private:
    InnerLineEdit *lineEdit;
    QPushButton *btn;
};

class InnerLineEdit : public QLineEdit
{
    Q_OBJECT

 public:
    explicit InnerLineEdit(QWidget *parent = nullptr);
    void setNormal();
    void setSearching();
    void addValue(const QString &value);

protected:
   void focusInEvent(QFocusEvent *event);
   void focusOutEvent(QFocusEvent *event);

 signals:
    void pressed();

private slots:
    void editComplete();

private:
    QStringList valueList;
    QStringListModel *listModel;
};

#endif // SEARCHLINEEDIT_H
