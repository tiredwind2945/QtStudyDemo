#include "MainWindow.h"


MainWindow::MainWindow():
    m_find(new FindDialog(this, &mainEditor)),
    m_replace(new ReplaceDialog(this, &mainEditor))
{
    resize(800, 600);
    setWindowTitle("Note - [New ]");
    m_filepath = "";
    m_isTextChanged = false;
    mainEditor.setAcceptDrops(false);
    setAcceptDrops(true);
}

MainWindow::~MainWindow()
{
    QFont font = mainEditor.font();
    bool isautowrap = (mainEditor.lineWrapMode() == QPlainTextEdit::WidgetWidth);
    bool istoolbarvisible = (findMenuBarItem("Tool Bar")->isChecked() && findToolBarItem("Tool Bar")->isChecked());
    bool isstatusbarvisible = (findMenuBarItem("Status Bar")->isChecked() && findToolBarItem("Status Bar")->isChecked());

    AppConfig config(font, isautowrap, istoolbarvisible, isstatusbarvisible, this);
    config.store();
}

MainWindow* MainWindow::newInstance()
{
    MainWindow* ret = new MainWindow();
    if((ret == NULL) || (!ret->construct()))
    {
        delete ret;
        ret = NULL;
    }
    return ret;
}

bool MainWindow::construct()
{
    bool ret = true;

    AppConfig config;

    ret = ret && initMenuBar();
    ret = ret && initToolBar();
    ret = ret && initStatusBar();
    ret = ret && initMainEditor();

    if(config.isValid())
    {
        mainEditor.setFont(config.editorFont());
        if(!config.isAutoWrap())
        {
            mainEditor.setLineWrapMode(QPlainTextEdit::NoWrap);
            findToolBarItem("Auto Wrap")->setCheckable(false);
            findMenuBarItem("Auto Wrap")->setChecked(false);
        }
        if(!config.isToolBarVisible())
        {
            toolBar()->setVisible(false);
            findMenuBarItem("Tool Bar")->setChecked(false);
            findToolBarItem("Tool Bar")->setChecked(false);
        }
        if(!config.isStatusBarVisible())
        {
            statusBar()->setVisible(false);
            findMenuBarItem("Status Bar")->setChecked(false);
            findToolBarItem("Status Bar")->setChecked(false);
        }
    }
    return ret;
}

QToolBar* MainWindow::toolBar()
{
    QToolBar* ret = NULL;
    const QObjectList& list = children();

    for(int i=0; i<list.count(); i++)
    {
        QToolBar* tb = dynamic_cast<QToolBar*>(list[i]);

        if( tb != NULL )
        {
            ret = tb;
            break;
        }
    }

    return ret;
}

bool MainWindow::initMenuBar()
{
    bool ret = true;
    QMenuBar *mb = menuBar();
    ret = ret && initFileMenu(mb);
    ret = ret && initEditMenu(mb);
    ret = ret && initFormatMenu(mb);
    ret = ret && initViewMenu(mb);
    ret = ret && initHelpMenu(mb);
    return ret;
}

bool MainWindow::initFileMenu(QMenuBar *mb)
{
    QMenu *menu = new QMenu("File(&F)", mb);
    bool ret = (menu != NULL);
    if(ret)
    {
        QAction *action = NULL;
        ret = ret && makeAction(action, "New(&N)", Qt::CTRL + Qt::Key_N);
        if(ret)
        {
            connect(action, SIGNAL(triggered()), this, SLOT(onFileNew()));
            menu->addAction(action);
        }

        ret = ret && makeAction(action, "Open(&O)", Qt::CTRL + Qt::Key_O);
        if(ret)
        {
            connect(action, SIGNAL(triggered()), this, SLOT(onFileOpen()));
            menu->addAction(action);
        }

        ret = ret && makeAction(action, "Save(&S)", Qt::CTRL + Qt::Key_S);
        if(ret)
        {
            connect(action, SIGNAL(triggered()), this, SLOT(onFileSave()));
            menu->addAction(action);
        }

        ret = ret && makeAction(action, "Save As(&A)", 0);
        if(ret)
        {
            connect(action, SIGNAL(triggered()), this, SLOT(onFileSaveAs()));
            menu->addAction(action);
        }
        menu->addSeparator();

        ret = ret && makeAction(action, "Page Setting(&U)", 0);
        if(ret)
        {
            menu->addAction(action);
        }

        ret = ret && makeAction(action, "Print(&P)", Qt::CTRL + Qt::Key_P);
        if(ret)
        {
            connect(action, SIGNAL(triggered()), this, SLOT(onPrint()));
            menu->addAction(action);
        }
        menu->addSeparator();

        ret = ret && makeAction(action, "Exit(&X)", 0);
        if(ret)
        {
            menu->addAction(action);
        }
    }

    if(ret)
    {
        mb->addMenu(menu);
    }
    else
    {
        delete menu;
    }
    return ret;
}

