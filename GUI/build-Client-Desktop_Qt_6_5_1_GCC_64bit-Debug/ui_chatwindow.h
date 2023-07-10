/********************************************************************************
** Form generated from reading UI file 'chatwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATWINDOW_H
#define UI_CHATWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatWindow
{
public:
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QTabWidget *tabWidget;
    QWidget *tab;
    QListWidget *listWidget;
    QWidget *tab_2;
    QListWidget *listWidget_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *serverIP;
    QLabel *label_2;
    QSpinBox *serverPort;
    QPushButton *connButton;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QTextEdit *convBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QLineEdit *messageBox;
    QPushButton *sendButton;
    QLineEdit *lineEdit;

    void setupUi(QWidget *ChatWindow)
    {
        if (ChatWindow->objectName().isEmpty())
            ChatWindow->setObjectName("ChatWindow");
        ChatWindow->resize(783, 505);
        QIcon icon;
        icon.addFile(QString::fromUtf8("chat.png"), QSize(), QIcon::Normal, QIcon::Off);
        ChatWindow->setWindowIcon(icon);
        layoutWidget = new QWidget(ChatWindow);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 10, 761, 481));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setHorizontalSpacing(60);
        gridLayout->setVerticalSpacing(0);
        gridLayout->setContentsMargins(30, 0, 0, 0);
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 0, 1, 1, 1);

        tabWidget = new QTabWidget(layoutWidget);
        tabWidget->setObjectName("tabWidget");
        tab = new QWidget();
        tab->setObjectName("tab");
        listWidget = new QListWidget(tab);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(0, 0, 191, 421));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        listWidget_2 = new QListWidget(tab_2);
        listWidget_2->setObjectName("listWidget_2");
        listWidget_2->setGeometry(QRect(0, 0, 191, 421));
        tabWidget->addTab(tab_2, QString());

        gridLayout->addWidget(tabWidget, 1, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(layoutWidget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        serverIP = new QLineEdit(layoutWidget);
        serverIP->setObjectName("serverIP");
        serverIP->setMaximumSize(QSize(150, 16777215));

        horizontalLayout->addWidget(serverIP);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName("label_2");

        horizontalLayout->addWidget(label_2);

        serverPort = new QSpinBox(layoutWidget);
        serverPort->setObjectName("serverPort");
        serverPort->setMinimumSize(QSize(60, 0));
        serverPort->setMinimum(1024);
        serverPort->setMaximum(65535);
        serverPort->setValue(50885);

        horizontalLayout->addWidget(serverPort);

        connButton = new QPushButton(layoutWidget);
        connButton->setObjectName("connButton");

        horizontalLayout->addWidget(connButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");

        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout);

        convBox = new QTextEdit(layoutWidget);
        convBox->setObjectName("convBox");
        convBox->setMaximumSize(QSize(16777215, 16777215));
        convBox->setReadOnly(true);

        verticalLayout_2->addWidget(convBox);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName("label_4");

        horizontalLayout_2->addWidget(label_4);

        messageBox = new QLineEdit(layoutWidget);
        messageBox->setObjectName("messageBox");

        horizontalLayout_2->addWidget(messageBox);

        sendButton = new QPushButton(layoutWidget);
        sendButton->setObjectName("sendButton");
        sendButton->setIcon(icon);

        horizontalLayout_2->addWidget(sendButton);


        verticalLayout_2->addLayout(horizontalLayout_2);


        gridLayout->addLayout(verticalLayout_2, 1, 1, 1, 1);

        lineEdit = new QLineEdit(layoutWidget);
        lineEdit->setObjectName("lineEdit");

        gridLayout->addWidget(lineEdit, 0, 0, 1, 1);


        retranslateUi(ChatWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ChatWindow);
    } // setupUi

    void retranslateUi(QWidget *ChatWindow)
    {
        ChatWindow->setWindowTitle(QCoreApplication::translate("ChatWindow", "Aloo!", nullptr));
        label_3->setText(QCoreApplication::translate("ChatWindow", "Choose a person to chat", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("ChatWindow", "Tab 1", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("ChatWindow", "Tab 2", nullptr));
        label->setText(QCoreApplication::translate("ChatWindow", "Server IP :", nullptr));
        serverIP->setText(QCoreApplication::translate("ChatWindow", "127.0.0.1", nullptr));
        label_2->setText(QCoreApplication::translate("ChatWindow", "Port :", nullptr));
        connButton->setText(QCoreApplication::translate("ChatWindow", "Connect", nullptr));
        label_4->setText(QCoreApplication::translate("ChatWindow", "Message:", nullptr));
        sendButton->setText(QCoreApplication::translate("ChatWindow", "Send", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatWindow: public Ui_ChatWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATWINDOW_H
