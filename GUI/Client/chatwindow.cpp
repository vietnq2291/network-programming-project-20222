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
}

ChatWindow::~ChatWindow(){

}

void ChatWindow::pressConnect() {

    ui.convBox->append(tr("<em>Connecting...</em>"));
    ui.connButton->setEnabled(false);


//    socket->abort();
//    socket->connectToHost(ui.serverIP->text(), ui.serverPort->value());
}

void ChatWindow::pressSendButton() {
    QByteArray pack;
    QDataStream out(&pack, QIODevice::WriteOnly);

    QString sendPack = ui.messageBox->text();

    ui.messageBox->clear();
    ui.messageBox->setFocus();
}

void ChatWindow::pressSendEnter() {
    pressSendButton();
}

void ChatWindow::recvMsg() {

    QString Message;

    ui.convBox->append(Message);
}

void ChatWindow::Conn() {
    ui.convBox->append(tr("<em>Connect successfully !</em>"));
    ui.connButton->setEnabled(true);
}

void ChatWindow::closeConn() {
    ui.convBox->append(tr("<em>Goodbye!</em>"));
}

void ChatWindow::socketErr(QAbstractSocket::SocketError err) {
    switch(err) { // Hien thi thong bao khac nhau tuy theo loi gap phai
          case QAbstractSocket::HostNotFoundError:
            ui.convBox->append(tr("<em>ERR : Cannot connect to server ! Please check again IP address and Port number</em>"));
            break;
        case QAbstractSocket::ConnectionRefusedError:
            ui.convBox->append(tr("<em>ERR : Server refused to connect ! Check again if the server has started yet.</em>"));
            break;
        case QAbstractSocket::RemoteHostClosedError:
            ui.convBox->append(tr("<em>ERR : Server has closed !</em>"));
            break;
        default:
            ui.convBox->append(tr("<em>ERR : ") + tr("</em>"));
    }

    ui.connButton->setEnabled(true);
}
