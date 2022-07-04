#include "MainWindow.h"
#include <QDebug>

void MainWindow::onFileNew()
{
    preTextChanged();
    if(!m_isTextChanged)
    {
        mainEditor.clear();
        setWindowTitle("NotePad - [New ]");
        m_filepath = "";
        m_isTextChanged = false;
    }
}

void MainWindow::onFileOpen()
{
    preTextChanged();
    if(!m_isTextChanged)
    {
        QString path = createFileDialog(QFileDialog::AcceptOpen, "Open");
        if(path != "")
        {
            QFile file(path);
            if(file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                mainEditor.setPlainText(QString(file.readAll()));
                file.close();
                m_filepath = path;
                m_isTextChanged = false;
                setWindowTitle("NotePad - [" + m_filepath + "]");
            }
            else
            {
                showMessage(this, QMessageBox::Critical, QString("Error"), QString("Open file error: " + m_filepath), QMessageBox::Ok);
            }
        }
    }
}

void MainWindow::onFileSave()
{
    if(m_filepath == "")
    {
        m_filepath = createFileDialog(QFileDialog::AcceptSave, "Save");
    }
    if(m_filepath != "")
    {
        QFile file(m_filepath);
        if(file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&file);
            out << mainEditor.toPlainText();
            file.close();
            setWindowTitle("NotePad - [ " + m_filepath + " ]");
        }
        else
        {
            showMessage(this, QMessageBox::Critical, QString("Error"), QString("Save file error: " + m_filepath), QMessageBox::Ok);
            m_filepath = "";
        }
    }
}

void MainWindow::onFileSaveAs()
{
    QString path = createFileDialog(QFileDialog::AcceptSave, "Save As");
    if(path != "")
    {
        QFile file(path);
        if(file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&file);
            out << mainEditor.toPlainText();
            file.close();
            m_filepath = path;
            setWindowTitle("NotePad - [ " + m_filepath + " ]");
        }
        else
        {
            showMessage(this, QMessageBox::Critical, QString("Error"), QString("Save as error: " + m_filepath), QMessageBox::Ok);
        }
    }
}

void MainWindow::onEditFind()
{
   m_find->show();
}

void MainWindow::onEditReplace()
{
    m_replace->show();
}

