/********************************************************************************
** Form generated from reading UI file 'GaitUI.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAITUI_H
#define UI_GAITUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GaitUIClass
{
public:
    QWidget *centralWidget;
    QPushButton *loadModelBtn;
    QPushButton *addToDataBaseBtn;
    QPushButton *recognitionBtn;
    QPushButton *deleteDataBaseBtn;
    QLabel *database_count_label;
    QTextEdit *database_number_edit;
    QLabel *recognition_obj_label;
    QTextEdit *recognition_obj_edit;
    QLabel *image_show_label;
    QProgressBar *progressBar;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GaitUIClass)
    {
        if (GaitUIClass->objectName().isEmpty())
            GaitUIClass->setObjectName(QStringLiteral("GaitUIClass"));
        GaitUIClass->resize(672, 372);
        QFont font;
        font.setFamily(QStringLiteral("Consolas"));
        font.setPointSize(9);
        font.setBold(false);
        font.setWeight(50);
        GaitUIClass->setFont(font);
        GaitUIClass->setLayoutDirection(Qt::RightToLeft);
        GaitUIClass->setAutoFillBackground(false);
        centralWidget = new QWidget(GaitUIClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        loadModelBtn = new QPushButton(centralWidget);
        loadModelBtn->setObjectName(QStringLiteral("loadModelBtn"));
        loadModelBtn->setGeometry(QRect(546, 12, 113, 34));
        loadModelBtn->setCheckable(false);
        addToDataBaseBtn = new QPushButton(centralWidget);
        addToDataBaseBtn->setObjectName(QStringLiteral("addToDataBaseBtn"));
        addToDataBaseBtn->setGeometry(QRect(546, 56, 114, 37));
        recognitionBtn = new QPushButton(centralWidget);
        recognitionBtn->setObjectName(QStringLiteral("recognitionBtn"));
        recognitionBtn->setGeometry(QRect(546, 103, 114, 38));
        deleteDataBaseBtn = new QPushButton(centralWidget);
        deleteDataBaseBtn->setObjectName(QStringLiteral("deleteDataBaseBtn"));
        deleteDataBaseBtn->setGeometry(QRect(547, 151, 113, 37));
        database_count_label = new QLabel(centralWidget);
        database_count_label->setObjectName(QStringLiteral("database_count_label"));
        database_count_label->setGeometry(QRect(552, 190, 104, 20));
        database_count_label->setLayoutDirection(Qt::RightToLeft);
        database_count_label->setAlignment(Qt::AlignCenter);
        database_number_edit = new QTextEdit(centralWidget);
        database_number_edit->setObjectName(QStringLiteral("database_number_edit"));
        database_number_edit->setGeometry(QRect(550, 213, 108, 30));
        database_number_edit->setLineWrapMode(QTextEdit::WidgetWidth);
        database_number_edit->setReadOnly(true);
        recognition_obj_label = new QLabel(centralWidget);
        recognition_obj_label->setObjectName(QStringLiteral("recognition_obj_label"));
        recognition_obj_label->setGeometry(QRect(552, 244, 104, 20));
        recognition_obj_label->setLayoutDirection(Qt::RightToLeft);
        recognition_obj_label->setAlignment(Qt::AlignCenter);
        recognition_obj_edit = new QTextEdit(centralWidget);
        recognition_obj_edit->setObjectName(QStringLiteral("recognition_obj_edit"));
        recognition_obj_edit->setGeometry(QRect(550, 268, 108, 30));
        recognition_obj_edit->setReadOnly(true);
        image_show_label = new QLabel(centralWidget);
        image_show_label->setObjectName(QStringLiteral("image_show_label"));
        image_show_label->setGeometry(QRect(40, 20, 481, 241));
        image_show_label->setAlignment(Qt::AlignCenter);
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(80, 280, 431, 23));
        progressBar->setLayoutDirection(Qt::LeftToRight);
        progressBar->setValue(0);
        GaitUIClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(GaitUIClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 672, 23));
        GaitUIClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(GaitUIClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        GaitUIClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(GaitUIClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        GaitUIClass->setStatusBar(statusBar);

        retranslateUi(GaitUIClass);

        QMetaObject::connectSlotsByName(GaitUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *GaitUIClass)
    {
        GaitUIClass->setWindowTitle(QApplication::translate("GaitUIClass", "GaitUI", Q_NULLPTR));
        loadModelBtn->setText(QApplication::translate("GaitUIClass", "Load Model", Q_NULLPTR));
        addToDataBaseBtn->setText(QApplication::translate("GaitUIClass", "Add To DataBase", Q_NULLPTR));
        recognitionBtn->setText(QApplication::translate("GaitUIClass", "Recognition", Q_NULLPTR));
        deleteDataBaseBtn->setText(QApplication::translate("GaitUIClass", "Delete DataBase", Q_NULLPTR));
        database_count_label->setText(QApplication::translate("GaitUIClass", "DataBase Count", Q_NULLPTR));
        recognition_obj_label->setText(QApplication::translate("GaitUIClass", "RecognitionOBJ", Q_NULLPTR));
        image_show_label->setText(QApplication::translate("GaitUIClass", "SequenceShowArea", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class GaitUIClass: public Ui_GaitUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAITUI_H
