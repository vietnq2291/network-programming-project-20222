#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QWidget>
#include <QtNetwork>
#include "ui_clientwindow.h"

class ClientWindow : public QWidget
{
    Q_OBJECT

    public:
        ClientWindow();

    private slots:
        void pressConnect();
        void pressSendButton();
        void pressSendEnter();
        void recvMsg();
        void Conn();
        void closeConn();
        void socketErr(QAbstractSocket::SocketError err);

    private:
        QTcpSocket *socket;  // socket connect to server
        quint16 packSize;
        Ui::clientWindow ui;
};
#endif // CLIENTWINDOW_H
