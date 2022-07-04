#include <QButtonGroup>
#include <QToolBar>
#include <QToolButton>
#include <QDebug>
#include "explorewidget.h"
#include "ui_explorewidget.h"

ExploreWidget::ExploreWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExploreWidget)
{
    ui->setupUi(this);
    initExplore();
}

ExploreWidget::~ExploreWidget()
{
    delete ui;
}

/*
 *初始化导航栏
*/
void ExploreWidget::initExplore()
{
    //第一步 创建每个导航栏按钮
    QList<QPair<QString, QIcon> > pairList = getButtonTextAndIcons();
    QToolBar* tool = new QToolBar(this);
    QButtonGroup* btnGroup = new QButtonGroup(this);
    for (int i = 0; i < pairList.size(); ++i)
    {
        QPair<QString, QIcon> pair = pairList.at(i);
        QToolButton* btn = createExploreButton(pair.first, pair.second);
        btnGroup->addButton(btn, i);//每个button都可以设置一个id，这里将索引设置为id
        tool->addWidget(btn);

        if (i == 3)
        {
            tool->addSeparator();
        }
    }

    //第二步 导航栏被点击时，发出点击信号
    btnGroup->button(0)->setChecked(true);
    connect(btnGroup, SIGNAL(buttonClicked(int)), this, SIGNAL(sigShowWidget(int)));

    //第三步 设置工具栏
    tool->setOrientation(Qt::Vertical);//按钮垂直排列
    tool->layout()->setSpacing(20);
    ui->verticalLayout->insertWidget(0, tool, 1);
}

/*
 * 获取按钮文字和图标的hash结构,
 * 这里使用列表而不是hash表的原因是，
 * 每个按钮都是有序的
*/
QList<QPair<QString, QIcon> > ExploreWidget::getButtonTextAndIcons() const
{
    QList<QPair<QString, QIcon> > ret;
    ret << qMakePair(QStringLiteral("查词       "),
                         QIcon(":/image/dict.png"));
    ret << qMakePair(QStringLiteral("翻译      ") ,
                         QIcon(":/image/trans.png"));
    ret << qMakePair(QStringLiteral("例句      ")  ,
                         QIcon(":/image/example.png"));
    ret << qMakePair(QStringLiteral("百科      ")  ,
                         QIcon(":/image/wiki.png"));
    ret << qMakePair(QStringLiteral("单词本    ")  ,
                         QIcon(":/image/wordbook.png"));
    ret << qMakePair(QStringLiteral("人工翻译  ")  ,
                         QIcon(":/image/manual-trans.png"));
    ret << qMakePair(QStringLiteral("设置      ") ,
                         QIcon(":/image/settings.png"));
    ret << qMakePair(QStringLiteral("满意度调查 ") ,
                         QIcon(":/image/survey.png"));

    return ret;
}

/*
 * 创建导航栏按钮
*/
QToolButton *ExploreWidget::createExploreButton(
        const QString& text, const QIcon& icon) const
{
    QToolButton* btn = new QToolButton();

    //设置按钮图标
    btn->setIcon(icon);

    //设置按钮文字
    btn->setText(text);

    //设置按钮固定高度为40像素
    btn->setFixedHeight(40);

    //设置按钮在文字的右侧，还可以传递其他的枚举值来设置按钮和文字的位置
    btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    //设置图标的大小
    btn->setIconSize(QSize(10, 10));

    //因为当选择不同的导航栏按钮，在右侧会弹出相对应的内容，
    //所以将按钮设置为可选择，以提示当前内容所属类别
    btn->setCheckable(true);

    return btn;
}
