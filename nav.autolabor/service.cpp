#include "service.h"
#include "mainwindow.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <quanju.h>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QDateTime>
#include <QDir>

//每隔1秒循环发送一次消息 多线程
Service::Service(QObject *parent) :
    QThread(parent)
{
}

Service::Service(int i,QObject *parent) :
    QThread(parent)
{
    this->j=i;
}

Service::~Service()
{

}

void Service::run()
{

//    QWebSocket websocket;
//    QUrl url = QUrl("ws://192.168.1.1:9090");
//    websocket.open(url);

    QJsonObject json;

    QJsonObject linear;
    linear.insert("x",Quanju::x*Quanju::v1);
    linear.insert("y",0);
    linear.insert("z",0);
    QJsonObject angular;
    angular.insert("x",0);
    angular.insert("y",0);
    angular.insert("z",Quanju::y*Quanju::v2);
    QJsonObject msg;
    msg.insert("linear",linear);
    msg.insert("angular",angular);

    json.insert("op","publish");
    json.insert("topic","/cmd_vel");
    json.insert("msg",msg);
    QJsonDocument json_doc;
    json_doc.setObject(json);
    QString msgss=json_doc.toJson(QJsonDocument::Compact);

    QDir mydir(QDir::currentPath());
    //path=mydir.absolutePath()+"/shuju";
	path = "D://shuju";

    while(Quanju::flag[j])
    {
        linear.insert("x",Quanju::x*Quanju::v1);
        angular.insert("z",Quanju::y*Quanju::v2);
        msg.insert("linear",linear);
        msg.insert("angular",angular);
        json.insert("msg",msg);
        json_doc.setObject(json);
        msgss=json_doc.toJson(QJsonDocument::Compact);

//        Quanju::websocket.sendTextMessage(msgss);
//        Quanju::websocket.flush();
//        qDebug()<<msgss<<endl;

        emit send(msgss);

        if(Quanju::change==1)
        {
            QFile file(path+"/shuju.txt");
            if(!file.open(QIODevice::ReadWrite | QIODevice::Append))
                qDebug()<<file.errorString();
            qDebug()<<path<<"/shuju.txt"<<endl;
            QTextStream out(&file);
            out<<msgss<<" "<<QDateTime::currentDateTime().toMSecsSinceEpoch()<<"\n\r"<<endl;
            file.close();
            Quanju::change=0;
        }

        sleep(1);  //停1s

        if(j==0) Quanju::flag[j]=0;
    }

    Quanju::flag[j]=0;
}
