#include "Controller.h"


controller::controller()
{
    v = new views();
    clt = new client(DEFAULT_PORT, DEFAULT_IP, DEFAULT_FOLDER);
    clt->connectToServer();

    std::cerr << "success" << std::endl;

    connect(v, SIGNAL(recievedAuthView(QString,QString)), clt, SLOT(Authenticate(QString,QString)));
    connect(v, SIGNAL(recievedSignUpView(QString,QString,QString)), clt, SLOT(SignUp(QString,QString,QString)));

//    connect(clt, SIGNAL(authSuccess1st()), this, SLOT(initThread()));
//    connect(clt, SIGNAL(authSuccess(std::vector<Chat>,std::vector<Friend>)), this, SLOT(initThread(std::vector<Chat>,std::vector<Friend>)));
    connect(v, SIGNAL(initThread()), this, SLOT(initThread()));

    connect(clt, SIGNAL(messageReceived(ChatMessage)), v, SLOT(recvMsg(ChatMessage)));
    connect(clt, SIGNAL(authSuccess(std::vector<Chat>,std::vector<Friend>)), v, SLOT(initChat(std::vector<Chat>,std::vector<Friend>)));
    connect(clt, SIGNAL(LogOutSuccess()), v, SLOT(switchToLogin()));
    connect(clt, SIGNAL(recvFriendRequest(std::string,int)), v, SLOT(RequestFriend(std::string,int)));
    connect(clt, SIGNAL(chatHistory(ChatMessage,QString)), v, SLOT(loadChatHistory(ChatMessage,QString)));
    connect(clt, SIGNAL(resetUI()), v, SLOT(resetUI()));
    connect(clt, SIGNAL(anonymousJoined()), v, SLOT(setupAnonymous()));

    connect(v, SIGNAL(setChatView(QString)), clt, SLOT(setChat(QString)));
    connect(v, SIGNAL(sendMessageView(QString)), clt, SLOT(sendMessage(QString)));
    connect(v, SIGNAL(addGroupView(QString,std::vector<QString>)), clt, SLOT(addGroup(QString,std::vector<QString>)));
    connect(v, SIGNAL(addFriendView(QString)), clt, SLOT(addFriend(QString)));
    connect(v, SIGNAL(denyFRView(int)), clt, SLOT(denyFriend(int)));
    connect(v, SIGNAL(accFRView(int)), clt, SLOT(accFriend(int)));
    connect(v, SIGNAL(anonymousRequireView()), clt, SLOT(anonymousChatInit()));
    connect(v, SIGNAL(LogOutView()), clt, SLOT(LogOut()));



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

//void controller::initThread(std::vector<Chat>,std::vector<Friend>) {
////    const int num_threads = 2;
//    int rc = pthread_create(&threads, NULL, receive_thread_message, clt);
//    if (rc) {
//        std::cerr << "Error: unable to create receive thread, " << rc << std::endl;
//        exit(-1);
//    }
//}

void controller::initThread() {
    //    const int num_threads = 2;
    int rc = pthread_create(&threads, NULL, receive_thread_message, clt);
    if (rc) {
        std::cerr << "Error: unable to create receive thread, " << rc << std::endl;
        exit(-1);
    }
}

void* receive_thread_message(void* arg) {
    client* clt = static_cast<client*>(arg);
    std::cerr << "thread created" << std::endl;
    clt->receive_message_p(NULL);
    return NULL;
}

//void* send_thread_message(void* arg) {
////    client* clt = static_cast<client*>(arg);
////    clt->send_message(NULL);
//    return NULL;
//}

