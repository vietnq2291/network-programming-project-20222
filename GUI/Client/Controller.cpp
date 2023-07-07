#include "Controller.h"

controller::controller(views *_v, client *_clt)
{
    v = _v;
    clt = _clt;

    connect(clt, SIGNAL(messageReceived()), this, SLOT(recvMsg()));
    connect(v, SIGNAL(loggedInView()), this, SLOT(logInSucc()));
}

void controller::pressSendButton(){

}

void controller::pressSendEnter(){

}

void controller::recvMsg() {

}

void controller::logInSucc() {

}
