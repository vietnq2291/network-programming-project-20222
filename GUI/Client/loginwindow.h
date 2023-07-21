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
    void clearInput();

signals:
    void receivedAuth(QString username, QString password);
    void receiveSignUp(QString username, QString password, QString dispname);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_Login_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::LoginWindow *ui;
};

#endif // LOGINWINDOW_H
