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

    ui->pushButton_cancel->setVisible(false);
    ui->label_3->setVisible(false);
    ui->lineEdit_Dispname->setVisible(false);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::clearInput() {
    ui->lineEdit_UserName->clear();
    ui->lineEdit_Password->clear();
    ui->lineEdit_Dispname->clear();
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
        ui->pushButton_cancel->setVisible(true);
        ui->pushButton_Login->setVisible(false);
        ui->label_3->setVisible(true);
        ui->lineEdit_Dispname->setVisible(true);
        ui->groupBox->setTitle("Sign Up");
        clearInput();
    } else {
        QString username = ui->lineEdit_UserName->text();
        QString password = ui->lineEdit_Password->text();
        QString dispname = ui->lineEdit_Dispname->text();

        emit receiveSignUp(username, password, dispname);
        ui->groupBox->setTitle("Sign In");
        ui->label_3->setVisible(false);
        ui->lineEdit_Dispname->setVisible(false);
        ui->pushButton_cancel->setVisible(false);
        ui->pushButton_Login->setVisible(true);
        clearInput();
    }
}


void LoginWindow::on_pushButton_cancel_clicked()
{
    ui->groupBox->setTitle("Sign In");
    ui->pushButton_cancel->setVisible(false);
    ui->pushButton_Login->setVisible(true);
    ui->label_3->setVisible(false);
    ui->lineEdit_Dispname->setVisible(false);
    clearInput();
}

