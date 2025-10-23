/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_1_Ort_Anlegen;
    QAction *action_2_Laden;
    QAction *action_3_Speichern;
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QPushButton *pushButton_verschieben;
    QPushButton *pushButton_alle_Orte;
    QPushButton *pushButton_meinOrt;
    QPushButton *pushButton_Entfernung;
    QPushButton *Rooting;
    QPushButton *pushButton_Information;
    QLabel *label;
    QPushButton *Ort_Entfernen;
    QMenuBar *menubar;
    QMenu *menuMen;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1000, 700);
        action_1_Ort_Anlegen = new QAction(MainWindow);
        action_1_Ort_Anlegen->setObjectName("action_1_Ort_Anlegen");
        action_2_Laden = new QAction(MainWindow);
        action_2_Laden->setObjectName("action_2_Laden");
        action_3_Speichern = new QAction(MainWindow);
        action_3_Speichern->setObjectName("action_3_Speichern");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName("gridLayout_2");
        scrollArea = new QScrollArea(centralwidget);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(-61, -851, 1031, 1474));
        gridLayout = new QGridLayout(scrollAreaWidgetContents);
        gridLayout->setObjectName("gridLayout");
        pushButton_verschieben = new QPushButton(scrollAreaWidgetContents);
        pushButton_verschieben->setObjectName("pushButton_verschieben");

        gridLayout->addWidget(pushButton_verschieben, 4, 1, 1, 1);

        pushButton_alle_Orte = new QPushButton(scrollAreaWidgetContents);
        pushButton_alle_Orte->setObjectName("pushButton_alle_Orte");

        gridLayout->addWidget(pushButton_alle_Orte, 3, 1, 1, 1);

        pushButton_meinOrt = new QPushButton(scrollAreaWidgetContents);
        pushButton_meinOrt->setObjectName("pushButton_meinOrt");

        gridLayout->addWidget(pushButton_meinOrt, 6, 1, 1, 1);

        pushButton_Entfernung = new QPushButton(scrollAreaWidgetContents);
        pushButton_Entfernung->setObjectName("pushButton_Entfernung");

        gridLayout->addWidget(pushButton_Entfernung, 1, 1, 1, 1);

        Rooting = new QPushButton(scrollAreaWidgetContents);
        Rooting->setObjectName("Rooting");

        gridLayout->addWidget(Rooting, 7, 1, 1, 1);

        pushButton_Information = new QPushButton(scrollAreaWidgetContents);
        pushButton_Information->setObjectName("pushButton_Information");

        gridLayout->addWidget(pushButton_Information, 2, 1, 1, 1);

        label = new QLabel(scrollAreaWidgetContents);
        label->setObjectName("label");
        label->setPixmap(QPixmap(QString::fromUtf8(":/german_map/NicePng_germany-png_8664209.png")));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        Ort_Entfernen = new QPushButton(scrollAreaWidgetContents);
        Ort_Entfernen->setObjectName("Ort_Entfernen");

        gridLayout->addWidget(Ort_Entfernen, 8, 1, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout_2->addWidget(scrollArea, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1000, 21));
        menuMen = new QMenu(menubar);
        menuMen->setObjectName("menuMen");
        MainWindow->setMenuBar(menubar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);

        menubar->addAction(menuMen->menuAction());
        menuMen->addAction(action_1_Ort_Anlegen);
        menuMen->addAction(action_2_Laden);
        menuMen->addAction(action_3_Speichern);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        action_1_Ort_Anlegen->setText(QCoreApplication::translate("MainWindow", "(1) Ort Anlegen", nullptr));
        action_2_Laden->setText(QCoreApplication::translate("MainWindow", "(2) Laden ", nullptr));
        action_3_Speichern->setText(QCoreApplication::translate("MainWindow", "(3) Speichern", nullptr));
        pushButton_verschieben->setText(QCoreApplication::translate("MainWindow", "Verschieben", nullptr));
        pushButton_alle_Orte->setText(QCoreApplication::translate("MainWindow", "Alle Orte", nullptr));
        pushButton_meinOrt->setText(QCoreApplication::translate("MainWindow", "MeinOrt", nullptr));
        pushButton_Entfernung->setText(QCoreApplication::translate("MainWindow", "Entfernung", nullptr));
        Rooting->setText(QCoreApplication::translate("MainWindow", "Rooting", nullptr));
        pushButton_Information->setText(QCoreApplication::translate("MainWindow", "Information", nullptr));
        label->setText(QString());
        Ort_Entfernen->setText(QCoreApplication::translate("MainWindow", "Ort Entfernen", nullptr));
        menuMen->setTitle(QCoreApplication::translate("MainWindow", "Men\303\274", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
