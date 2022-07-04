/********************************************************************************
** Form generated from reading UI file 'youdaowidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_YOUDAOWIDGET_H
#define UI_YOUDAOWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "explorewidget.h"
#include "searchedit.h"

QT_BEGIN_NAMESPACE

class Ui_YouDaoWidget
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame_title;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_logo;
    QPushButton *btn_pre;
    QPushButton *btn_next;
    SearchEdit *frame_search;
    QPushButton *btn_history;
    QPushButton *btn_login;
    QPushButton *btn_mini;
    QPushButton *btn_min;
    QPushButton *btn_max;
    QPushButton *btn_close;
    QHBoxLayout *hLayout;
    ExploreWidget *widget;
    QStackedWidget *stackedWidget;
    QWidget *page_find;
    QWidget *page_trans;
    QWidget *page_example;
    QWidget *page_encyclopedia;
    QWidget *page_wordbook;
    QWidget *page_trans_persion;
    QWidget *page_setting;
    QWidget *page_satis_survery;

    void setupUi(QWidget *YouDaoWidget)
    {
        if (YouDaoWidget->objectName().isEmpty())
            YouDaoWidget->setObjectName(QStringLiteral("YouDaoWidget"));
        YouDaoWidget->resize(654, 368);
        YouDaoWidget->setStyleSheet(QStringLiteral(""));
        verticalLayout = new QVBoxLayout(YouDaoWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        frame_title = new QFrame(YouDaoWidget);
        frame_title->setObjectName(QStringLiteral("frame_title"));
        frame_title->setMinimumSize(QSize(0, 60));
        frame_title->setStyleSheet(QStringLiteral(""));
        frame_title->setFrameShape(QFrame::StyledPanel);
        frame_title->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_title);
        horizontalLayout_2->setSpacing(20);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 9, -1, -1);
        label_logo = new QLabel(frame_title);
        label_logo->setObjectName(QStringLiteral("label_logo"));
        label_logo->setMinimumSize(QSize(80, 0));
        label_logo->setMaximumSize(QSize(100, 23));
        label_logo->setStyleSheet(QStringLiteral(""));

        horizontalLayout_2->addWidget(label_logo);

        btn_pre = new QPushButton(frame_title);
        btn_pre->setObjectName(QStringLiteral("btn_pre"));
        btn_pre->setMinimumSize(QSize(0, 10));
        btn_pre->setMaximumSize(QSize(10, 16777215));
        btn_pre->setStyleSheet(QStringLiteral(""));

        horizontalLayout_2->addWidget(btn_pre);

        btn_next = new QPushButton(frame_title);
        btn_next->setObjectName(QStringLiteral("btn_next"));
        btn_next->setEnabled(false);
        btn_next->setMinimumSize(QSize(0, 10));
        btn_next->setMaximumSize(QSize(10, 16777215));
        btn_next->setStyleSheet(QStringLiteral(""));

        horizontalLayout_2->addWidget(btn_next);

        frame_search = new SearchEdit(frame_title);
        frame_search->setObjectName(QStringLiteral("frame_search"));
        frame_search->setMinimumSize(QSize(0, 10));
        frame_search->setMaximumSize(QSize(16777215, 35));
        frame_search->setFrameShape(QFrame::StyledPanel);
        frame_search->setFrameShadow(QFrame::Raised);

        horizontalLayout_2->addWidget(frame_search);

        btn_history = new QPushButton(frame_title);
        btn_history->setObjectName(QStringLiteral("btn_history"));
        btn_history->setMaximumSize(QSize(16, 16));
        btn_history->setStyleSheet(QStringLiteral(""));

        horizontalLayout_2->addWidget(btn_history);

        btn_login = new QPushButton(frame_title);
        btn_login->setObjectName(QStringLiteral("btn_login"));
        btn_login->setMaximumSize(QSize(25, 25));
        btn_login->setStyleSheet(QStringLiteral(""));

        horizontalLayout_2->addWidget(btn_login);

        btn_mini = new QPushButton(frame_title);
        btn_mini->setObjectName(QStringLiteral("btn_mini"));
        btn_mini->setMaximumSize(QSize(30, 18));
        btn_mini->setStyleSheet(QStringLiteral(""));

        horizontalLayout_2->addWidget(btn_mini);

        btn_min = new QPushButton(frame_title);
        btn_min->setObjectName(QStringLiteral("btn_min"));
        btn_min->setMaximumSize(QSize(15, 2));
        btn_min->setStyleSheet(QStringLiteral(""));

        horizontalLayout_2->addWidget(btn_min);

        btn_max = new QPushButton(frame_title);
        btn_max->setObjectName(QStringLiteral("btn_max"));
        btn_max->setMinimumSize(QSize(0, 0));
        btn_max->setMaximumSize(QSize(13, 13));
        btn_max->setStyleSheet(QStringLiteral(""));

        horizontalLayout_2->addWidget(btn_max);

        btn_close = new QPushButton(frame_title);
        btn_close->setObjectName(QStringLiteral("btn_close"));
        btn_close->setMaximumSize(QSize(13, 13));
        btn_close->setStyleSheet(QStringLiteral(""));

        horizontalLayout_2->addWidget(btn_close);


        verticalLayout->addWidget(frame_title);

        hLayout = new QHBoxLayout();
        hLayout->setSpacing(0);
        hLayout->setObjectName(QStringLiteral("hLayout"));
        widget = new ExploreWidget(YouDaoWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMinimumSize(QSize(120, 0));

        hLayout->addWidget(widget);

        stackedWidget = new QStackedWidget(YouDaoWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setStyleSheet(QStringLiteral(""));
        page_find = new QWidget();
        page_find->setObjectName(QStringLiteral("page_find"));
        stackedWidget->addWidget(page_find);
        page_trans = new QWidget();
        page_trans->setObjectName(QStringLiteral("page_trans"));
        stackedWidget->addWidget(page_trans);
        page_example = new QWidget();
        page_example->setObjectName(QStringLiteral("page_example"));
        stackedWidget->addWidget(page_example);
        page_encyclopedia = new QWidget();
        page_encyclopedia->setObjectName(QStringLiteral("page_encyclopedia"));
        stackedWidget->addWidget(page_encyclopedia);
        page_wordbook = new QWidget();
        page_wordbook->setObjectName(QStringLiteral("page_wordbook"));
        stackedWidget->addWidget(page_wordbook);
        page_trans_persion = new QWidget();
        page_trans_persion->setObjectName(QStringLiteral("page_trans_persion"));
        stackedWidget->addWidget(page_trans_persion);
        page_setting = new QWidget();
        page_setting->setObjectName(QStringLiteral("page_setting"));
        stackedWidget->addWidget(page_setting);
        page_satis_survery = new QWidget();
        page_satis_survery->setObjectName(QStringLiteral("page_satis_survery"));
        stackedWidget->addWidget(page_satis_survery);

        hLayout->addWidget(stackedWidget);


        verticalLayout->addLayout(hLayout);


        retranslateUi(YouDaoWidget);

        stackedWidget->setCurrentIndex(7);


        QMetaObject::connectSlotsByName(YouDaoWidget);
    } // setupUi

    void retranslateUi(QWidget *YouDaoWidget)
    {
        YouDaoWidget->setWindowTitle(QApplication::translate("YouDaoWidget", "YouDaoWidget", Q_NULLPTR));
        label_logo->setText(QString());
        btn_pre->setText(QString());
        btn_next->setText(QString());
        btn_history->setText(QString());
        btn_login->setText(QString());
        btn_mini->setText(QString());
        btn_min->setText(QString());
        btn_max->setText(QString());
        btn_close->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class YouDaoWidget: public Ui_YouDaoWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_YOUDAOWIDGET_H
