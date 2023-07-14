#include "Views.h"

views::views()
{
    cw = new ChatWindow();
    lw = new LoginWindow();

    this->switchToLogin();

    connect(lw, SIGNAL(receivedAuth(QString,QString)), this, SLOT(recvAuth(QString,QString)));
    connect(lw, SIGNAL(receiveSignUp(QString,QString)), this, SLOT(recvSignUp(QString,QString)));
    connect(cw, SIGNAL(chooseChat(QString)), this, SLOT(setToChat(QString)));
    connect(cw, SIGNAL(sendMessage(QString)), this, SLOT(sendMessage(QString)));
    connect(cw, SIGNAL(LogOut()), this, SLOT(LogOut()));
    connect(this, SIGNAL(recvMessage(ChatMessage)), cw, SLOT(recvMsg(ChatMessage)));
}

views::~views()
{

}

void views::switchToChat(){
    lw->hide();
    cw->show();
}

void views::initChat(std::vector<Chat> chatList) {
    lw->hide();
    cw->show();

    int size = chatList.size();

    for (int i = 0; i < size; i++) {
        cw->loadFriend(chatList[i].cname);
    }
}

void views::switchToLogin(){
    lw->show();
//    cw->clearAll();
    cw->hide();
}

void views::recvAuth(QString user, QString pass) {
    emit recievedAuthView(user, pass);
}

void views::recvSignUp(QString username, QString password) {
    emit recievedSignUpView(username, password);
}

void views::setToChat(QString chat_name) {
    emit setChatView(chat_name);
}

void views::sendMessage(QString packet) {
    emit sendMessageView(packet);
}

void views::recvMsg(ChatMessage message) {
    emit recvMessage(message);
}

void views::LogOut() {
    emit LogOutView();
}
