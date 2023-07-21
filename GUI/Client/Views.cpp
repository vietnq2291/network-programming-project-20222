#include "Views.h"

views::views()
{
    cw = new ChatWindow();
    lw = new LoginWindow();

    this->switchToLogin();

    connect(lw, SIGNAL(receivedAuth(QString,QString)), this, SLOT(recvAuth(QString,QString)));
    connect(lw, SIGNAL(receiveSignUp(QString,QString,QString)), this, SLOT(recvSignUp(QString,QString,QString)));

    connect(cw, SIGNAL(chooseChat(QString)), this, SLOT(setToChat(QString)));
    connect(cw, SIGNAL(sendMessage(QString)), this, SLOT(sendMessage(QString)));
    connect(cw, SIGNAL(addGroup(QString,std::vector<QString>)), this, SLOT(addGroup(QString,std::vector<QString>)));
    connect(cw, SIGNAL(addFriend(QString)), this, SLOT(addFriend(QString)));
    connect(cw, SIGNAL(LogOut()), this, SLOT(LogOut()));
    connect(cw, SIGNAL(denyFriendRequest(int)), this, SLOT(denyFR(int)));
    connect(cw, SIGNAL(acceptFriendRequest(int)), this, SLOT(accFR(int)));
    connect(cw, SIGNAL(anonymousRequire()), this, SLOT(anonymousRequire()));

    connect(this, SIGNAL(recvMessage(ChatMessage)), cw, SLOT(recvMsg(ChatMessage)));
}

views::~views()
{

}

void views::switchToChat(){
    lw->hide();
    cw->show();
}

void views::initChat(std::vector<Chat> chatList, std::vector<Friend> friendList) {
    std::cerr << "init chat" << std::endl;
    lw->hide();
    cw->show();

    int chatsize = chatList.size();
    int friendsize = friendList.size();

    for (int i = 0; i < chatsize; i++) {
        cw->loadChat(chatList[i].cname);
    }

    for (int i = 0; i < friendsize; i++) {
        cw->loadFriend(friendList[i].disp_name);
    }
    if (firstLog == true) {
        emit initThread();
        firstLog = false;
    }
}

void views::switchToLogin(){
    lw->show();
    lw->clearInput();
//    cw->clearAll();
    cw->hide();

}

void views::recvAuth(QString user, QString pass) {
    emit recievedAuthView(user, pass);
}

void views::recvSignUp(QString username, QString password, QString dispname) {
    emit recievedSignUpView(username, password, dispname);
}

void views::setToChat(QString chat_name) {
    emit setChatView(chat_name);
}

void views::sendMessage(QString packet) {
    emit sendMessageView(packet);
}

void views::addGroup(QString gname, std::vector<QString> userList) {
    emit addGroupView(gname, userList);
}

void views::recvMsg(ChatMessage message) {
    emit recvMessage(message);
}

void views::addFriend(QString name) {
    emit addFriendView(name);
}

void views::RequestFriend(std::string dispname, int id) {
    cw->resFriend(dispname, id);
}

void views::denyFR(int id) {
    emit denyFRView(id);
}

void views::accFR(int id) {
    emit accFRView(id);
}

void views::resetUI() {
    cw->clearAll();
}

void views::loadChatHistory(ChatMessage message, QString sender) {
    cw->renderChat(sender, message.timestamp, message.data.c_str());
}

void views::setupAnonymous() {
    cw->anoConnected();
}

void views::anonymousRequire() {
    emit anonymousRequireView();
}

void views::LogOut() {
    emit LogOutView();
}
