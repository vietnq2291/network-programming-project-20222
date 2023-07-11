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

private slots:
    void recvAuth(QString user, QString pass);
    void switchToChat();
    void switchToLogin();
    void initChat(std::vector<Friend>);

private:
    ChatWindow *cw;
    LoginWindow *lw;
};

#endif // VIEWS_H
