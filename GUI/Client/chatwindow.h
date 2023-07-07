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

    private slots:
        void pressConnect();
        void pressSendButton();
        void pressSendEnter();
        void recvMsg();
        void Conn();
        void closeConn();
        void socketErr(QAbstractSocket::SocketError);

    private:
        Ui::ChatWindow ui;

};
#endif // CLIENTWINDOW_H
