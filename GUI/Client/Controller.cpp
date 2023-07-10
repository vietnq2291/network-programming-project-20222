#include "Controller.h"


controller::controller()
{
    v = new views();
    clt = new client(DEFAULT_PORT, DEFAULT_IP);
    clt->connect();

    connect(v, SIGNAL(loggedInView()), this, SLOT(logInSucc()));
    connect(v, SIGNAL(recievedAuthView(QString,QString)), this, SLOT(Authenticate(QString,QString)));

    connect(clt, SIGNAL(messageReceived()), this, SLOT(recvMsg()));
    connect(clt, SIGNAL(authSuccess()), v, SLOT(switchToChat()));
}

void controller::Authenticate(QString username, QString password) {
    std::string buff = "R L " + username.toStdString() + " " + password.toStdString();
    clt->send_request_message(buff);
    clt->receive_message();
}

void controller::pressSendButton(){

}

void controller::pressSendEnter(){

}

void controller::recvMsg() {

}

void controller::logInSucc() {
//    v->switchToChat();
}
