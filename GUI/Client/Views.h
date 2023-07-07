#ifndef VIEWS_H
#define VIEWS_H
#include "chatwindow.h"
#include "loginwindow.h"

class views: public QObject
{
    Q_OBJECT
public:
    views();
    ~views();

signals:
    void loggedInView();

private:
    ChatWindow *cw;
    LoginWindow *lw;
};

#endif // VIEWS_H
