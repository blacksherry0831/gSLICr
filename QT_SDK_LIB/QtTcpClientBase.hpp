#pragma once

#include "cpp_stl.h"

#include  "qt_basic.h"

#include "CMD_CTRL.hpp"

#include "IPrintQ.hpp"

/*-------------------------------------*/
#define HEART_BEAT_FREQUENCY (5)
/*-------------------------------------*/
/**
*
*
*/
/*-------------------------------------*/
enum ResultMy
{
	INIT_MY = 255,
	SocketErrorMy = -1,
	SocketErrotTimeout=-2,
	TRUE_MY = 1,
	FALSE_MY = 0,
};
/*-------------------------------------*/
/**
*
*
*/
/*-------------------------------------*/
class QtTcpClientBase :public QTcpSocket ,public IPrintQ
{
	Q_OBJECT
public:
	enum SOCKET_STATUS {
		Error=-1,
		DisConnected = 0,
		Connected = 1,
		ReadWriteTimeOut =1,
		ErrorOccur=1,
		
	};
protected:
	int  MAX_MSECS;
public:
	explicit QtTcpClientBase(QObject *parent = Q_NULLPTR);
	~QtTcpClientBase(void);
protected:
	QByteArray m_buffer;
	int m_buffer_Length;
protected:
	int mSocketReadMaxTimeOut;
	int mSocketConnected;
protected:
	int mSocketRun;
	int mSocketErrorOccur;

	int mSocketReadTimeOut;
	int mSocketWriteTimeOut;
public:
	int init();
	ResultMy read_n_byte(int _n);
	ResultMy write_n_byte(const char* const _data, const int _size);
	int ReadAllMy(const int _size);
	int ReadMy(const int _size);
	int ReadMy_seg(const int _size);
	int ReadMy_all(const int _size);
	int WriteMy(QByteArray _data);
	int WriteMy(const char* const _data,const int _size);
public:
	int GetSocketConnected();
	int IsSocketAlive();
	int IsSocketConnected();
	int IsSocketError();
	void SetReadTimeOutMy(const unsigned int _max_time_out_ms);
	void disconnectFromHostMy();
public:
	void startSocketRun();
	void stopSocketRun();
public:

signals:
	void socket_connect_state(int);
public:

};