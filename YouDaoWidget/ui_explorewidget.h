/********************************************************************************
** Form generated from reading UI file 'explorewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXPLOREWIDGET_H
#define UI_EXPLOREWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ExploreWidget
{
public:
    QVBoxLayout *verticalLayout;
    QCheckBox *check_qc;
    QCheckBox *check_hc;

    void setupUi(QWidget *ExploreWidget)
    {
        if (ExploreWidget->objectName().isEmpty())
            ExploreWidget->setObjectName(QStringLiteral("ExploreWidget"));
        ExploreWidget->resize(184, 301);
        ExploreWidget->setStyleSheet(QStringLiteral(""));
        verticalLayout = new QVBoxLayout(ExploreWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(10, 0, 0, 0);
        check_qc = new QCheckBox(ExploreWidget);
        check_qc->setObjectName(QStringLiteral("check_qc"));
        check_qc->setMinimumSize(QSize(0, 40));

        verticalLayout->addWidget(check_qc);

        check_hc = new QCheckBox(ExploreWidget);
        check_hc->setObjectName(QStringLiteral("check_hc"));
        check_hc->setMinimumSize(QSize(0, 40));
        check_hc->setStyleSheet(QStringLiteral(""));

        verticalLayout->addWidget(check_hc);


        retranslateUi(ExploreWidget);

        QMetaObject::connectSlotsByName(ExploreWidget);
    } // setupUi

    void retranslateUi(QWidget *ExploreWidget)
    {
        ExploreWidget->setWindowTitle(QApplication::translate("ExploreWidget", "Form", Q_NULLPTR));
        check_qc->setText(QApplication::translate("ExploreWidget", "\345\217\226\350\257\215", Q_NULLPTR));
        check_hc->setText(QApplication::translate("ExploreWidget", "\345\210\222\350\257\215", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ExploreWidget: public Ui_ExploreWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXPLOREWIDGET_H
