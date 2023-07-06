#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "Views.h"
#include "Client.h"

class controller
{
public:
    controller(views *_v, client *_clt);

private slots:
    void pressSendButton();
    void pressSendEnter();
    void recvMsg();

private:
    views* v;
    client* clt;

};

#endif // CONTROLLER_H
