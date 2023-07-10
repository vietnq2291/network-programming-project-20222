#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include "common.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

public slots:
    void on_pushButton_Login_clicked();

signals:
    void receivedAuth(QString username, QString password);
    void loggedIn();

private:
    Ui::LoginWindow *ui;
};

#endif // LOGINWINDOW_H
