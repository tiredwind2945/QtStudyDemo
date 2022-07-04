#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenuBar>
#include <QKeySequence>
#include <QToolBar>
#include <QStatusBar>
#include <QLabel>
#include <QPlainTextEdit>
#include <QPalette>
#include <QColor>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QCloseEvent>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QList>
#include <QUrl>
#include <QFileInfo>
#include <QObjectList>
#include <QPrintDialog>
#include <QPrinter>
#include <QTextDocument>
#include <QSharedPointer>
#include <QFontDialog>
#include <QFont>
#include <QMenu>
#include <QSize>
#include <QDesktopServices>
#include "FindDialog.h"
#include "ReplaceDialog.h"
#include "AboutDialog.h"
#include "AppConfig.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static MainWindow* newInstance();
    ~MainWindow();
protected:
    void closeEvent(QCloseEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

private:
    MainWindow();
    bool construct();

    bool initMenuBar();
    bool makeAction(QAction *&action, QString text, int key);
    bool initFileMenu(QMenuBar *mb);
    bool initEditMenu(QMenuBar *mb);
    bool initFormatMenu(QMenuBar *mb);
    bool initViewMenu(QMenuBar *mb);
    bool initHelpMenu(QMenuBar *mb);

    bool initToolBar();
    bool makeAction(QAction*& action, QString tip, QString icon);
    bool initFileToolItem(QToolBar *tb);
    bool initEditToolItem(QToolBar* tb);
    bool initFormatToolItem(QToolBar* tb);
    bool initViewToolItem(QToolBar* tb);

    bool initStatusBar();

    bool initMainEditor();

    QString createFileDialog(QFileDialog::AcceptMode mode, QString title);
    int showMessage(QWidget *parent, QMessageBox::Icon icon, const QString& title, const QString& text, QMessageBox::StandardButtons buttons);
    QString saveFile(QString path = "");
    void preTextChanged();
    void loadFile(QString path);
    QAction* findMenuBarItem(QString text);
    QAction* findToolBarItem(QString text);
    QToolBar* toolBar();
private slots:
    void onFileNew();
    void onFileOpen();
    void onFileSave();
    void onFileSaveAs();


    void onTextChanged();
    void onCopyAvailable(bool available);
    void onUndoAvailable(bool available);
    void onRedoAvailable(bool available);
    void onEditFind();
    void onEditReplace();

    void onViewStatusBar();
    void onViewToolBar();
    void onHelpAbout();
    void onHelpManual();
    void onFormatFont();
    void onFormatWrap();

    void onPrint();
    void onCursorChanged();

private:
    QPlainTextEdit mainEditor;
    QString m_filepath;
    bool m_isTextChanged;
    QLabel m_status;
    QSharedPointer<FindDialog> m_find;
    QSharedPointer<ReplaceDialog> m_replace;
};

#endif // MAINWINDOW_H
