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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatWindow
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QListWidget *listChat;
    QPushButton *AddGroupButton;
    QWidget *tab_2;
    QListWidget *listFriend;
    QPushButton *AddFriendButton;
    QPushButton *LogOutButton;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QVBoxLayout *verticalLayout_2;
    QTextEdit *convBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QLineEdit *messageBox;
    QPushButton *sendButton;

    void setupUi(QWidget *ChatWindow)
    {
        if (ChatWindow->objectName().isEmpty())
            ChatWindow->setObjectName("ChatWindow");
        ChatWindow->resize(1143, 653);
        QIcon icon;
        icon.addFile(QString::fromUtf8("chat.png"), QSize(), QIcon::Normal, QIcon::Off);
        ChatWindow->setWindowIcon(icon);
        tabWidget = new QTabWidget(ChatWindow);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(10, 46, 221, 591));
        tab = new QWidget();
        tab->setObjectName("tab");
        listChat = new QListWidget(tab);
        listChat->setObjectName("listChat");
        listChat->setGeometry(QRect(0, 0, 221, 521));
        AddGroupButton = new QPushButton(tab);
        AddGroupButton->setObjectName("AddGroupButton");
        AddGroupButton->setGeometry(QRect(30, 530, 161, 25));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        listFriend = new QListWidget(tab_2);
        listFriend->setObjectName("listFriend");
        listFriend->setGeometry(QRect(0, 0, 221, 521));
        AddFriendButton = new QPushButton(tab_2);
        AddFriendButton->setObjectName("AddFriendButton");
        AddFriendButton->setGeometry(QRect(30, 530, 161, 25));
        tabWidget->addTab(tab_2, QString());
        LogOutButton = new QPushButton(ChatWindow);
        LogOutButton->setObjectName("LogOutButton");
        LogOutButton->setGeometry(QRect(10, 10, 221, 31));
        layoutWidget = new QWidget(ChatWindow);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(241, 10, 881, 631));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName("label_3");

        horizontalLayout->addWidget(label_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName("pushButton");

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
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


        verticalLayout->addLayout(verticalLayout_2);


        retranslateUi(ChatWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ChatWindow);
    } // setupUi

    void retranslateUi(QWidget *ChatWindow)
    {
        ChatWindow->setWindowTitle(QCoreApplication::translate("ChatWindow", "Aloo!", nullptr));
#if QT_CONFIG(accessibility)
        tab->setAccessibleName(QString());
#endif // QT_CONFIG(accessibility)
        AddGroupButton->setText(QCoreApplication::translate("ChatWindow", "Add Group", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("ChatWindow", "Chats", nullptr));
        AddFriendButton->setText(QCoreApplication::translate("ChatWindow", "Add Friend", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("ChatWindow", "Friends", nullptr));
        LogOutButton->setText(QCoreApplication::translate("ChatWindow", "Log Out", nullptr));
        label_3->setText(QCoreApplication::translate("ChatWindow", "Choose a person to chat", nullptr));
        pushButton->setText(QCoreApplication::translate("ChatWindow", "Go Anonymous...", nullptr));
        label_4->setText(QCoreApplication::translate("ChatWindow", "Message:", nullptr));
        sendButton->setText(QCoreApplication::translate("ChatWindow", "Send", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatWindow: public Ui_ChatWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATWINDOW_H
