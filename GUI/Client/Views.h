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
    void setChatView(QString chat_name);
    void sendMessageView(QString packet);
    void recvMessage(QString message);

private slots:
    void recvAuth(QString user, QString pass);
    void recvMsg(QString message);
    void setToChat(QString chat_name);
    void sendMessage(QString packet);

    void switchToChat();
    void switchToLogin();
    void initChat(std::vector<Friend>);

private:
    ChatWindow *cw;
    LoginWindow *lw;
};

#endif // VIEWS_H
