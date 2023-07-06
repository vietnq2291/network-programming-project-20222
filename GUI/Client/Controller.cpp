#include "Controller.h"

controller::controller(views *_v, client *_clt)
{
    v = _v;
    clt = _clt;

    QObject::connect(clt, SIGNAL(receiveMessage()), this, SLOT(recvMsg()));

//    connect(socket, SIGNAL(readyRead()), this, SLOT(recvMsg()));
//    connect(socket, SIGNAL(connected()), this, SLOT(Conn()));
//    connect(socket, SIGNAL(disconnected()), this, SLOT(closeConn()));
//    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketErr(QAbstractSocket::SocketError)));

//    connect(ui.connButton, SIGNAL(clicked()), this, SLOT(pressConnect()));
//    connect(ui.sendButton, SIGNAL(clicked()), this, SLOT(pressSendButton()));
//    connect(ui.messageBox, SIGNAL(returnPressed()), this, SLOT(pressSendEnter()));
}

controller::recvMsg() {

}
