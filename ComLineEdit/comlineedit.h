#ifndef COMLINEEDIT_H
#define COMLINEEDIT_H
#include <QLineEdit>
#include <QStringListModel>

class ComLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit ComLineEdit(QWidget *parent = nullptr);
    ~ComLineEdit();

    void setNormal();
    void setSearching();
    void addValue(const QString &value);

protected:
   void focusInEvent(QFocusEvent *event);
   void focusOutEvent(QFocusEvent *event);

signals:
    void pressed();

private:
    QStringList valueList;
    QStringListModel *listModel;

private slots:
    void editComplete();
};

#endif // COMLINEEDIT_H
