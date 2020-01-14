#ifndef SAVEMSG_H
#define SAVEMSG_H

#include <QThread>
#include <QImage>

class SaveMsg: public QThread
{
    Q_OBJECT

public:
    explicit SaveMsg(QObject *parent=0);
    ~SaveMsg();

    void start_s();

protected:
    virtual void run();

private:
    QString paths;
};

#endif // SAVEMSG_H
