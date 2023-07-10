#include "Views.h"

views::views()
{
    cw = new ChatWindow();
    lw = new LoginWindow();

    this->switchToLogin();

    connect(lw, SIGNAL(loggedIn()), this, SIGNAL(loggedInView()));
    connect(lw, SIGNAL(receivedAuth(QString,QString)), this, SLOT(recvAuth(QString,QString)));
}

views::~views()
{

}

void views::switchToChat(){
    lw->hide();
    cw->show();
}

void views::switchToLogin(){
    lw->show();
    cw->hide();
}

void views::recvAuth(QString user, QString pass) {
    emit recievedAuthView(user, pass);
}
