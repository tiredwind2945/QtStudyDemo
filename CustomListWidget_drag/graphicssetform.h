#ifndef GRAPHICSSETFORM_H
#define GRAPHICSSETFORM_H

#include <QWidget>

namespace Ui {
class GraphicsSetForm;
}

class GraphicsSetForm : public QWidget
{
    Q_OBJECT

public:
    explicit GraphicsSetForm(QWidget *parent = nullptr);
    ~GraphicsSetForm();

    void setName(QString text);

private slots:
    void on_setBt_clicked();

private:
    Ui::GraphicsSetForm *ui;


};

#endif // GRAPHICSSETFORM_H
