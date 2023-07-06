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

    socket = new QTcpSocket(this);


    packSize = 0;
}

void ClientWindow::pressConnect() {

    ui.convBox->append(tr("<em>Connecting...</em>"));
    ui.connButton->setEnabled(false);


//    socket->abort();
//    socket->connectToHost(ui.serverIP->text(), ui.serverPort->value());
}

void ClientWindow::pressSendButton() {
    QByteArray pack;
    QDataStream out(&pack, QIODevice::WriteOnly);

    QString sendPack = ui.messageBox->text();

    out << (quint16) 0;
    out << sendPack;
    out.device()->seek(0);
    out << (quint16) (pack.size() - sizeof(quint16));

    socket->write(pack);

    ui.messageBox->clear();
    ui.messageBox->setFocus();
}

void ClientWindow::pressSendEnter() {
    pressSendButton();
}

void ClientWindow::recvMsg() {

    QDataStream in(socket);
    if (packSize == 0) {
        if (socket->bytesAvailable() < (int)sizeof(quint16)) {
            //Kich thuoc goi tin nho hon kich thuc kieu so nguyen
            return;
        }
        // Neu nhan duoc kich thuoc tin nhan thi lay ra gia tri do
        in >> packSize;
    }

    // Biet kich thuoc, chung ta se kiem tra xem da nhan duoc toan bo tin nhan chua
    if (socket->bytesAvailable() < packSize) {
        // Neu chua nhan du tin nhan thi thoat xu ly
        return;
    }

    QString Message;
    in >> Message;

    ui.convBox->append(Message);

    // Dat lai kich thuoc la 0 de cho tin nhan tiep theo
    packSize = 0;
}

void ClientWindow::Conn() {
    ui.convBox->append(tr("<em>Connect successfully !</em>"));
    ui.connButton->setEnabled(true);
}

void ClientWindow::closeConn() {
    ui.convBox->append(tr("<em>Goodbye!</em>"));
}

void ClientWindow::socketErr(QAbstractSocket::SocketError err) {
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
            ui.convBox->append(tr("<em>ERR : ") + socket->errorString() + tr("</em>"));
    }

    ui.connButton->setEnabled(true);
}