bool MainWindow::makeAction(QAction *&action, QString text, int key)
{
    bool ret = true;
    action = new QAction(text, NULL);
    if(action != NULL)
    {
        action->setShortcut(QKeySequence(key));
    }
    else
    {
        ret = false;
    }
    return ret;
}

bool MainWindow::initEditMenu(QMenuBar *mb)
{
    QMenu *menu = new QMenu("Edit(&E)", mb);
    bool ret = (menu != NULL);
    if(ret)
    {
        QAction *action = NULL;
        ret = ret && makeAction(action, "Undo(&U)", Qt::CTRL + Qt::Key_Z);
        if(ret)
        {
            connect(action, SIGNAL(triggered()), &mainEditor, SLOT(undo()));
            action->setEnabled(false);
            menu->addAction(action);
        }
        menu->addSeparator();

        ret = ret && makeAction(action, "Cut(&T)", Qt::CTRL + Qt::Key_X);
        if(ret)
        {
            connect(action, SIGNAL(triggered()), &mainEditor, SLOT(cut()));
            action->setEnabled(false);
            menu->addAction(action);
        }

        ret = ret && makeAction(action, "Copy(&C)", Qt::CTRL + Qt::Key_C);
        if(ret)
        {
            connect(action, SIGNAL(triggered()), &mainEditor, SLOT(copy()));
            action->setEnabled(false);
            menu->addAction(action);
        }

        ret = ret && makeAction(action, "Paste(&P)", Qt::CTRL + Qt::Key_V);
        if(ret)
        {
            connect(action, SIGNAL(triggered()), &mainEditor, SLOT(paste()));
            menu->addAction(action);
        }

        ret = ret && makeAction(action, "Delete(&L)", Qt::Key_Delete);
        if(ret)
        {
            menu->addAction(action);
        }
        menu->addSeparator();

        ret = ret && makeAction(action, "Find(&F)", Qt::CTRL + Qt::Key_F);
        if(ret)
        {
            connect(action, SIGNAL(triggered()), this, SLOT(onEditFind()));
            menu->addAction(action);
        }

        ret = ret && makeAction(action, "Find Next(&N)", Qt::Key_F3);
        if(ret)
        {
            menu->addAction(action);
        }

        ret = ret && makeAction(action, "Replace(&R)", Qt::CTRL + Qt::Key_H);
        if(ret)
        {
            connect(action, SIGNAL(triggered()), this, SLOT(onEditReplace()));
            menu->addAction(action);
        }

        ret = ret && makeAction(action, "Goto(&G)", Qt::CTRL + Qt::Key_G);
        if(ret)
        {
            menu->addAction(action);
        }
        menu->addSeparator();

        ret = ret && makeAction(action, "All(&A)", Qt::CTRL + Qt::Key_A);
        if(ret)
        {
            connect(action, SIGNAL(triggered()), &mainEditor, SLOT(selectAll()));
            menu->addAction(action);
        }

        ret = ret && makeAction(action, "Time/Date(&D)", Qt::Key_F5);
        if(ret)
        {
            menu->addAction(action);
        }
    }
    if(ret)
    {
        mb->addMenu(menu);
    }
    else
    {
        delete menu;
    }
    return ret;
}

bool MainWindow::initFormatMenu(QMenuBar *mb)
{
    QMenu *menu = new QMenu("Format(&O)", mb);
    bool ret = (menu != NULL);
    if(ret)
    {
        QAction *action = NULL;
        ret = ret && makeAction(action, "Auto Wrap(&W)", 0);
        if(ret)
        {
            action->setCheckable(true);
            action->setChecked(true);
            connect(action, SIGNAL(triggered()), this, SLOT(onFormatWrap()));
            menu->addAction(action);
        }
        menu->addSeparator();

        ret = ret && makeAction(action, "Font(&F)", 0);
        if(ret)
        {
            connect(action, SIGNAL(triggered()), this, SLOT(onFormatFont()));
            menu->addAction(action);
        }
    }
    if(ret)
    {
        mb->addMenu(menu);
    }
    else
    {
        delete menu;
    }
    return ret;
}

