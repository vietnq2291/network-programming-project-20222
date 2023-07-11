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
}

ChatWindow::~ChatWindow(){

}

void ChatWindow::loadFriend(std::string disName){

    ui.listWidget->addItem(disName.c_str());
}


void ChatWindow::pressSendButton() {
    QString sendPack = ui.messageBox->text();
    if (!sendPack.isEmpty()) {
        emit sendMessage(sendPack);
    }

    ui.messageBox->clear();
    ui.messageBox->setFocus();
}

void ChatWindow::pressSendEnter() {
    pressSendButton();
}

void ChatWindow::recvMsg(ChatMessage message) {
    QDateTime t(QTime::fromTime_t(message.timestamp));
    QString Message = chat_name + "<" + t.toString("hh:mm") + ">:" + message.data.c_str() + "\n";

    ui.convBox->append(Message);
}


void ChatWindow::on_listWidget_itemClicked(QListWidgetItem *chat)
{
    ui.messageBox->setReadOnly(false);
    chat_name = chat->text();
    ui.label_3->setText(chat_name);

    emit chooseChat(chat->text());
}

