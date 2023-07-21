#ifndef GROUPWINDOW_H
#define GROUPWINDOW_H

#include <QWidget>
#include <QMessageBox>

namespace Ui {
class GroupWindow;
}

class GroupWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GroupWindow(QWidget *parent = nullptr);
    ~GroupWindow();
    void addToSelected(QString username);
    void usrNotAv();

signals:
    void checkUser(QString username);
    void addToGroup(QString gname, std::vector<QString> userList);

private slots:
    void on_AddButton_clicked();

    void on_confirmButton_clicked();

private:
    Ui::GroupWindow *ui;
};

#endif // GROUPWINDOW_H
