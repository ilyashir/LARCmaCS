/********************************************************************************
** Form generated from reading UI file 'larcmacs.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LARCMACS_H
#define UI_LARCMACS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LARCmaCS
{
public:

    void setupUi(QWidget *LARCmaCS)
    {
        if (LARCmaCS->objectName().isEmpty())
            LARCmaCS->setObjectName(QString::fromUtf8("LARCmaCS"));
        LARCmaCS->resize(400, 300);

        retranslateUi(LARCmaCS);

        QMetaObject::connectSlotsByName(LARCmaCS);
    } // setupUi

    void retranslateUi(QWidget *LARCmaCS)
    {
        LARCmaCS->setWindowTitle(QApplication::translate("LARCmaCS", "LARCmaCS", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class LARCmaCS: public Ui_LARCmaCS {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LARCMACS_H
