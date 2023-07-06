#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QWidget>
#include <QtNetwork>
#include "ui_chatwindow.h"
#include "Client.h"

class LoginWindow;

class ChatWindow : public QWidget
{
    Q_OBJECT

    public:
        ChatWindow();


    private:
        Ui::ChatWindow ui;

};
#endif // CLIENTWINDOW_H
