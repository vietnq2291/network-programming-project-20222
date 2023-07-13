#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "Views.h"
#include "Client.h"
#include "common.h"

class controller: public QObject
{
    Q_OBJECT
public:
    controller();

private:
    views* v;
    client* clt;

};

#endif // CONTROLLER_H
