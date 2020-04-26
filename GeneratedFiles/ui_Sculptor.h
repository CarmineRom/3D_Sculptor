/********************************************************************************
** Form generated from reading UI file 'Sculptor.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCULPTOR_H
#define UI_SCULPTOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SculptorClass
{
public:

    void setupUi(QWidget *SculptorClass)
    {
        if (SculptorClass->objectName().isEmpty())
            SculptorClass->setObjectName(QStringLiteral("SculptorClass"));
        SculptorClass->resize(600, 400);

        retranslateUi(SculptorClass);

        QMetaObject::connectSlotsByName(SculptorClass);
    } // setupUi

    void retranslateUi(QWidget *SculptorClass)
    {
        SculptorClass->setWindowTitle(QApplication::translate("SculptorClass", "Sculptor", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SculptorClass: public Ui_SculptorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCULPTOR_H
