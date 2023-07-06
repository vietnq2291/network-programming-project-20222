#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    client *clt = new client(DEFAULT_PORT, DEFAULT_IP);
    if (clt == nullptr) {
        std::cerr << "Failed to allocate memory for ClientWindow object." << std::endl;
        return;
    }

    clt->connect();
    connect(ui->lineEdit_UserName, SIGNAL(returnPressed()), this, SLOT(on_pushButton_Login_clicked()));
    connect(ui->lineEdit_Password, SIGNAL(returnPressed()), this, SLOT(on_pushButton_Login_clicked()));
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_pushButton_Login_clicked()
{
    QString username = ui->lineEdit_UserName->text();
    QString password = ui->lineEdit_Password->text();

    if (username == "test" && password == "test") {
//        QMessageBox::information(this, "Login", "Username and password is correct");

        hide();
        cw = new ClientWindow(clt, this);
        cw->show();
    } else {
//        QMessageBox::warning(this, "Login", "Wrong username or password");
        ui->statusbar->showMessage("Wrong username or password");
    }
}

