#include "Views.h"

views::views()
{
    cw = new ChatWindow();
    lw = new LoginWindow();

    this->switchToLogin();

    connect(lw, SIGNAL(receivedAuth(QString,QString)), this, SLOT(recvAuth(QString,QString)));
    connect(cw, SIGNAL(chooseChat(QString)), this, SLOT(setToChat(QString)));
    connect(cw, SIGNAL(sendMessage(QString)), this, SLOT(sendMessage(QString)));
    connect(this, SIGNAL(recvMessage(ChatMessage)), cw, SLOT(recvMsg(ChatMessage)));
}

views::~views()
{

}

void views::switchToChat(){
    lw->hide();
    cw->show();
}

void views::initChat(std::vector<Friend> friendList) {
    lw->hide();
    cw->show();

    int size = friendList.size();

    for (int i = 0; i < size; i++) {
        cw->loadFriend(friendList[i].disp_name);
    }
}

void views::switchToLogin(){
    lw->show();
    cw->hide();
}

void views::recvAuth(QString user, QString pass) {
    emit recievedAuthView(user, pass);
}

void views::setToChat(QString chat_name) {
    emit setChatView(chat_name);
}

void views::sendMessage(QString packet) {
    emit sendMessageView(packet);
}

void views::recvMsg(QString message) {
    emit recvMessage(message);
}
