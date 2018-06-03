#ifndef REGISTER_H
#define REGISTER_H
#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
    #include <QNetworkAccessManager>
    #include <QNetworkReply>
    #include <QNetworkRequest>
    #include <QUrlQuery>
    #include <QUrl>
    #include <QJsonDocument>
    #include <QJsonObject>
    #include<QDebug>

namespace Ui {
class Register;
}

class Register : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Register(QWidget *parent = 0);

    void reg();
    void reply(QNetworkReply *reply);
    ~Register();
    
private slots:
    void on_login_clicked();

private:
    Ui::Register *ui2;
    QNetworkAccessManager *manager;
    QNetworkRequest  req;
};

#endif // REGISTER_H
