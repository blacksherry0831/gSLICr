//#include "stdafx.h"
#include "CMD_CTRL.hpp"
/*-------------------------------------*/
/**
*
*
*/
/*-------------------------------------*/
CMD_CTRL::CMD_CTRL(CMD_CTRL * _p)
{
	this->From(_p);
}
/*-------------------------------------*/
/**
*
*
*/
/*-------------------------------------*/
CMD_CTRL::CMD_CTRL()
{

	this->SetCmdRemote();
}
/*-------------------------------------*/
/**
*
*
*/
/*-------------------------------------*/
CMD_CTRL::~CMD_CTRL() 
{
	
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void CMD_CTRL::From(CMD_CTRL * _data)
{
	CMD_CTRL_DATA::From(_data);
	this->copy(_data);
	
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void CMD_CTRL::Move(const CMD_CTRL * _p)
{
	CMD_CTRL_DATA::Move(_p);
	this->copy(_p);
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void CMD_CTRL::copy(const CMD_CTRL * _p)
{
	
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void CMD_CTRL::setRespCmd(CMD_TYPE_02_RESP _type, int work_mode)
{
	Q_ASSERT(_type == CMD_TYPE_02_RESP::CT_OK || _type == CMD_TYPE_02_RESP::CT_ERROR);

	f_header.f_cmd[0] = CMD_TYPE::CT_RESP;
	f_header.f_cmd[1] = _type;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void CMD_CTRL::Parse(char * _data,int _size)
{
	const int HeaderSize_ = sizeof(CMD_CTRL_DATA::CMD_CTRL_HEADER);
	const int BodySize_ = CMD_CTRL_DATA::GetCMDBodySize((CMD_CTRL_DATA::CMD_CTRL_HEADER*)_data);
	const char* body_data_= _data + HeaderSize_;
	/*----------------------------------------------------------*/
	this->destory();
	/*----------------------------------------------------------*/
	memcpy(&(this->f_header), _data, HeaderSize_);	
	f_data.insert(f_data.end(),body_data_,body_data_ +BodySize_);	
	f_data_size = f_data.size();	
	f_crc = _data[_size - 1];
	/*----------------------------------------------------------*/
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
int CMD_CTRL::IsResp() const
{

	if (this->f_header.f_cmd[0] == CMD_TYPE::CT_RESP  ) {

			Q_ASSERT(this->f_header.f_cmd[1] == CMD_TYPE_02_RESP::CT_OK || this->f_header.f_cmd[1] == CMD_TYPE_02_RESP::CT_ERROR || this->f_header.f_cmd[1] == CMD_TYPE_02_RESP::CT_NONE);
			
			return TRUE;

	}	

	return FALSE;

}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
int CMD_CTRL::isHeartbeatCmd()
{
	if (this->f_header.f_cmd[0] == CMD_TYPE::CT_HEART &&
		this->f_header.f_cmd[1] == CMD_TYPE_02::CT_BEAT) {
		return TRUE;
	}
	return FALSE;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
int CMD_CTRL::CmdStat()
{
	int stat = (this->f_header.f_cmd[1] *256) + this->f_header.f_cmd[0];
	return stat;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
int CMD_CTRL::IsThisCmd00(int _cmd)
{

	if (this->f_header.f_cmd[0] == _cmd) {
		
		return TRUE;
	}
	return FALSE;

}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
int CMD_CTRL::IsCmd(const unsigned char _cmd00,const unsigned char _cmd01) const
{
	//¹¤¼þ¾ÍÐ÷
	if (this->f_header.f_cmd[0] == _cmd00 &&
		this->f_header.f_cmd[1] == _cmd01) {
		return TRUE;
	}
	return FALSE;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
int CMD_CTRL::IsCmdCtrlStatus(const unsigned char _cmd01) const
{
	return IsCmd(CMD_TYPE::CT_STATUS,_cmd01);
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
int CMD_CTRL::GetCmd00()
{
	return this->f_header.f_cmd[0];
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
int CMD_CTRL::GetCmd01()
{
	return this->f_header.f_cmd[1];
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
int CMD_CTRL::GetCmdParam()
{
	Q_ASSERT(this->f_data.size() >= 2);
	const int param = this->f_data[0] + this->f_data[1] * 256;
	return param;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
int CMD_CTRL::SetCmdParam(int _param)
{
	Q_ASSERT(this->f_data.size() >= 2);
	 
	 this->f_data[0]=_param%256;
	 this->f_data[1]=_param/256;
	
	 return _param;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
std::vector<unsigned char> CMD_CTRL::getRespCmd(CMD_TYPE_02_RESP _type,int _param)
{
	this->setRespCmd(_type, 0x01);
	this->initHeader();
	this->initpc2pc();
	this->SetDataSize();
	this->SetCmdParam(_param);
	this->initCRC();
	return this->Data();
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
std::vector<unsigned char> CMD_CTRL::getLocalCmd(int _cmd00, int _cmd01, uint _circle_seq)
{

	this->initHeader();
	
#if TRUE

	f_header.f_cmd[0] = _cmd00;
	f_header.f_cmd[1] = _cmd01;

#endif // TRUE

	this->SetCmdFrameSeq(_circle_seq);

	this->SetCmdLocal();
	this->initCRC();
	return this->Data();
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
QSharedPointer<CMD_CTRL> CMD_CTRL::getLocalCmdEx(int _cmd00, int _cmd01,int _cmd_idx)
{	
	QSharedPointer<CMD_CTRL> qsp_c_c_t = QSharedPointer<CMD_CTRL>(new CMD_CTRL());

	qsp_c_c_t->getLocalCmd(_cmd00,_cmd01,_cmd_idx);

	return qsp_c_c_t;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/

std::vector<unsigned char> CMD_CTRL::getHeartBeatCmd(int _need_resp)
{

	Q_ASSERT(_need_resp == BodyHearBeatResp::HB_NONE ||
			_need_resp == BodyHearBeatResp::HB_RESP);

	this->initHeader();
	this->initHearbeatCmd(_need_resp);

	this->initCRC();
	return this->Data();
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
int CMD_CTRL::IsCmdRemote()
{
	return mCmdRemoteFlag;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
int CMD_CTRL::IsCmdLocal()
{
	return mCmdRemoteFlag == FALSE;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
int CMD_CTRL::SetCmdRemote()
{
	return mCmdRemoteFlag = TRUE;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
int CMD_CTRL::SetCmdLocal()
{
	return mCmdRemoteFlag = FALSE;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void CMD_CTRL::SetIpAddrRemote(QTcpSocket* _pSocket)
{
	this->mIpAddrRemote = _pSocket->peerAddress().toString().toStdString();
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
std::string CMD_CTRL::GetIpAddrRemote()
{
	return this->mIpAddrRemote;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
