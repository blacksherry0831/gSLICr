#ifndef QUANJU_H
#define QUANJU_H

#include <QWebSocket>
#include <QQueue>
#include <QImage>
#include <QMutex>

class Quanju
{
public:
    Quanju();
    ~Quanju();
    static QWebSocket websocket;
    static double volatile v1;       //线速度
    static double volatile v2;       //角速度
    static double x;                 //线速度方向
    static double y;                 //角速度方向
    static int flag[9];             //停 前进 后退 左 右 上左 上右 下左 下右
    static int volatile change;     //命令是否已经改变

    static QQueue<QImage> igs;
    static QQueue<QString> msgs;
    static QMutex mutex;
public:
	static void WebSocketSendMessage(QString _msg);
};

#endif // QUANJU_H
