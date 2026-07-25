/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *myWidget;
    QLineEdit *lineEdit;
    QLabel *label;
    QPushButton *cancelBtn;
    QPushButton *acceptBtn;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName("Dialog");
        Dialog->resize(337, 201);
        horizontalLayout = new QHBoxLayout(Dialog);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        myWidget = new QWidget(Dialog);
        myWidget->setObjectName("myWidget");
        myWidget->setStyleSheet(QString::fromUtf8("QWidget#myWidget { \n"
"	background-color: white; \n"
"	border-radius: 12px; \n"
"	border: 1.5px solid rgb(80, 158, 247);\n"
"}"));
        lineEdit = new QLineEdit(myWidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(30, 70, 281, 41));
        lineEdit->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"border-radius: 5px;\n"
"padding-left: 10px;\n"
"background-color: white;\n"
"border: 1.5px solid #D0D5DD;\n"
"color: #333333;\n"
"}\n"
""));
        label = new QLabel(myWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 10, 81, 31));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("color: black;"));
        cancelBtn = new QPushButton(myWidget);
        cancelBtn->setObjectName("cancelBtn");
        cancelBtn->setGeometry(QRect(120, 150, 81, 31));
        cancelBtn->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        cancelBtn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"border-radius: 10px;\n"
"background-color: rgb(175, 177, 179);\n"
"color: black;\n"
"}"));
        acceptBtn = new QPushButton(myWidget);
        acceptBtn->setObjectName("acceptBtn");
        acceptBtn->setGeometry(QRect(230, 150, 81, 31));
        acceptBtn->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        acceptBtn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"border-radius: 10px;\n"
"background-color: rgb(74, 144, 226);\n"
"color: white;\n"
"}"));

        horizontalLayout->addWidget(myWidget);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        lineEdit->setPlaceholderText(QCoreApplication::translate("Dialog", "\350\257\267\350\276\223\345\205\245\346\255\214\345\215\225\345\220\215", nullptr));
        label->setText(QCoreApplication::translate("Dialog", "\345\210\233\345\273\272\346\255\214\345\215\225", nullptr));
        cancelBtn->setText(QCoreApplication::translate("Dialog", "\345\217\226\346\266\210", nullptr));
        acceptBtn->setText(QCoreApplication::translate("Dialog", "\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
