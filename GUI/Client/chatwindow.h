#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QWidget>
#include <QtNetwork>
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

    private slots:
        void pressSendButton();
        void pressSendEnter();
        void recvMsg(ChatMessage message);

        void on_listWidget_itemClicked(QListWidgetItem *chat);

    signals:
        void chooseChat(QString chat_name);
        void sendMessage(QString message);

    private:
        Ui::ChatWindow ui;
        QString chat_name;

};
#endif // CLIENTWINDOW_H
