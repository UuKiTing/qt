/********************************************************************************
** Form generated from reading UI file 'uisearch.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UISEARCH_H
#define UI_UISEARCH_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UISearch
{
public:
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_2;
    QLineEdit *searchBar;
    QPushButton *searchBtn;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *UISearch)
    {
        if (UISearch->objectName().isEmpty())
            UISearch->setObjectName("UISearch");
        UISearch->resize(679, 58);
        UISearch->setFocusPolicy(Qt::FocusPolicy::ClickFocus);
        horizontalLayout_2 = new QHBoxLayout(UISearch);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(UISearch);
        widget->setObjectName("widget");
        widget->setStyleSheet(QString::fromUtf8("background-color: white;"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setMinimumSize(QSize(30, 30));
        pushButton_2->setMaximumSize(QSize(30, 30));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/flush.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_2->setIcon(icon);
        pushButton_2->setIconSize(QSize(17, 17));
        pushButton_2->setFlat(true);

        horizontalLayout->addWidget(pushButton_2);

        searchBar = new QLineEdit(widget);
        searchBar->setObjectName("searchBar");
        searchBar->setMinimumSize(QSize(300, 30));
        searchBar->setMaximumSize(QSize(300, 16777215));
        searchBar->setFocusPolicy(Qt::FocusPolicy::ClickFocus);
        searchBar->setStyleSheet(QString::fromUtf8("border-radius: 5px;\n"
"background-color: #E3E3E3;\n"
"padding-left: 5px;"));

        horizontalLayout->addWidget(searchBar);

        searchBtn = new QPushButton(widget);
        searchBtn->setObjectName("searchBtn");
        searchBtn->setMinimumSize(QSize(30, 30));
        searchBtn->setMaximumSize(QSize(30, 30));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icon/search.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        searchBtn->setIcon(icon1);
        searchBtn->setIconSize(QSize(22, 22));
        searchBtn->setFlat(true);

        horizontalLayout->addWidget(searchBtn);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        horizontalLayout_2->addWidget(widget);


        retranslateUi(UISearch);

        QMetaObject::connectSlotsByName(UISearch);
    } // setupUi

    void retranslateUi(QWidget *UISearch)
    {
        UISearch->setWindowTitle(QCoreApplication::translate("UISearch", "Form", nullptr));
        pushButton_2->setText(QString());
        searchBar->setPlaceholderText(QCoreApplication::translate("UISearch", "\346\220\234\347\264\242\351\237\263\344\271\220", nullptr));
        searchBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class UISearch: public Ui_UISearch {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UISEARCH_H