void MainWindow::preTextChanged()
{
    if(m_isTextChanged)
    {
        int ret = showMessage(this, QMessageBox::Question, "Question", "Do you want to save the changes to the file?", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        switch(ret)
        {
        case QMessageBox::Yes:
            saveFile(m_filepath);
            break;
        case QMessageBox::No:
            m_isTextChanged = false;
            break;
        case QMessageBox::Cancel:
            break;
        }
    }
}

QString MainWindow::createFileDialog(QFileDialog::AcceptMode mode, QString title)
{
    QString ret = "";
    QFileDialog filedialog(this);
    QStringList filter;
    filter.append("Text Files (*.txt)");
    filter.append("All Files (*.*)");
    filedialog.setWindowTitle(title);
    filedialog.setAcceptMode(mode);
    filedialog.setNameFilters(filter);
    if(mode == QFileDialog::AcceptOpen)
    {
        filedialog.setFileMode(QFileDialog::ExistingFile);
    }
    if(filedialog.exec() == QFileDialog::Accepted)
    {
        ret = filedialog.selectedFiles()[0];
    }
    return ret;
}

int MainWindow::showMessage(QWidget *parent, QMessageBox::Icon icon, const QString& title, const QString & text, QMessageBox::StandardButtons buttons)
{
    int ret = -1;
    if(icon == QMessageBox::Critical)
    {
        ret = QMessageBox::critical(parent, title, text, buttons);
    }
    if(icon == QMessageBox::Question)
    {
        ret = QMessageBox::question(parent, title, text, buttons);
    }
    if(icon == QMessageBox::Warning)
    {
        ret = QMessageBox::warning(parent, title, text, buttons);
    }
    if(icon == QMessageBox::Information)
    {
        ret = QMessageBox::information(parent, title, text, buttons);
    }
    return ret;
}

void MainWindow::onTextChanged()
{
    if( !m_isTextChanged )
    {
        setWindowTitle("*" + windowTitle());
    }
    m_isTextChanged = true;
}

QString MainWindow::saveFile(QString path)
{
    QString ret = path;
    if(m_filepath == "")
    {
        m_filepath = createFileDialog(QFileDialog::AcceptSave, "Save");
    }

    loadFile(path);
    return ret;
}

void MainWindow::loadFile(QString path)
{
    if(path != "")
    {
        QFile file(path);
        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QString text = file.readAll();
            mainEditor.setPlainText(text);
            file.close();
            m_filepath = path;
            setWindowTitle("NotePad - [ " + m_filepath + " ]");
            m_isTextChanged = false;
        }
        else
        {
            showMessage(this, QMessageBox::Critical, QString("Error"), QString("Save file error: " + m_filepath), QMessageBox::Ok);
        }
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    preTextChanged();
    if(!m_isTextChanged)
    {
        QMainWindow::closeEvent(event);
    }
    else
    {
        event->ignore();
    }
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasFormat("text/uri-list"))
    {
        event->acceptProposedAction();
    }
    else
    {
        event->ignore();
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    if(event->mimeData()->hasUrls())
    {
        QList<QUrl> list = event->mimeData()->urls();
        QString path = list[0].toLocalFile();
        QFileInfo fi(path);

        if( fi.isFile() )
        {
            preTextChanged();

            if(!m_isTextChanged)
            {
                loadFile(path);
            }
        }
        else
        {
            showMessage(this, QMessageBox::Critical, "Error", "Open file error", QMessageBox::Ok);
        }
    }
    else
    {
        event->ignore();
    }
}

void MainWindow::onCopyAvailable(bool available)
{
    findMenuBarItem("Copy")->setEnabled(available);
    findMenuBarItem("Cut")->setEnabled(available);
    findToolBarItem("Copy")->setEnabled(available);
    findToolBarItem("Cut")->setEnabled(available);
}

void MainWindow::onUndoAvailable(bool available)
{
    findMenuBarItem("Undo")->setEnabled(available);
    findToolBarItem("Undo")->setEnabled(available);
}

void MainWindow::onRedoAvailable(bool available)
{
    findToolBarItem("Redo")->setEnabled(available);
}

QAction* MainWindow::findMenuBarItem(QString text)
{
    QAction* ret = NULL;
    const QObjectList& list = menuBar()->children();

    for(int i=0; i<list.count(); i++)
    {
        QMenu* menu = dynamic_cast<QMenu*>(list[i]);

        if( menu != NULL )
        {
            QList<QAction*> actions = menu->actions();
            for(int j=0; j < actions.count(); j++)
            {
                if(actions[j]->text().startsWith(text))
                {
                    ret = actions[j];
                    break;
                }
            }
        }
    }

    return ret;
}
QAction* MainWindow::findToolBarItem(QString text)
{
    QAction* ret = NULL;
    const QObjectList& list = children();
    for(int i = 0; i < list.count(); i++)
    {
        QToolBar *tb = dynamic_cast<QToolBar *>(list[i]);
        if(tb != NULL)
        {
            QList<QAction *> actions = tb->actions();
            for(int j = 0; j < actions.count(); j++)
            {
                if(actions[j]->toolTip().startsWith(text))
                {
                    ret = actions[j];
                    break;
                }
            }
        }
    }
    return ret;
}

void MainWindow::onPrint()
{
    QPrintDialog printdialog(this);
    printdialog.setWindowTitle("Print");
    if(printdialog.exec() == QPrintDialog::Accepted)
    {
        QPrinter *printer = printdialog.printer();
        mainEditor.document()->print(printer);
    }
}

void MainWindow::onCursorChanged()
{
    int pos = mainEditor.textCursor().position();
    QString text = mainEditor.toPlainText();
    int colum = 0;
    int row = 0;
    int flag = -1;
    for(int i = 0; i < pos; i++)
    {
        if( text[i] == '\n' )
        {
            row++;
            flag = i;
        }
    }
    flag++;
    colum = pos - flag;
    m_status.setText("Line: " + QString::number(row + 1) + "   Colum: " + QString::number(colum + 1));
}

void MainWindow::onViewStatusBar()
{
    QStatusBar *sb = statusBar();
    bool visible = sb->isVisible();
    sb->setVisible(!visible);
    findToolBarItem("Status Bar")->setChecked(!visible);
    findMenuBarItem("Status Bar")->setChecked(!visible);
}

void MainWindow::onViewToolBar()
{
    const QObjectList& list = children();
    for(int i = 0; i < list.count(); i++)
    {
        QToolBar *tb = dynamic_cast<QToolBar*>(list[i]);
        if(tb != NULL)
        {
            bool visible = tb->isVisible();
            tb->setVisible(!visible);
            findMenuBarItem("Tool Bar")->setChecked(!visible);
            findToolBarItem("Tool Bar")->setChecked(!visible);
            break;
        }
    }
}

void MainWindow::onHelpAbout()
{
    AboutDialog(this).exec();
}

void MainWindow::onFormatFont()
{
    bool ok = false;
    QFont font = QFontDialog::getFont(&ok, mainEditor.font(), this);
    if(ok)
    {
        mainEditor.setFont(font);
    }
}

void MainWindow::onFormatWrap()
{
    QPlainTextEdit::LineWrapMode mode = mainEditor.lineWrapMode();
    if(mode == QPlainTextEdit::NoWrap)
    {
        mainEditor.setLineWrapMode(QPlainTextEdit::WidgetWidth);
        findMenuBarItem("Auto Wrap")->setChecked(true);
        findToolBarItem("Auto Wrap")->setChecked(true);
    }
    else
    {
        mainEditor.setLineWrapMode(QPlainTextEdit::NoWrap);
        findMenuBarItem("Auto Wrap")->setChecked(false);
        findToolBarItem("Auto Wrap")->setChecked(false);
    }
}

void MainWindow::onHelpManual()
{
    QDesktopServices::openUrl(QUrl("http://9291927.blog.51cto.com/"));
}
