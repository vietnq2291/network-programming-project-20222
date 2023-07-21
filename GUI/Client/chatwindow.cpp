#include "chatwindow.h"
#include "ui_clientwindow.h"
#include "common.h"
#include <QPixmap>
#include <QIcon>

ChatWindow::ChatWindow()
{
    ui.setupUi(this);
    QPixmap pix(":/resource/img/chat.png");
    this->setWindowIcon(QIcon(pix));
    ui.sendButton->setIcon(QIcon(pix));
    ui.messageBox->setReadOnly(true);

    connect(ui.sendButton, SIGNAL(clicked(bool)), this, SLOT(pressSendButton()));
    connect(ui.messageBox, SIGNAL(returnPressed()), this, SLOT(pressSendEnter()));
}

ChatWindow::~ChatWindow(){
    emit LogOut();
}

void ChatWindow::clearAll() {
//    while(ui.listChat->currentItem() != NULL) {
//        ui.listChat->removeItemWidget(ui.listChat->currentItem());
//    }
    ui.label_3->setText("Choose a person to chat");
    ui.listChat->clear();
    ui.listFriend->clear();
    ui.convBox->clear();
}

void ChatWindow::loadChat(std::string disName){

    ui.listChat->addItem(disName.c_str());
}

void ChatWindow::loadFriend(std::string disName){

    ui.listFriend->addItem(disName.c_str());
}

void ChatWindow::resFriend(std::string dispname, int id) {
    QString dname = dispname.c_str();
    QString text = dname + " wants to connect with you. Agree?";
    int reply = QMessageBox::question(this, "Friend request", text);

    if (reply == QMessageBox::No) {
        emit denyFriendRequest(id);
        QMessageBox::information(this, "Reject", "You have rejected " + dname + " request");
    } else if (reply == QMessageBox::Yes) {
        clearAll();
        emit acceptFriendRequest(id);
        QMessageBox::information(this, "Accept", "You and " + dname + " has became friend!");
    }
}

void ChatWindow::renderChat(QString sender, time_t timestamp, QString Message) {
    QString message = "<b>%1</b> &lt;%2&gt;: %3";
    QString FormatMessage = message.arg(sender, time2string(timestamp).c_str(), Message);
    ui.convBox->append(FormatMessage);
    ui.convBox->append("\n");
}

void ChatWindow::anoConnected() {
    ui.convBox->append("<i>You are connected! Go ahead and have fun!</i>");
}

void ChatWindow::pressSendButton() {
    QString sendPack = ui.messageBox->text();
    if (!sendPack.isEmpty()) {
        renderChat("Me", time(NULL), sendPack);
        emit sendMessage(sendPack);
    }

    ui.messageBox->clear();
    ui.messageBox->setFocus();
}

void ChatWindow::pressSendEnter() {
    pressSendButton();
}

void ChatWindow::recvMsg(ChatMessage message) {
    renderChat(chat_name, message.timestamp, message.data.c_str());
}

void ChatWindow::checkUser(QString username) {
    for (int i = 0; i < ui.listChat->count(); i++) {
        if (ui.listChat->item(i)->text() == username) {
            gw->addToSelected(username);
            return;
        }
    }
    gw->usrNotAv();
}

void ChatWindow::addToGroup(QString gname, std::vector<QString> userList) {
    emit addGroup(gname, userList);
}


void ChatWindow::on_LogOutButton_clicked()
{
    clearAll();
    emit LogOut();

}

void ChatWindow::on_listChat_itemClicked(QListWidgetItem *item)
{
    ui.messageBox->setReadOnly(false);
    chat_name = item->text();
    ui.label_3->setText(chat_name);
    ui.convBox->clear();
    emit chooseChat(item->text());

}


void ChatWindow::on_AddFriendButton_clicked()
{
    QString disp_name = QInputDialog::getText(this, "Add Friend", "Enter your friend's username...");
    if (!disp_name.isEmpty()) {
        emit addFriend(disp_name);
    }
}


void ChatWindow::on_AddGroupButton_clicked()
{
    gw = new GroupWindow();
    gw->show();

    connect(gw, SIGNAL(checkUser(QString)), this, SLOT(checkUser(QString)));
    connect(gw, SIGNAL(addToGroup(QString, std::vector<QString>)), this, SLOT(addToGroup(QString, std::vector<QString>)));
}


void ChatWindow::on_pushButton_clicked()
{
    clearAll();
    ui.label_3->setText("Anonymous Chat");
    ui.convBox->append("<i>Waiting for another user to join</i>\n");
    emit anonymousRequire();
}

