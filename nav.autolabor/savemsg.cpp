#include "savemsg.h"
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

//多线程 保存信息
SaveMsg::SaveMsg(QObject *parent) :
    QThread(parent)
{
}

SaveMsg::~SaveMsg()
{

}



void SaveMsg::run()
{

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
    QString path=mydir.absolutePath()+"/shuju";

    QFile file(path+"/shuju.txt");
    if(!file.open(QIODevice::ReadWrite | QIODevice::Append))
        qDebug()<<file.errorString();
    //qDebug()<<path<<"/shuju.txt"<<endl;
    QTextStream out(&file);
    out<<msgss<<" "<<QDateTime::currentDateTime().toMSecsSinceEpoch()<<"\n\r"<<endl;
    file.close();
}
