/********************************************************************************
** Form generated from reading UI file 'searchedit.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHEDIT_H
#define UI_SEARCHEDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SearchEdit
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *label_left;
    QLabel *label_model;
    QPushButton *btn_drop;
    QLabel *label_vline;
    QLineEdit *line_search;
    QPushButton *btn_search;
    QLabel *label_right;

    void setupUi(QFrame *SearchEdit)
    {
        if (SearchEdit->objectName().isEmpty())
            SearchEdit->setObjectName(QStringLiteral("SearchEdit"));
        SearchEdit->resize(400, 92);
        SearchEdit->setFrameShape(QFrame::StyledPanel);
        SearchEdit->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(SearchEdit);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_left = new QLabel(SearchEdit);
        label_left->setObjectName(QStringLiteral("label_left"));
        label_left->setMinimumSize(QSize(30, 60));
        label_left->setStyleSheet(QStringLiteral(""));

        horizontalLayout->addWidget(label_left);

        label_model = new QLabel(SearchEdit);
        label_model->setObjectName(QStringLiteral("label_model"));
        label_model->setStyleSheet(QStringLiteral(""));

        horizontalLayout->addWidget(label_model);

        btn_drop = new QPushButton(SearchEdit);
        btn_drop->setObjectName(QStringLiteral("btn_drop"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btn_drop->sizePolicy().hasHeightForWidth());
        btn_drop->setSizePolicy(sizePolicy);
        btn_drop->setMaximumSize(QSize(10, 16777215));
        btn_drop->setStyleSheet(QStringLiteral(""));
        QIcon icon;
        icon.addFile(QStringLiteral(":/image/drop.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_drop->setIcon(icon);

        horizontalLayout->addWidget(btn_drop);

        label_vline = new QLabel(SearchEdit);
        label_vline->setObjectName(QStringLiteral("label_vline"));
        label_vline->setMinimumSize(QSize(20, 0));
        QFont font;
        font.setFamily(QStringLiteral("04b_21"));
        font.setPointSize(10);
        label_vline->setFont(font);
        label_vline->setStyleSheet(QStringLiteral(""));
        label_vline->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_vline);

        line_search = new QLineEdit(SearchEdit);
        line_search->setObjectName(QStringLiteral("line_search"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(line_search->sizePolicy().hasHeightForWidth());
        line_search->setSizePolicy(sizePolicy1);
        line_search->setStyleSheet(QStringLiteral(""));

        horizontalLayout->addWidget(line_search);

        btn_search = new QPushButton(SearchEdit);
        btn_search->setObjectName(QStringLiteral("btn_search"));
        sizePolicy.setHeightForWidth(btn_search->sizePolicy().hasHeightForWidth());
        btn_search->setSizePolicy(sizePolicy);
        btn_search->setMaximumSize(QSize(999, 999));
        btn_search->setStyleSheet(QStringLiteral(""));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/image/search.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_search->setIcon(icon1);

        horizontalLayout->addWidget(btn_search);

        label_right = new QLabel(SearchEdit);
        label_right->setObjectName(QStringLiteral("label_right"));
        label_right->setMinimumSize(QSize(17, 0));
        label_right->setStyleSheet(QStringLiteral(""));

        horizontalLayout->addWidget(label_right);


        retranslateUi(SearchEdit);

        QMetaObject::connectSlotsByName(SearchEdit);
    } // setupUi

    void retranslateUi(QFrame *SearchEdit)
    {
        SearchEdit->setWindowTitle(QApplication::translate("SearchEdit", "Frame", Q_NULLPTR));
        label_left->setText(QString());
        label_model->setText(QApplication::translate("SearchEdit", "\350\213\261\346\261\211\344\272\222\350\257\221 ", Q_NULLPTR));
        btn_drop->setText(QString());
        label_vline->setText(QApplication::translate("SearchEdit", "|", Q_NULLPTR));
        btn_search->setText(QString());
        label_right->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SearchEdit: public Ui_SearchEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHEDIT_H
