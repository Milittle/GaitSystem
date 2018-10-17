/********************************************************************************
** Form generated from reading UI file 'GaitUI.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAITUI_H
#define UI_GAITUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
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
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QPushButton *loadModelBtn;
    QPushButton *addToDataBaseBtn;
    QPushButton *recognitionBtn;
    QPushButton *deleteDataBaseBtn;
    QLabel *database_count_label;
    QLabel *image_show_label;
    QLabel *recognition_obj_label;
    QTextEdit *database_number_edit;
    QProgressBar *progressBar;
    QTextEdit *recognition_obj_edit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GaitUIClass)
    {
        if (GaitUIClass->objectName().isEmpty())
            GaitUIClass->setObjectName(QStringLiteral("GaitUIClass"));
        GaitUIClass->resize(758, 397);
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
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        loadModelBtn = new QPushButton(centralWidget);
        loadModelBtn->setObjectName(QStringLiteral("loadModelBtn"));
        loadModelBtn->setCheckable(false);

        gridLayout->addWidget(loadModelBtn, 0, 0, 1, 1);

        addToDataBaseBtn = new QPushButton(centralWidget);
        addToDataBaseBtn->setObjectName(QStringLiteral("addToDataBaseBtn"));

        gridLayout->addWidget(addToDataBaseBtn, 1, 0, 1, 1);

        recognitionBtn = new QPushButton(centralWidget);
        recognitionBtn->setObjectName(QStringLiteral("recognitionBtn"));

        gridLayout->addWidget(recognitionBtn, 2, 0, 1, 1);

        deleteDataBaseBtn = new QPushButton(centralWidget);
        deleteDataBaseBtn->setObjectName(QStringLiteral("deleteDataBaseBtn"));

        gridLayout->addWidget(deleteDataBaseBtn, 3, 0, 1, 1);

        database_count_label = new QLabel(centralWidget);
        database_count_label->setObjectName(QStringLiteral("database_count_label"));
        database_count_label->setLayoutDirection(Qt::RightToLeft);
        database_count_label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(database_count_label, 4, 0, 1, 1);

        image_show_label = new QLabel(centralWidget);
        image_show_label->setObjectName(QStringLiteral("image_show_label"));
        image_show_label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(image_show_label, 0, 1, 7, 1);

        recognition_obj_label = new QLabel(centralWidget);
        recognition_obj_label->setObjectName(QStringLiteral("recognition_obj_label"));
        recognition_obj_label->setLayoutDirection(Qt::RightToLeft);
        recognition_obj_label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(recognition_obj_label, 6, 0, 1, 1);

        database_number_edit = new QTextEdit(centralWidget);
        database_number_edit->setObjectName(QStringLiteral("database_number_edit"));
        database_number_edit->setLineWrapMode(QTextEdit::WidgetWidth);
        database_number_edit->setReadOnly(true);

        gridLayout->addWidget(database_number_edit, 5, 0, 1, 1);

        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setLayoutDirection(Qt::LeftToRight);
        progressBar->setValue(0);

        gridLayout->addWidget(progressBar, 7, 1, 1, 1);

        recognition_obj_edit = new QTextEdit(centralWidget);
        recognition_obj_edit->setObjectName(QStringLiteral("recognition_obj_edit"));
        recognition_obj_edit->setReadOnly(true);

        gridLayout->addWidget(recognition_obj_edit, 7, 0, 1, 1);

        gridLayout->setRowStretch(0, 2);
        gridLayout->setRowStretch(1, 2);
        gridLayout->setRowStretch(2, 2);
        gridLayout->setRowStretch(3, 2);
        gridLayout->setRowStretch(4, 2);
        gridLayout->setRowStretch(5, 2);
        gridLayout->setRowStretch(6, 1);
        gridLayout->setRowStretch(7, 1);
        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 3);

        horizontalLayout->addLayout(gridLayout);

        GaitUIClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(GaitUIClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 758, 23));
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
        GaitUIClass->setWindowTitle(QApplication::translate("GaitUIClass", "GaitUI", nullptr));
        loadModelBtn->setText(QApplication::translate("GaitUIClass", "Load Model", nullptr));
        addToDataBaseBtn->setText(QApplication::translate("GaitUIClass", "Add To DataBase", nullptr));
        recognitionBtn->setText(QApplication::translate("GaitUIClass", "Recognition", nullptr));
        deleteDataBaseBtn->setText(QApplication::translate("GaitUIClass", "Delete DataBase", nullptr));
        database_count_label->setText(QApplication::translate("GaitUIClass", "DataBase Count", nullptr));
        image_show_label->setText(QApplication::translate("GaitUIClass", "SequenceShowArea", nullptr));
        recognition_obj_label->setText(QApplication::translate("GaitUIClass", "RecognitionOBJ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GaitUIClass: public Ui_GaitUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAITUI_H
