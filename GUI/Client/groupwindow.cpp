#include "groupwindow.h"
#include "ui_groupwindow.h"

GroupWindow::GroupWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupWindow)
{
    ui->setupUi(this);
}

GroupWindow::~GroupWindow()
{
    delete ui;
}

void GroupWindow::addToSelected(QString username) {
    ui->listWidget->addItem(username);
}

void GroupWindow::usrNotAv() {
    QMessageBox::warning(this, "Not found", "Username you typed in is not found!");
    ui->lineEdit_username->clear();
    ui->lineEdit_group->clear();
}

void GroupWindow::on_AddButton_clicked()
{
    QString username = ui->lineEdit_username->text();
    emit checkUser(username);
}


void GroupWindow::on_confirmButton_clicked()
{
    QString gname = ui->lineEdit_group->text();
    std::vector<QString> userList;
    if (ui->listWidget->count() == 0) {
        QMessageBox::warning(this, "Cannot create group", "No username is typed in!");
    } else {
        for (int i = 0; i < ui->listWidget->count(); i++) {
            userList.push_back(ui->listWidget->item(i)->text());
        }
    }
    emit addToGroup(gname, userList);
}

