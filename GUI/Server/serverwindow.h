
#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QtWidgets>
#include <QtNetwork>

class ServerWindow : public QWidget

{
    Q_OBJECT

public:
    ServerWindow();
    void sendToAllUser(const QString &message);

private slots:
    void newConnect();
    void recvMsg();
    void closeConn();

private:
    QLabel *state;
    QPushButton *close;

    QTcpServer *server;
    QList<QTcpSocket *> user;
    quint16 packSize;
};

#endif // SERVERWINDOW_H
