#include <QWebSocket>
#include <quanju.h>
#include <QImage>

//全局变量
//QWebSocket Quanju::websocket;      //socket连接
double volatile Quanju::v1=0.125;
double volatile Quanju::v2=0.8;
double Quanju::x=0;
double Quanju::y=0;
int Quanju::flag[9]={0,0,0,0,0,0,0,0,0};
int volatile Quanju::change=0;
QQueue<QImage> Quanju::igs;
QQueue<QString> Quanju::msgs;
QMutex Quanju::mutex;
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
Quanju::Quanju()
{

}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
Quanju::~Quanju()
{

}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/