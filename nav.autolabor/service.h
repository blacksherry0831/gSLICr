#ifndef SERVICE_H
#define SERVICE_H
#include <QThread>
#include <QtWebSockets/QtWebSockets>

class Service : public QThread
{
    Q_OBJECT

public:
    Service(QObject *parent=0);
    Service(int i,QObject *parent=0);
    virtual void run();
    ~Service();
private:
    int j;
    QString path;

private slots:
//    void onconnected();
//    void disconnected();
//    void errorconnected(QAbstractSocket::SocketError error);
//    void receive(QString msg);

signals:
    void send(QString msg);
};

#endif // SERVICE_H
