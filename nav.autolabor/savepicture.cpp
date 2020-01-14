#include "savepicture.h"
#include <QTimer>
#include <QDateTime>
#include <QDebug>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <quanju.h>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QDateTime>
#include <QDir>

//保存截图 多线程
SavePicture::SavePicture(QString path)
{
    paths=path;
}

SavePicture::~SavePicture()
{
    //delete &igs;

    qDebug()<<"exit!!!"<<endl;
}

void SavePicture::run()
{
    while(1)
    {
        Quanju::mutex.lock();
        if(!Quanju::igs.isEmpty() && !Quanju::msgs.isEmpty())
        {
            QImage img = Quanju::igs.dequeue();
            QString msg = Quanju::msgs.dequeue();

            qint64 t =QDateTime::currentDateTime().toMSecsSinceEpoch();
            QString name =QString("/%1").arg(t)+".jpg";

            if(!(img).save(paths+name,"jpg"))
            {
                qDebug()<<"picture save failed"<<endl;
            }

            QFile file(paths+"/shuju.txt");
            if(!file.open(QIODevice::ReadWrite | QIODevice::Append))
                qDebug()<<file.errorString();
            QTextStream out(&file);
            out<<msg<<" "<<t<<" jietu "<<"\n\r"<<endl;
            file.close();
        }
        Quanju::mutex.unlock();
    }
}

void SavePicture::start_s()
{
    this->start();
}
