#ifndef MAIN_B_H
#define MAIN_B_H

#include "loginpage.h"
#include <QMainWindow>

namespace Ui {
class Main_b;
}

class Main_b : public QMainWindow
{
    Q_OBJECT

public:
    explicit Main_b(QString token,QWidget *parent = 0);
    ~Main_b();
    void getuserlist();




private:
    Ui::Main_b *ui;
    QNetworkAccessManager *manager;
    QNetworkRequest  req;
    QString token;
};

#endif // MAIN_B_H
