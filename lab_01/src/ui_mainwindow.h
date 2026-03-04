/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QFormLayout *formLayout_3;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QPushButton *load_btn;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QPushButton *move_btn;
    QLabel *dz_label;
    QLineEdit *dy_lineEdit;
    QLineEdit *dx_lineEdit;
    QLabel *dx_label;
    QLabel *dy_label;
    QLineEdit *dz_lineEdit;
    QGroupBox *groupBox_3;
    QFormLayout *formLayout;
    QLabel *kx_label;
    QLineEdit *kx_lineEdit;
    QLabel *ky_label;
    QLabel *kz_label;
    QLineEdit *kz_lineEdit;
    QPushButton *scale_btn;
    QLineEdit *ky_lineEdit;
    QGroupBox *groupBox_4;
    QFormLayout *formLayout_2;
    QLabel *xa_label;
    QLineEdit *xa_lineEdit;
    QLabel *ya_label;
    QLineEdit *ya_lineEdit;
    QLineEdit *za_lineEdit;
    QPushButton *turn_btn;
    QLabel *za_label;
    QGraphicsView *graphicsView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(1214, 813);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setLayoutDirection(Qt::LeftToRight);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        formLayout_3 = new QFormLayout(centralwidget);
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        load_btn = new QPushButton(groupBox);
        load_btn->setObjectName(QString::fromUtf8("load_btn"));
        sizePolicy.setHeightForWidth(load_btn->sizePolicy().hasHeightForWidth());
        load_btn->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(load_btn);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        move_btn = new QPushButton(groupBox_2);
        move_btn->setObjectName(QString::fromUtf8("move_btn"));

        gridLayout->addWidget(move_btn, 3, 0, 1, 2);

        dz_label = new QLabel(groupBox_2);
        dz_label->setObjectName(QString::fromUtf8("dz_label"));

        gridLayout->addWidget(dz_label, 2, 0, 1, 1);

        dy_lineEdit = new QLineEdit(groupBox_2);
        dy_lineEdit->setObjectName(QString::fromUtf8("dy_lineEdit"));

        gridLayout->addWidget(dy_lineEdit, 1, 1, 1, 1);

        dx_lineEdit = new QLineEdit(groupBox_2);
        dx_lineEdit->setObjectName(QString::fromUtf8("dx_lineEdit"));

        gridLayout->addWidget(dx_lineEdit, 0, 1, 1, 1);

        dx_label = new QLabel(groupBox_2);
        dx_label->setObjectName(QString::fromUtf8("dx_label"));

        gridLayout->addWidget(dx_label, 0, 0, 1, 1);

        dy_label = new QLabel(groupBox_2);
        dy_label->setObjectName(QString::fromUtf8("dy_label"));

        gridLayout->addWidget(dy_label, 1, 0, 1, 1);

        dz_lineEdit = new QLineEdit(groupBox_2);
        dz_lineEdit->setObjectName(QString::fromUtf8("dz_lineEdit"));

        gridLayout->addWidget(dz_lineEdit, 2, 1, 1, 1);


        verticalLayout->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        formLayout = new QFormLayout(groupBox_3);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        kx_label = new QLabel(groupBox_3);
        kx_label->setObjectName(QString::fromUtf8("kx_label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, kx_label);

        kx_lineEdit = new QLineEdit(groupBox_3);
        kx_lineEdit->setObjectName(QString::fromUtf8("kx_lineEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, kx_lineEdit);

        ky_label = new QLabel(groupBox_3);
        ky_label->setObjectName(QString::fromUtf8("ky_label"));

        formLayout->setWidget(1, QFormLayout::LabelRole, ky_label);

        kz_label = new QLabel(groupBox_3);
        kz_label->setObjectName(QString::fromUtf8("kz_label"));

        formLayout->setWidget(2, QFormLayout::LabelRole, kz_label);

        kz_lineEdit = new QLineEdit(groupBox_3);
        kz_lineEdit->setObjectName(QString::fromUtf8("kz_lineEdit"));

        formLayout->setWidget(2, QFormLayout::FieldRole, kz_lineEdit);

        scale_btn = new QPushButton(groupBox_3);
        scale_btn->setObjectName(QString::fromUtf8("scale_btn"));

        formLayout->setWidget(3, QFormLayout::SpanningRole, scale_btn);

        ky_lineEdit = new QLineEdit(groupBox_3);
        ky_lineEdit->setObjectName(QString::fromUtf8("ky_lineEdit"));

        formLayout->setWidget(1, QFormLayout::FieldRole, ky_lineEdit);


        verticalLayout->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        formLayout_2 = new QFormLayout(groupBox_4);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        xa_label = new QLabel(groupBox_4);
        xa_label->setObjectName(QString::fromUtf8("xa_label"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, xa_label);

        xa_lineEdit = new QLineEdit(groupBox_4);
        xa_lineEdit->setObjectName(QString::fromUtf8("xa_lineEdit"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, xa_lineEdit);

        ya_label = new QLabel(groupBox_4);
        ya_label->setObjectName(QString::fromUtf8("ya_label"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, ya_label);

        ya_lineEdit = new QLineEdit(groupBox_4);
        ya_lineEdit->setObjectName(QString::fromUtf8("ya_lineEdit"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, ya_lineEdit);

        za_lineEdit = new QLineEdit(groupBox_4);
        za_lineEdit->setObjectName(QString::fromUtf8("za_lineEdit"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, za_lineEdit);

        turn_btn = new QPushButton(groupBox_4);
        turn_btn->setObjectName(QString::fromUtf8("turn_btn"));

        formLayout_2->setWidget(3, QFormLayout::SpanningRole, turn_btn);

        za_label = new QLabel(groupBox_4);
        za_label->setObjectName(QString::fromUtf8("za_label"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, za_label);


        verticalLayout->addWidget(groupBox_4);


        formLayout_3->setLayout(0, QFormLayout::LabelRole, verticalLayout);

        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        formLayout_3->setWidget(0, QFormLayout::FieldRole, graphicsView);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1214, 28));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "LAB_01", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\272\320\260", nullptr));
        load_btn->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\320\275\320\276\321\201", nullptr));
        move_btn->setText(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\320\275\320\265\321\201\321\202\320\270", nullptr));
        dz_label->setText(QCoreApplication::translate("MainWindow", "dz:", nullptr));
        dx_label->setText(QCoreApplication::translate("MainWindow", "dx:", nullptr));
        dy_label->setText(QCoreApplication::translate("MainWindow", "dy:", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "\320\234\320\260\321\201\321\210\321\202\320\260\320\261\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265", nullptr));
        kx_label->setText(QCoreApplication::translate("MainWindow", "kx:", nullptr));
        ky_label->setText(QCoreApplication::translate("MainWindow", "ky:", nullptr));
        kz_label->setText(QCoreApplication::translate("MainWindow", "kz:", nullptr));
        scale_btn->setText(QCoreApplication::translate("MainWindow", "\320\234\320\260\321\201\321\210\321\202\320\260\320\261\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\262\320\276\321\200\320\276\321\202 (\321\203\320\263\320\273\321\213 \320\262 \302\260)", nullptr));
        xa_label->setText(QCoreApplication::translate("MainWindow", "\320\277\320\276 x:", nullptr));
        ya_label->setText(QCoreApplication::translate("MainWindow", "\320\277\320\276 y:", nullptr));
        turn_btn->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\262\320\265\321\200\320\275\321\203\321\202\321\214", nullptr));
        za_label->setText(QCoreApplication::translate("MainWindow", "\320\277\320\276 z:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
