/********************************************************************************
** Form generated from reading UI file 'groupwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GROUPWINDOW_H
#define UI_GROUPWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GroupWindow
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *lineEdit_group;
    QWidget *widget1;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit_username;
    QWidget *widget2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QListWidget *listWidget;
    QWidget *widget3;
    QHBoxLayout *horizontalLayout;
    QPushButton *AddButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *confirmButton;

    void setupUi(QWidget *GroupWindow)
    {
        if (GroupWindow->objectName().isEmpty())
            GroupWindow->setObjectName("GroupWindow");
        GroupWindow->resize(400, 447);
        widget = new QWidget(GroupWindow);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(20, 10, 351, 51));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        lineEdit_group = new QLineEdit(widget);
        lineEdit_group->setObjectName("lineEdit_group");

        verticalLayout->addWidget(lineEdit_group);

        widget1 = new QWidget(GroupWindow);
        widget1->setObjectName("widget1");
        widget1->setGeometry(QRect(20, 80, 351, 51));
        verticalLayout_2 = new QVBoxLayout(widget1);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(widget1);
        label_2->setObjectName("label_2");

        verticalLayout_2->addWidget(label_2);

        lineEdit_username = new QLineEdit(widget1);
        lineEdit_username->setObjectName("lineEdit_username");

        verticalLayout_2->addWidget(lineEdit_username);

        widget2 = new QWidget(GroupWindow);
        widget2->setObjectName("widget2");
        widget2->setGeometry(QRect(20, 160, 351, 217));
        verticalLayout_3 = new QVBoxLayout(widget2);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(widget2);
        label_3->setObjectName("label_3");

        verticalLayout_3->addWidget(label_3);

        listWidget = new QListWidget(widget2);
        listWidget->setObjectName("listWidget");

        verticalLayout_3->addWidget(listWidget);

        widget3 = new QWidget(GroupWindow);
        widget3->setObjectName("widget3");
        widget3->setGeometry(QRect(39, 400, 311, 27));
        horizontalLayout = new QHBoxLayout(widget3);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        AddButton = new QPushButton(widget3);
        AddButton->setObjectName("AddButton");

        horizontalLayout->addWidget(AddButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        confirmButton = new QPushButton(widget3);
        confirmButton->setObjectName("confirmButton");

        horizontalLayout->addWidget(confirmButton);


        retranslateUi(GroupWindow);

        QMetaObject::connectSlotsByName(GroupWindow);
    } // setupUi

    void retranslateUi(QWidget *GroupWindow)
    {
        GroupWindow->setWindowTitle(QCoreApplication::translate("GroupWindow", "Form", nullptr));
        label->setText(QCoreApplication::translate("GroupWindow", "Group name", nullptr));
        lineEdit_group->setPlaceholderText(QCoreApplication::translate("GroupWindow", "Group name...", nullptr));
        label_2->setText(QCoreApplication::translate("GroupWindow", "Friend add to group", nullptr));
        lineEdit_username->setPlaceholderText(QCoreApplication::translate("GroupWindow", "Display name...", nullptr));
        label_3->setText(QCoreApplication::translate("GroupWindow", "Selected", nullptr));
        AddButton->setText(QCoreApplication::translate("GroupWindow", "Add", nullptr));
        confirmButton->setText(QCoreApplication::translate("GroupWindow", "Ok", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GroupWindow: public Ui_GroupWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GROUPWINDOW_H
