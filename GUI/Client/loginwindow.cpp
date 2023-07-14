#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

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

    emit receivedAuth(username, password);
}


void LoginWindow::on_pushButton_clicked()
{
    if (!ui->pushButton_Login->isHidden()) {
        ui->pushButton_Login->setVisible(false);
        ui->groupBox->setTitle("Sign Up");
    } else {
        QString username = ui->lineEdit_UserName->text();
        QString password = ui->lineEdit_Password->text();

        emit receiveSignUp(username, password);
    }
}

