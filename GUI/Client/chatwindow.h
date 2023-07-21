#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QWidget>
#include <QInputDialog>
#include <QMessageBox>

#include "ui_chatwindow.h"
#include "Client.h"
#include "groupwindow.h"
#include "Utils.h"



class LoginWindow;

class ChatWindow : public QWidget
{
    Q_OBJECT

    public:
        ChatWindow();
        ~ChatWindow();
        void loadChat(std::string disName);
        void loadFriend(std::string disName);
        void resFriend(std::string dispname, int id);
        void renderChat(QString sender, time_t timestamp, QString Message);
        void anoConnected();
        void clearAll();

    private slots:
        void pressSendButton();
        void pressSendEnter();
        void recvMsg(ChatMessage message);
        void checkUser(QString username);
        void addToGroup(QString gname, std::vector<QString> userList);

        void on_LogOutButton_clicked();

        void on_listChat_itemClicked(QListWidgetItem *item);

        void on_AddFriendButton_clicked();

        void on_ChatWindow_destroyed();

        void on_AddGroupButton_clicked();

        void on_pushButton_clicked();

    signals:
        void chooseChat(QString chat_name);
        void sendMessage(QString message);
        void addGroup(QString gname, std::vector<QString> userList);
        void addFriend(QString name);
        void acceptFriendRequest(int id);
        void denyFriendRequest(int id);
        void anonymousRequire();

        void LogOut();

    private:
        Ui::ChatWindow ui;
        GroupWindow *gw;
        QTcpSocket input_socket;
        QString chat_name;

};
#endif // CLIENTWINDOW_H
