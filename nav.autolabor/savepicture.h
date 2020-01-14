#ifndef SAVEPICTURE_H
#define SAVEPICTURE_H

#include <QThread>
#include <QImage>
#include <queue>
#include <QJsonDocument>
#include <QJsonObject>
#include <QQueue>

class SavePicture : public QThread
{
    Q_OBJECT

public:
    explicit SavePicture(QString path);
    ~SavePicture();

    void start_s();

protected:
    virtual void run();

private:
    QString paths;
};

#endif // SAVEPICTURE_H
