//#include "stdafx.h"
#include "QtTcpClientBase.hpp"
/*-------------------------------------*/
/**
*
*
*/
/*-------------------------------------*/

/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
QtTcpClientBase::QtTcpClientBase(QObject *parent):QTcpSocket(parent)
{
	
	MAX_MSECS =30000;
	mSocketRun = TRUE;
	m_buffer.clear();
	mSocketErrorOccur=0;
	mSocketReadMaxTimeOut = 0;

	m_buffer.reserve(2 * 1024 * 1024);


}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
QtTcpClientBase::~QtTcpClientBase(void)
{


}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
int  QtTcpClientBase::init()
{
	return 0;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
int  QtTcpClientBase::ReadAllMy(const int _size)
{
	Q_ASSERT(_size >= 0);

#if 1
	return this->ReadMy_all(_size);
#else
	return ReadMy_seg(_size);
#endif // 0

	
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
int  QtTcpClientBase::ReadMy(const int _size)
{
	//QByteArray qba;	
	 char buff[16*1024];

	if (this->waitForReadyRead(MAX_MSECS)) {
	
		

		int len_t=this->read(buff, 16*1024);

//		SocketError error = this->error();
//		qDebug() << this->errorString();
		
		if (len_t > 0) {
			m_buffer.append(buff,len_t);
			return TRUE;
		
		}else{
			return FALSE;
		}
	}else {

		SocketError error=this->error();
		QString  error_str_t = this->errorString();
		if (error == SocketError::ConnectionRefusedError
			&&  error_str_t.isEmpty()) {
			//maybe time out
			return TRUE;
		}else{
			qDebug() << error_str_t;
			return FALSE;
		}
		
	}

	return IsSocketAlive();
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
int  QtTcpClientBase::ReadMy_seg(const int _size)
{
	QByteArray qba(_size,0);	
	char* buff = qba.data();
	int size_left = _size;

	while (this->mSocketRun){
		
								if (this->waitForReadyRead(MAX_MSECS)) {

											int len_t = this->read(&buff[_size-size_left], size_left);
		
											if (len_t > 0) {
												size_left -= len_t;
											}else if (len_t == 0) {
												Q_ASSERT(1);//no data
											}else if (len_t == -1) {
												this->mSocketConnected = SOCKET_STATUS::DisConnected;
												return SOCKET_STATUS::Error;//socket error
											}
											else {
												Q_ASSERT(0);
											}
											
								}else {

									mSocketReadTimeOut += MAX_MSECS;
									
								}

								if (size_left == 0)
								{
									break;
								}
				
	}
	
	if (size_left==0)
	{
		m_buffer.append(qba);
	}
	
	return (_size-size_left);
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
int  QtTcpClientBase::ReadMy_all(int _size)
{
	Q_ASSERT(_size >= 0);

	QByteArray qba;
	mSocketReadTimeOut=0;
	if (this->waitForReadyRead(MAX_MSECS)) {
		
		qba = this->readAll();
		Q_ASSERT(qba.size() > 0);
		m_buffer.append(qba);
		return qba.size();

	}else {
#if _DEBUG
				QString error_t = __func__;
				error_t + "Socket Read time out error !";
				printf_event_q(this->objectName(), error_t);
#endif		
				mSocketReadTimeOut += MAX_MSECS;
		
				if (mSocketReadTimeOut>mSocketReadMaxTimeOut){
#if _DEBUG && 0
							Q_ASSERT(0);
#endif // _DEBUG
							this->mSocketConnected = SOCKET_STATUS::DisConnected;
							return SOCKET_STATUS::Error;
				}

		return SOCKET_STATUS::Error;

	}


}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
int  QtTcpClientBase::WriteMy(QByteArray _data)
{
	return this->WriteMy(_data.data(),_data.size());
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
int  QtTcpClientBase::WriteMy(const char* const _data,const int _size)
{
	assert(_size > 0);
	assert(_data!=NULL);

	const char* buff_t = _data;
	int left = _size;

	do
	{
		const int size = this->write(buff_t, left);

		if (size==-1){
			this->mSocketConnected = SOCKET_STATUS::DisConnected;
			this->mSocketErrorOccur = SOCKET_STATUS::ErrorOccur;
			return FALSE;//error
		}else if(size>=0){
	
				if (this->waitForBytesWritten(MAX_MSECS)) {
					//success
					left -= size;
					buff_t += size;

				}else{
					this->mSocketConnected = SOCKET_STATUS::DisConnected;
					this->mSocketWriteTimeOut = SOCKET_STATUS::ReadWriteTimeOut;
					return FALSE;//if the operation timed out, or if an error occurred
					
				}


		}else{
			assert(0);

		}
		
		if (left==0)
		{
			break;
		}

	} while (this->mSocketRun);
	
	assert(left == 0);

	return TRUE;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/

/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/

/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
int  QtTcpClientBase::IsSocketAlive()
{
	return this->IsSocketConnected();
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
int  QtTcpClientBase::IsSocketConnected()
{
	QAbstractSocket::SocketState stat_t = this->state();
	QAbstractSocket::SocketError error_t = this->error();
	if (stat_t == QAbstractSocket::SocketState::UnconnectedState) {

		printf_event_q(objectName(), "socket is UnconnectedState");
		
	}
	else if (stat_t == QAbstractSocket::SocketState::HostLookupState) {

		printf_event_q(objectName(), "socket is HostLookupState");  
		return TRUE;

	}
	else if (stat_t == QAbstractSocket::SocketState::ConnectingState) {

		printf_event_q(objectName(),  "socket is ConnectingState"); 
	
		return TRUE;
		
	}
	else if (stat_t == QAbstractSocket::SocketState::ConnectedState) {

		return TRUE;

	}
	else if (stat_t == QAbstractSocket::SocketState::BoundState) {

		printf_event_q(objectName(), "socket is BoundState"); 

	}
	else if (stat_t == QAbstractSocket::SocketState::ClosingState) {

		printf_event_q(objectName(), "socket is :ClosingState" );

	}
	else if (stat_t == QAbstractSocket::SocketState::ListeningState) {

		printf_event_q(objectName(), "socket is ListeningState");
		return TRUE;

	}
	else {
		

	}

	return FALSE;


}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
int  QtTcpClientBase::IsSocketError()
{

	if (this->IsSocketAlive()==TRUE) {	
	
		SocketError error = this->error();
		QString  error_str_t = this->errorString();
		
		qDebug() << error_str_t;

		if (error == SocketError::SocketTimeoutError) {

			return TRUE;//time out

		} else {
		

		}

		
	
	}

	return FALSE;

}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void  QtTcpClientBase::disconnectFromHostMy()
{
	QAbstractSocket::SocketState stat_t = this->state();
	if (stat_t== QAbstractSocket::SocketState::ConnectedState) {
		this->disconnectFromHost();
		if (QAbstractSocket::ConnectedState == this->state())
			this->waitForDisconnected();
	}

}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void  QtTcpClientBase::startSocketRun()
{
	mSocketRun = TRUE;
	m_buffer.clear();
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void  QtTcpClientBase::stopSocketRun()
{
	mSocketRun = FALSE;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
ResultMy  QtTcpClientBase::read_n_byte(int _n)
{
	int  len_t = 0;
	char buff[1024];
	ResultMy result_my_t=ResultMy::INIT_MY;
	Q_ASSERT(_n<=1024);

	if (this->waitForReadyRead(MAX_MSECS)) {
		
		len_t = this->read(buff, _n);
		
		if (len_t >= 0) {
			m_buffer.append(buff, len_t);
			result_my_t=ResultMy::TRUE_MY;

		}else if(len_t==-1) {
			this->mSocketErrorOccur = TRUE;
			result_my_t = ResultMy::SocketErrorMy;
		}else {
			Q_ASSERT(FALSE);
		}

	}else {

		SocketError error = this->error();
		QString  error_str_t = this->errorString();
		if ( error_str_t.isEmpty()) {
			result_my_t = ResultMy::SocketErrotTimeout;
		}
		else {
			result_my_t = ResultMy::SocketErrorMy;
		}

	}

	if (!IsSocketAlive()) {

		result_my_t = ResultMy::SocketErrorMy;

	}

	return result_my_t;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
ResultMy  QtTcpClientBase::write_n_byte(const char * const _data, const int _size)
{
	Q_ASSERT(_size > 0);
	Q_ASSERT(_data != NULL);

	const char* buff_t = _data;
	int left = _size;
	ResultMy result_my_t = ResultMy::INIT_MY;

	do
	{
		const int size = this->write(buff_t, left);

		if (size == -1) {

			result_my_t = ResultMy::SocketErrorMy;
			return result_my_t;
		
		}else if (size >= 0) {

			if (this->waitForBytesWritten(MAX_MSECS)) {
				//success
				left -= size;
				buff_t += size;

			}
			else {

				result_my_t = ResultMy::SocketErrorMy;

				//if the operation timed out, or if an error occurred
			}


		}
		else {
			Q_ASSERT(0);

		}


	} while (left>0);

	Q_ASSERT(left == 0);
	
	if (left==0)
	{
		result_my_t = ResultMy::TRUE_MY;
	}
	else
	{
		result_my_t = ResultMy::FALSE_MY;
	}

	return result_my_t;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/

/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/

/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/

/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
int  QtTcpClientBase::GetSocketConnected()
{
	return this->mSocketConnected;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void  QtTcpClientBase::SetReadTimeOutMy(const unsigned int _max_time_out_ms)
{
	mSocketReadMaxTimeOut = _max_time_out_ms;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/