#pragma once
/*-----------------------------------*/
#include "cpp_stl.h"
#include  "qt_basic.h"
/*-----------------------------------*/
/**
*
*/
/*-----------------------------------*/
#include "CMD_CTRL_DATA.hpp"
/*-----------------------------------*/
/**
*
*/
/*-----------------------------------*/
class CMD_CTRL :public CMD_CTRL_DATA
{
public:
	CMD_CTRL(CMD_CTRL* _p);
	CMD_CTRL();
	~CMD_CTRL();
public:
	void From(CMD_CTRL* _data);
	void Move(const CMD_CTRL* _p);
private:
	void copy(const CMD_CTRL* _p);
/*-------------------------------------*/
public:
	int mCmdRemoteFlag;
	std::string mIpAddrLocal;
private:
	std::string mIpAddrRemote;
public:
	int IsCmdRemote();
	int IsCmdLocal();
	int SetCmdRemote();
	int SetCmdLocal();
public:
	void SetIpAddrRemote(QTcpSocket* _pSocket);
	std::string GetIpAddrRemote();
/*-------------------------------------*/
public:
	void setRespCmd(CMD_TYPE_02_RESP _type, int work_mode);	
public:
	std::vector<unsigned char>	getRespCmd(CMD_TYPE_02_RESP _type, int _param);
		
	std::vector<unsigned char>  getHeartBeatCmd(int _need_resp);
private:
	std::vector<unsigned char>  getLocalCmd(int _cmd00, int _cmd01 = 0x00, uint _circle_seq = 0);
public:
	static QSharedPointer<CMD_CTRL> getLocalCmdEx(int _cmd00, int _cmd01 = 0x00,int _cmd_idx=0);
public:
	void Parse(char* _data,int _size);
public:
	int IsResp() const;
	int isHeartbeatCmd();
	int CmdStat();
public:
	int IsThisCmd00(int _cmd);
	int IsCmd(const unsigned char _cmd00,const unsigned char _cmd01) const;
	int IsCmdCtrlStatus(const unsigned char _cmd01) const;
	int GetCmd00();
	int GetCmd01();
	int GetCmdParam();
	int SetCmdParam(int _param);

	
};