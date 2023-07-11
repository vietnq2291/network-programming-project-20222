#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QWidget>
#include <QtNetwork>
#include "ui_chatwindow.h"
#include "Client.h"

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
        void recvMsg();

        void on_listWidget_itemClicked(QListWidgetItem *item);

    signals:
        void sendMessage(QString message);

    private:
        Ui::ChatWindow ui;

};
#endif // CLIENTWINDOW_H
