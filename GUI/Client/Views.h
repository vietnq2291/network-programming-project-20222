#ifndef VIEWS_H
#define VIEWS_H
#include "chatwindow.h"
#include "loginwindow.h"

class views
{
public:
    views();

private:
    ChatWindow *cw;
    LoginWindow *lw;
};

#endif // VIEWS_H
