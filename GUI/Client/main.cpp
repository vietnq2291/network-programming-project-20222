#include "chatwindow.h"
#include "loginwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    LoginWindow lw;
    lw.show();
    return app.exec();
}
