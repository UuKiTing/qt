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
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UISearch
{
public:

    void setupUi(QWidget *UISearch)
    {
        if (UISearch->objectName().isEmpty())
            UISearch->setObjectName("UISearch");
        UISearch->resize(400, 300);

        retranslateUi(UISearch);

        QMetaObject::connectSlotsByName(UISearch);
    } // setupUi

    void retranslateUi(QWidget *UISearch)
    {
        UISearch->setWindowTitle(QCoreApplication::translate("UISearch", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UISearch: public Ui_UISearch {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UISEARCH_H
