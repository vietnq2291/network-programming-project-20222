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
    void recievedSignUpView(QString username, QString password);
    void setChatView(QString chat_name);
    void sendMessageView(QString packet);
    void recvMessage(ChatMessage message);
    void LogOutView();

private slots:
    void recvAuth(QString user, QString pass);
    void recvSignUp(QString username, QString password);
    void recvMsg(ChatMessage message);
    void setToChat(QString chat_name);
    void sendMessage(QString packet);
    void LogOut();

    void switchToChat();
    void switchToLogin();
    void initChat(std::vector<Chat> chatList);

private:
    ChatWindow *cw;
    LoginWindow *lw;
};

#endif // VIEWS_H
