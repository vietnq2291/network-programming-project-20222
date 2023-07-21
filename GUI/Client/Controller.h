#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "Views.h"
#include "Client.h"
#include "common.h"
#include "pthread.h"



class controller: public QObject
{
    Q_OBJECT
public:
    controller();

private slots:
//    void initThread(std::vector<Chat>,std::vector<Friend>);
    void initThread();
private:
    views* v;
    client* clt;
    pthread_t threads;
};

void *receive_thread_message(void *arg);
void *send_thread_message(void *arg);

#endif // CONTROLLER_H
