#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QWidget>

#include "ui_chatwindow.h"
#include "Client.h"
#include "Utils.h"

class LoginWindow;

class ChatWindow : public QWidget
{
    Q_OBJECT

    public:
        ChatWindow();
        ~ChatWindow();
        void loadFriend(std::string disName);
        void clearAll();

    private slots:
        void pressSendButton();
        void pressSendEnter();
        void recvMsg(ChatMessage message);

        void on_listWidget_itemClicked(QListWidgetItem *chat);

        void on_LogOutButton_clicked();

    signals:
        void chooseChat(QString chat_name);
        void sendMessage(QString message);
        void LogOut();

    private:
        Ui::ChatWindow ui;
        QTcpSocket input_socket;
        QString chat_name;

};
#endif // CLIENTWINDOW_H
