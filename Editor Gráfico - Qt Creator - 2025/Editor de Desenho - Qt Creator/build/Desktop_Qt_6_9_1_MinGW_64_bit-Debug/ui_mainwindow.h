/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "drawwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    DrawWidget *drawArea;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QPushButton *btnLimpar;
    QPushButton *btnCor;
    QPushButton *btnBorracha;
    QComboBox *comboForma;
    QPushButton *btnTamanho;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(728, 510);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        drawArea = new DrawWidget(centralwidget);
        drawArea->setObjectName("drawArea");
        drawArea->setGeometry(QRect(-170, 0, 1241, 611));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(drawArea->sizePolicy().hasHeightForWidth());
        drawArea->setSizePolicy(sizePolicy);
        widget = new QWidget(drawArea);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(180, 0, 84, 146));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName("verticalLayout");
        btnLimpar = new QPushButton(widget);
        btnLimpar->setObjectName("btnLimpar");

        verticalLayout->addWidget(btnLimpar);

        btnCor = new QPushButton(widget);
        btnCor->setObjectName("btnCor");

        verticalLayout->addWidget(btnCor);

        btnBorracha = new QPushButton(widget);
        btnBorracha->setObjectName("btnBorracha");

        verticalLayout->addWidget(btnBorracha);

        comboForma = new QComboBox(widget);
        comboForma->addItem(QString());
        comboForma->addItem(QString());
        comboForma->addItem(QString());
        comboForma->addItem(QString());
        comboForma->setObjectName("comboForma");

        verticalLayout->addWidget(comboForma);

        btnTamanho = new QPushButton(widget);
        btnTamanho->setObjectName("btnTamanho");

        verticalLayout->addWidget(btnTamanho);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 728, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btnLimpar->setText(QCoreApplication::translate("MainWindow", "Limpar", nullptr));
        btnCor->setText(QCoreApplication::translate("MainWindow", "Mudar Cor", nullptr));
        btnBorracha->setText(QCoreApplication::translate("MainWindow", "Borracha", nullptr));
        comboForma->setItemText(0, QCoreApplication::translate("MainWindow", "Livre", nullptr));
        comboForma->setItemText(1, QCoreApplication::translate("MainWindow", "Linha", nullptr));
        comboForma->setItemText(2, QCoreApplication::translate("MainWindow", "Ret\303\242ngulo", nullptr));
        comboForma->setItemText(3, QCoreApplication::translate("MainWindow", "C\303\255rculo", nullptr));

        btnTamanho->setText(QCoreApplication::translate("MainWindow", "Tamanho", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
