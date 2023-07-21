#ifndef VIEWS_H
#define VIEWS_H
#include "chatwindow.h"
#include "loginwindow.h"
#include "common.h"



class views: public QObject
{
    Q_OBJECT
public:
    views();
    ~views();

signals:
    void loggedInView();
    void recievedAuthView(QString user, QString pass);
    void recievedSignUpView(QString username, QString password, QString dispname);
    void setChatView(QString chat_name);
    void sendMessageView(QString packet);
    void addGroupView(QString gname, std::vector<QString> userList);
    void recvMessage(ChatMessage message);
    void addFriendView(QString name);
    void denyFRView(int id);
    void accFRView(int id);
    void initThread();
    void anonymousRequireView();
    void LogOutView();

private slots:
    void recvAuth(QString user, QString pass);
    void recvSignUp(QString username, QString password, QString dispname);
    void recvMsg(ChatMessage message);
    void setToChat(QString chat_name);
    void sendMessage(QString packet);
    void addGroup(QString gname, std::vector<QString> userList);
    void addFriend(QString name);
    void RequestFriend(std::string dispname, int id);
    void denyFR(int id);
    void accFR(int id);
    void resetUI();
    void loadChatHistory(ChatMessage message, QString sender);
    void setupAnonymous();
    void anonymousRequire();
    void LogOut();

    void switchToChat();
    void switchToLogin();
    void initChat(std::vector<Chat> chatList, std::vector<Friend> friendList);

private:

    bool firstLog = true;
    ChatWindow *cw;
    LoginWindow *lw;
};

#endif // VIEWS_H
