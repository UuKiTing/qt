/********************************************************************************
** Form generated from reading UI file 'uisidebar.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UISIDEBAR_H
#define UI_UISIDEBAR_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UISideBar
{
public:
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QPushButton *avatarBtn;
    QToolButton *homeBtn;
    QToolButton *collectBtn;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *UISideBar)
    {
        if (UISideBar->objectName().isEmpty())
            UISideBar->setObjectName("UISideBar");
        UISideBar->resize(73, 465);
        UISideBar->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_2 = new QVBoxLayout(UISideBar);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(UISideBar);
        widget->setObjectName("widget");
        widget->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	background-color: #E9E9E9;\n"
"    border-radius: 10px;\n"
"	padding: 5px;\n"
"	min-height: 45px;\n"
"	max-height:45px;\n"
"	min-width: 45px;\n"
"	max-width: 45px;\n"
"}\n"
"QToolButton:checked {\n"
"    background-color: #D8D8D8;\n"
"}\n"
"\n"
"QToolButton:pressed {\n"
"	padding: 5px;\n"
"}\n"
"\n"
"background-color: #F3F3F3;\n"
""));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(10);
        verticalLayout->setObjectName("verticalLayout");
        avatarBtn = new QPushButton(widget);
        avatarBtn->setObjectName("avatarBtn");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(40);
        sizePolicy.setVerticalStretch(40);
        sizePolicy.setHeightForWidth(avatarBtn->sizePolicy().hasHeightForWidth());
        avatarBtn->setSizePolicy(sizePolicy);
        avatarBtn->setMinimumSize(QSize(52, 52));
        avatarBtn->setMaximumSize(QSize(52, 52));
        avatarBtn->setStyleSheet(QString::fromUtf8(""));
        avatarBtn->setIconSize(QSize(30, 30));
        avatarBtn->setFlat(true);

        verticalLayout->addWidget(avatarBtn);

        homeBtn = new QToolButton(widget);
        homeBtn->setObjectName("homeBtn");
        homeBtn->setMinimumSize(QSize(55, 55));
        homeBtn->setMaximumSize(QSize(55, 55));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/homeSelect.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        homeBtn->setIcon(icon);
        homeBtn->setIconSize(QSize(30, 30));
        homeBtn->setCheckable(true);
        homeBtn->setChecked(true);

        verticalLayout->addWidget(homeBtn);

        collectBtn = new QToolButton(widget);
        collectBtn->setObjectName("collectBtn");
        collectBtn->setMinimumSize(QSize(55, 55));
        collectBtn->setMaximumSize(QSize(55, 55));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icon/dislove.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        collectBtn->setIcon(icon1);
        collectBtn->setIconSize(QSize(22, 22));
        collectBtn->setCheckable(true);
        collectBtn->setChecked(false);

        verticalLayout->addWidget(collectBtn);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        verticalLayout_2->addWidget(widget);


        retranslateUi(UISideBar);

        QMetaObject::connectSlotsByName(UISideBar);
    } // setupUi

    void retranslateUi(QWidget *UISideBar)
    {
        UISideBar->setWindowTitle(QCoreApplication::translate("UISideBar", "Form", nullptr));
        avatarBtn->setText(QString());
        homeBtn->setText(QString());
        collectBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class UISideBar: public Ui_UISideBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UISIDEBAR_H
