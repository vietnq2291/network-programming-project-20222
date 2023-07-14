#include "Controller.h"


controller::controller()
{
    v = new views();
    clt = new client(DEFAULT_PORT, DEFAULT_IP, DEFAULT_FOLDER);
    clt->connectToServer();

    std::cerr << "success" << std::endl;

    connect(v, SIGNAL(recievedAuthView(QString,QString)), clt, SLOT(Authenticate(QString,QString)));
    connect(v, SIGNAL(recievedSignUpView(QString,QString)), clt, SLOT(SignUp(QString,QString)));

    connect(clt, SIGNAL(messageReceived(ChatMessage)), v, SLOT(recvMsg(ChatMessage)));
    connect(clt, SIGNAL(authSuccess(std::vector<Friend>)), v, SLOT(initChat(std::vector<Friend>)));
    connect(clt, SIGNAL(LogOutSuccess()), v, SLOT(switchToLogin()));
    connect(v, SIGNAL(setChatView(QString)), clt, SLOT(setChat(QString)));
    connect(v, SIGNAL(sendMessageView(QString)), clt, SLOT(sendMessage(QString)));
    connect(v, SIGNAL(LogOutView()), clt, SLOT(LogOut()));


    const int num_threads = 2;
    pthread_t threads[num_threads];
    int rc = pthread_create(&threads[0], NULL, receive_thread_message, clt);
    if (rc) {
        std::cerr << "Error: unable to create receive thread, " << rc << std::endl;
        exit(-1);
    }
//    rc = pthread_create(&threads[1], NULL, send_thread_message, clt);
//    if (rc) {
//        std::cerr << "Error: unable to create send thread, " << rc << std::endl;
//        exit(-1);
//    }

//    pthread_t thread;
//    int rc = pthread_create(&thread, NULL, receive_thread_message, clt);
//    if (rc) {
//        std::cerr << "Error: unable to create receive thread, " << rc << std::endl;
//        exit(-1);
//    }

//    for (int i = 0; i < num_threads; ++i) {
//        pthread_join(threads[i], NULL);
//    }
//    pthread_join(thread, NULL);
//    clt->start();
}

void* receive_thread_message(void* arg) {
    client* clt = static_cast<client*>(arg);
    std::cerr << "thread created" << std::endl;
    clt->receive_message_p(NULL);
    return NULL;
}

void* send_thread_message(void* arg) {
//    client* clt = static_cast<client*>(arg);
//    clt->send_message(NULL);
    return NULL;
}

