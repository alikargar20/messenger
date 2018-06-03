#include "loginpage.h"
#include <QApplication>
#include<QPainter>
#include<QPixmap>
#include<QGraphicsView>
#include<QGraphicsScene>
#include<QGraphicsPixmapItem>
#include"register.h"
#include"main_b.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    LoginPage w;
    w.show();
   // qDebug()<<w.succeed;
   // if(w.succeed==1){
    //Main_b  x(w.getToken());

    //}

    return a.exec();
}
