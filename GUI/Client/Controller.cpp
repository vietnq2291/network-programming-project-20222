#include "Controller.h"


controller::controller()
{
    v = new views();
    clt = new client(DEFAULT_PORT, DEFAULT_IP);
    clt->connectToServer();


    connect(v, SIGNAL(recievedAuthView(QString,QString)), clt, SLOT(Authenticate(QString,QString)));

    connect(clt, SIGNAL(messageReceived(ChatMessage)), v, SLOT(recvMsg(ChatMessage)));
    connect(clt, SIGNAL(authSuccess(std::vector<Friend>)), v, SLOT(initChat(std::vector<Friend>)));
    connect(v, SIGNAL(setChatView(QString)), clt, SLOT(setChat(QString)));
    connect(v, SIGNAL(sendMessageView(QString)), clt, SLOT(sendMessage(QString)));

//    clt->start();
}