bool MainWindow::initViewMenu(QMenuBar *mb)
{
    QMenu *menu = new QMenu("View(&V)", mb);
    bool ret = (menu != NULL);
    if(ret)
    {
        QAction *action = NULL;
        ret = ret && makeAction(action, "Status Bar(&S)", 0);
        if(ret)
        {
            action->setCheckable(true);
            action->setChecked(true);
            connect(action, SIGNAL(triggered()), this, SLOT(onViewStatusBar()));
            menu->addAction(action);
        }

        ret = ret && makeAction(action, "Tool Bar(&T)", 0);
        if(ret)
        {
            action->setCheckable(true);
            action->setChecked(true);
            connect(action, SIGNAL(triggered()), this, SLOT(onViewToolBar()));
            menu->addAction(action);
        }
    }
    if(ret)
    {
        mb->addMenu(menu);
    }
    else
    {
        delete menu;
    }
    return ret;
}

bool MainWindow::initHelpMenu(QMenuBar *mb)
{
    QMenu *menu = new QMenu("Help(&H)", mb);
    bool ret = (menu != NULL);
    if(ret)
    {
        QAction *action = NULL;
        ret = ret && makeAction(action, "Help(&H)", 0);
        if(ret)
        {
            connect(action, SIGNAL(triggered()), this, SLOT(onHelpManual()));
            menu->addAction(action);
        }
        menu->addSeparator();

        ret = ret && makeAction(action, "About NotePad(&A)", 0);
        if(ret)
        {
            connect(action, SIGNAL(triggered()), this, SLOT(onHelpAbout()));
            menu->addAction(action);
        }
    }
    if(ret)
    {
        mb->addMenu(menu);
    }
    else
    {
        delete menu;
    }
    return ret;
}

bool MainWindow::initToolBar()
{
    bool ret = true;
    QToolBar *tb = addToolBar("ToolBar");
    tb->setMovable(false);
    tb->setIconSize(QSize(16, 16));
    ret = ret && initFileToolItem(tb);//创建文件菜单栏的功能到工具栏
    ret = ret && initEditToolItem(tb);//创建编辑菜单栏到工具栏
    ret = ret && initFormatToolItem(tb);//创建格式菜单栏到工具栏
    ret = ret && initViewToolItem(tb);//创建查看菜单栏到工具栏

    return ret;

}
bool MainWindow::initFileToolItem(QToolBar *tb)
{
    bool ret = true;
    QAction *action = NULL;
    ret = ret && makeAction(action, "New", ":/res/pic/new.png");

    if( ret )
    {
        connect(action, SIGNAL(triggered()), this, SLOT(onFileNew()));
        tb->addAction(action);
    }

    ret = ret && makeAction(action, "Open", ":/res/pic/open.png");
    if( ret )
    {
        connect(action, SIGNAL(triggered()), this, SLOT(onFileOpen()));
        tb->addAction(action);
    }

    ret = ret && makeAction(action, "Save", ":/res/pic/save.png");
    if( ret )
    {
        connect(action, SIGNAL(triggered()), this, SLOT(onFileSave()));
        tb->addAction(action);
    }

    ret = ret && makeAction(action, "SaveAs", ":/res/pic/saveas.png");
    if( ret )
    {
        connect(action, SIGNAL(triggered()), this, SLOT(onFileSaveAs()));
        tb->addAction(action);
    }

    ret = ret && makeAction(action, "Print", ":/res/pic/print.png");
    if( ret )
    {
        connect(action, SIGNAL(triggered()), this, SLOT(onPrint()));
        tb->addAction(action);
    }
    tb->addSeparator();
    return ret;
}

bool MainWindow::initEditToolItem(QToolBar* tb)
{
    bool ret = true;
    QAction *action = NULL;
    ret = ret && makeAction(action, "Undo", ":/res/pic/undo.png");

    if( ret )
    {
        connect(action, SIGNAL(triggered()), &mainEditor, SLOT(undo()));
        action->setEnabled(false);
        tb->addAction(action);
    }

    ret = ret && makeAction(action, "Redo", ":/res/pic/redo.png");

    if( ret )
    {
        connect(action, SIGNAL(triggered()), &mainEditor, SLOT(redo()));
        action->setEnabled(false);
        tb->addAction(action);
    }

    ret = ret && makeAction(action, "Cut", ":/res/pic/cut.png");
    if( ret )
    {
        connect(action, SIGNAL(triggered()), &mainEditor, SLOT(cut()));
        action->setEnabled(false);
        tb->addAction(action);
    }

    ret = ret && makeAction(action, "Copy", ":/res/pic/copy.png");
    if( ret )
    {
        connect(action, SIGNAL(triggered()), &mainEditor, SLOT(copy()));
        action->setEnabled(false);
        tb->addAction(action);
    }

    ret = ret && makeAction(action, "Paste", ":/res/pic/paste.png");
    if( ret )
    {
        connect(action, SIGNAL(triggered()), &mainEditor, SLOT(paste()));
        tb->addAction(action);
    }

    ret = ret && makeAction(action, "Find", ":/res/pic/find.png");
    if( ret )
    {
        connect(action, SIGNAL(triggered()), this, SLOT(onEditFind()));
        tb->addAction(action);
    }

    ret = ret && makeAction(action, "Replace", ":/res/pic/replace.png");
    if( ret )
    {
        connect(action, SIGNAL(triggered()), this, SLOT(onEditReplace()));
        tb->addAction(action);
    }

    ret = ret && makeAction(action, "Goto", ":/res/pic/goto.png");
    if( ret )
    {
        tb->addAction(action);
    }
    tb->addSeparator();
    return ret;
}

