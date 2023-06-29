
#include "serverwindow.h"


ServerWindow::ServerWindow()
{
    state = new QLabel();
    close = new QPushButton(tr("Close"));

    connect(close, SIGNAL(clicked()), qApp, SLOT(quit()));

    QVBoxLayout *main = new QVBoxLayout();
    main->addWidget(state);
    main->addWidget(close);
    setLayout(main);
    setWindowTitle("Chat Server");

    server = new QTcpServer(this);
    if (!server->listen(QHostAddress::Any, 50885)) {
        state->setText(tr("Server cannot initiate. Reason: <br />") + server->errorString());
    } else {
        state->setText(tr("Server open on port <strong>") + QString::number(server->serverPort()) + tr("</strong>. User can connect and start chatting!"));
        connect(server, SIGNAL(newConnection()), this, SLOT(newConnect()));
    }

    packSize = 0;
}

void ServerWindow::newConnect() {
    sendToAllUser(tr("<em>A new user has joined!</em>"));
    QTcpSocket *newUser = server->nextPendingConnection();

    user << newUser;

    connect(newUser, SIGNAL(readyRead()), this, SLOT(recvMsg()));
    connect(newUser, SIGNAL(disconnected()), this, SLOT(closeConn()));
}

void ServerWindow::recvMsg() {
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());

//    Stop if source is not found
    if (socket == 0) {
        return;
    }

//    tcp packet contain: |packSize|   message   |

    QDataStream in(socket);

//    Handle when packet size is not known
    if (packSize == 0) {
        if (socket->bytesAvailable() < (int)sizeof(quint16)) {
//            packet size is smaller than packSize itself then stop
            return;
        }
        in >> packSize;
    }

    if (socket->bytesAvailable() < packSize) {
//        message is shorter than packSize, stop
        return;
    }

    QString Message;
    in >> Message;

    sendToAllUser(Message);

    packSize = 0;
}

void ServerWindow::closeConn() {
//    determine who left
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (socket == 0) {
        return;
    }

    sendToAllUser("<em>An user has just left</em>");
    user.removeOne(socket);
    socket->deleteLater();
}

void ServerWindow::sendToAllUser(const QString &message) {
    QByteArray messagePack;

    QDataStream out(&messagePack, QIODevice::WriteOnly);
    out << (quint16) 0;
    out << message;
    out.device()->seek(0);
    out << (quint16) (messagePack.size() - sizeof(quint16));

    for (int i = 0; i < user.size(); i++) {
        user[i]->write(messagePack);
    }
}
