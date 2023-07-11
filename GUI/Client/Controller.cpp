#include "Controller.h"


controller::controller()
{
    v = new views();
    clt = new client(DEFAULT_PORT, DEFAULT_IP);
    clt->connect();

    connect(v, SIGNAL(recievedAuthView(QString,QString)), this, SLOT(Authenticate(QString,QString)));

    connect(clt, SIGNAL(messageReceived(QString)), this, SLOT(recvMsg(QString)));
    connect(clt, SIGNAL(authSuccess(std::vector<Friend>)), v, SLOT(initChat(std::vector<Friend>)));
    connect(v, SIGNAL(setChatView(QString)), clt, SLOT(setChat(QString)));
    connect(v, SIGNAL(sendMessageView(QString)), clt, SLOT(sendMessage(QString)));
}

void controller::Authenticate(QString username, QString password) {
    std::string buff = "R L " + username.toStdString() + " " + password.toStdString();
    clt->send_request_message(buff);
    clt->receive_message();
}

void controller::recvMsg() {

}