bool MainWindow::initFormatToolItem(QToolBar* tb)
{
    bool ret = true;
    QAction *action = NULL;
    ret = ret && makeAction(action, "Auto Wrap", ":/res/pic/wrap.png");
    if( ret )
    {
        action->setCheckable(true);
        action->setChecked(true);
        connect(action, SIGNAL(triggered()), this, SLOT(onFormatWrap()));
        tb->addAction(action);
    }

    ret = ret && makeAction(action, "Font", ":/res/pic/font.png");
    if( ret )
    {
        connect(action, SIGNAL(triggered()), this, SLOT(onFormatFont()));
        tb->addAction(action);
    }
    tb->addSeparator();
    return ret;
}

bool MainWindow::initViewToolItem(QToolBar* tb)
{
    bool ret = true;
    QAction *action = NULL;
    ret = ret && makeAction(action, "Tool Bar", ":/res/pic/tool.png");

    if( ret )
    {
        action->setCheckable(true);
        action->setChecked(true);
        connect(action, SIGNAL(triggered()), this, SLOT(onViewToolBar()));
        tb->addAction(action);
    }

    ret = ret && makeAction(action, "Status Bar", ":/res/pic/status.png");

    if( ret )
    {
        action->setCheckable(true);
        action->setChecked(true);
        connect(action, SIGNAL(triggered()), this, SLOT(onViewStatusBar()));
        tb->addAction(action);
    }
    return ret;
}

bool MainWindow::makeAction(QAction*& action, QString tip, QString icon)
{
    bool ret = true;

    action = new QAction("", NULL);

    if( action != NULL )
    {
        action->setToolTip(tip);
        action->setIcon(QIcon(icon));
    }
    else
    {
        ret = false;
    }

    return ret;
}

bool MainWindow::initStatusBar()
{
    bool ret = true;
    QStatusBar *sb = statusBar();
    QLabel *label = new QLabel("CopyRight @Scorpio Studio");
    if(label != NULL)
    {
        label->setMinimumWidth(150);
        label->setAlignment(Qt::AlignCenter);
        m_status.setMinimumWidth(200);
        m_status.setAlignment(Qt::AlignCenter);
        m_status.setText("Line: 1           Colum:  1");
        sb->addPermanentWidget(&m_status);
        sb->addPermanentWidget(label);
    }
    else
    {
        ret = false;
    }
    return ret;
}

bool MainWindow::initMainEditor()
{
    bool ret = true;
    //设置mainEditor的父组件
    mainEditor.setParent(this);
    //设置中央组件为mainEditor
    setCentralWidget(&mainEditor);
    //设置mainEditor的背景色为豆沙绿
    QPalette p = mainEditor.palette();
    p.setColor(QPalette::Base, QColor(204, 232, 207));
    p.setColor(QPalette::Inactive, QPalette::Highlight, p.color(QPalette::Active, QPalette::Highlight));
    p.setColor(QPalette::Inactive, QPalette::HighlightedText, p.color(QPalette::Active, QPalette::HighlightedText));
    mainEditor.setPalette(p);

    connect(&mainEditor, SIGNAL(textChanged()), this, SLOT(onTextChanged()));
    connect(&mainEditor, SIGNAL(copyAvailable(bool)), this, SLOT(onCopyAvailable(bool)));
    connect(&mainEditor, SIGNAL(undoAvailable(bool)), this, SLOT(onUndoAvailable(bool)));
    connect(&mainEditor, SIGNAL(redoAvailable(bool)), this, SLOT(onRedoAvailable(bool)));
    connect(&mainEditor, SIGNAL(cursorPositionChanged()), this, SLOT(onCursorChanged()));
    return ret;
}

