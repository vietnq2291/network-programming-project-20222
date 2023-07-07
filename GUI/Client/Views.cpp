#include "Views.h"

views::views()
{
    cw = new ChatWindow();
    lw = new LoginWindow();

    lw->show();
    cw->hide();

    connect(lw, SIGNAL(loggedIn()), this, SIGNAL(loggedInView()));
}

views::~views()
{

}
