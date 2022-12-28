/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *arqCSV;
    QPlainTextEdit *arqSelect;
    QLabel *textoTituloTabela;
    QLineEdit *titulo;
    QLabel *label;
    QLabel *label_2;
    QPlainTextEdit *tabConvert;
    QGroupBox *groupBox;
    QRadioButton *radio_tab;
    QRadioButton *rd_quad;
    QPushButton *arqxlsx;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(441, 643);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        arqCSV = new QPushButton(centralwidget);
        arqCSV->setObjectName(QString::fromUtf8("arqCSV"));
        arqCSV->setGeometry(QRect(30, 170, 171, 41));
        arqSelect = new QPlainTextEdit(centralwidget);
        arqSelect->setObjectName(QString::fromUtf8("arqSelect"));
        arqSelect->setGeometry(QRect(30, 260, 381, 51));
        textoTituloTabela = new QLabel(centralwidget);
        textoTituloTabela->setObjectName(QString::fromUtf8("textoTituloTabela"));
        textoTituloTabela->setGeometry(QRect(20, 20, 101, 16));
        titulo = new QLineEdit(centralwidget);
        titulo->setObjectName(QString::fromUtf8("titulo"));
        titulo->setGeometry(QRect(140, 20, 271, 23));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 240, 141, 16));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 330, 141, 16));
        tabConvert = new QPlainTextEdit(centralwidget);
        tabConvert->setObjectName(QString::fromUtf8("tabConvert"));
        tabConvert->setGeometry(QRect(30, 350, 381, 241));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(30, 80, 361, 61));
        radio_tab = new QRadioButton(groupBox);
        radio_tab->setObjectName(QString::fromUtf8("radio_tab"));
        radio_tab->setGeometry(QRect(20, 30, 106, 22));
        radio_tab->setChecked(true);
        rd_quad = new QRadioButton(groupBox);
        rd_quad->setObjectName(QString::fromUtf8("rd_quad"));
        rd_quad->setGeometry(QRect(220, 30, 106, 22));
        arqxlsx = new QPushButton(centralwidget);
        arqxlsx->setObjectName(QString::fromUtf8("arqxlsx"));
        arqxlsx->setGeometry(QRect(220, 170, 191, 41));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 441, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        arqCSV->setText(QCoreApplication::translate("MainWindow", "Insira arquivos .CSV", nullptr));
        textoTituloTabela->setText(QCoreApplication::translate("MainWindow", "Titulo da tabela", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Arquivos convertidos", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Tabela convertida", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Estilo da Tabela", nullptr));
        radio_tab->setText(QCoreApplication::translate("MainWindow", "Tabela", nullptr));
        rd_quad->setText(QCoreApplication::translate("MainWindow", "Quadro", nullptr));
        arqxlsx->setText(QCoreApplication::translate("MainWindow", "Insira arquivos .xlsx", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
