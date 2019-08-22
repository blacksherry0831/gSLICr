//#include "stdafx.h"
#include "CMD_CTRL_DATA.hpp"
/*-------------------------------------*/
/**
*
*
*/
/*-------------------------------------*/
CMD_CTRL_DATA::CMD_CTRL_DATA(CMD_CTRL_DATA * _p)
{
	this->From(_p);
}
/*-------------------------------------*/
/**
*
*
*/
/*-------------------------------------*/
CMD_CTRL_DATA::CMD_CTRL_DATA()
{
		this->init();
		
}
/*-------------------------------------*/
/**
*
*
*/
/*-------------------------------------*/
CMD_CTRL_DATA::~CMD_CTRL_DATA()
{
		
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void CMD_CTRL_DATA::init()
{
	memset(&f_header, 0, sizeof(CMD_CTRL_HEADER));
	this->initHeader();
	this->initPc2Arm();

}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void CMD_CTRL_DATA::destory()
{
	this->f_data.clear();
	this->f_data_size = 0;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
std::vector<unsigned char> CMD_CTRL_DATA::Data()
{
	std::vector<unsigned char> cmd_data;

	cmd_data.insert(cmd_data.end(), f_header.f_header, f_header.f_header + 4);
	cmd_data.insert(cmd_data.end(), f_header.f_reserve, f_header.f_reserve + 2);
	cmd_data.insert(cmd_data.end(), f_header.f_cmd_idx, f_header.f_cmd_idx + 4);
	cmd_data.insert(cmd_data.end(), f_header.f_dst_dev, f_header.f_dst_dev + 2);

	cmd_data.insert(cmd_data.end(), f_header.f_src_dev, f_header.f_src_dev + 2);
	cmd_data.insert(cmd_data.end(), f_header.f_cmd, f_header.f_cmd + 2);
	cmd_data.insert(cmd_data.end(), f_header.f_data_len, f_header.f_data_len + 2);

	cmd_data.insert(cmd_data.end(), f_data.begin(), f_data.end());
	cmd_data.push_back(f_crc);

	return cmd_data;
}

/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void CMD_CTRL_DATA::initHeader()
{

	f_header.f_header[0] = 'Y';
	f_header.f_header[1] = 'j';
	f_header.f_header[2] = 'k';
	f_header.f_header[3] = 'j';

	this->SetDataSize();
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void CMD_CTRL_DATA::initHeaderBodySize(int _body_size)
{
	int low0_8bit = _body_size % 256;
	int high0_8bit = _body_size / 256 % 256;

	int low1_8bit = _body_size / 256 / 256 % 256;
	int high1_8bit = _body_size / 256 / 256 / 256;

	this->f_header.f_data_len[0] = low0_8bit;
	this->f_header.f_data_len[1] = high0_8bit;

	this->f_header.f_reserve[0] = low1_8bit;
	this->f_header.f_reserve[1] = high1_8bit;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void CMD_CTRL_DATA::SetDataSize(const int _body_size)
{
	if (f_data.size() < 2) {
		f_data.resize(2, 0);
	}
	else {
		f_data.resize(_body_size);
	}
	this->f_data_size = f_data.size();

	this->initHeaderBodySize(this->f_data_size);

}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void CMD_CTRL_DATA::initPc2Arm()
{
	//
	f_header.f_dst_dev[0] = DEV::DEV_FPGA_ARM;
	f_header.f_dst_dev[1] = 0x00;

	//
	f_header.f_src_dev[0] = DEV::DEV_IPC;
	f_header.f_src_dev[1] = 0x00;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void CMD_CTRL_DATA::SetCmdParam(const int _data)
{
	Q_ASSERT(f_data.size() >= 2);

	f_data[0] = _data % 256;//low
	f_data[1] = _data / 256;//height
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void CMD_CTRL_DATA::initpc2plcLR()
{
	//
	f_header.f_dst_dev[0] = DEV::DEV_PLC;
	f_header.f_dst_dev[1] = DEV::DEV_PLC_LR;

	//
	f_header.f_src_dev[0] = DEV::DEV_IPC;
	f_header.f_src_dev[1] = 0x00;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void CMD_CTRL_DATA::initpc2pc()
{
	//
	f_header.f_dst_dev[0] = DEV::DEV_IPC_DATA_CENTER_102;
	f_header.f_dst_dev[1] = 0x00;

	//
	f_header.f_src_dev[0] = DEV::DEV_IPC;
	f_header.f_src_dev[1] = 0x00;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void CMD_CTRL_DATA::initCRC()
{
	std::vector<unsigned char> data_t = this->Data();
	int crc = data_t.at(0);
	for (size_t i = 1; i <data_t.size() - 1; i++) {
		crc ^= data_t.at(i);
	}
	this->f_crc = crc;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
int  CMD_CTRL_DATA::UChar2Int(const unsigned char* const _data, const int _size)
{
	int value_t = 0;
	
	value_t = _data[0] +
		_data[1] * 256 +
		_data[2] * 256 * 256 +
		_data[3] * 256 * 256 * 256;

	return value_t;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
int CMD_CTRL_DATA::Int2UChar(int _size, unsigned char * _data)
{


	_data[0] = _size % 256;
	_data[1] = _size / 256 % 256;
	_data[2] = _size / 256 / 256 % 256;
	_data[3] = _size / 256 / 256 / 256 % 256;

	return _data[0];
}

/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
int CMD_CTRL_DATA::GetCMDBodySize(CMD_CTRL_DATA::CMD_CTRL_HEADER* _cmd)
{
	int size_t = _cmd->f_data_len[0] +
		_cmd->f_data_len[1] * 256 +
		_cmd->f_reserve[0] * 256 * 256 +
		_cmd->f_reserve[1] * 256 * 256 * 256;

	return size_t;

}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void CMD_CTRL_DATA::initHearbeatCmd(int _need_resp)
{
	initHeaderCmd(CMD_TYPE::CT_HEART, CMD_TYPE_02::CT_BEAT);
	this->SetCmdParam(_need_resp);
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void CMD_CTRL_DATA::initHeaderCmd(int _cmd00, int _cmd01)
{
	f_header.f_cmd[0] = _cmd00;
	f_header.f_cmd[1] = _cmd01;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void CMD_CTRL_DATA::SetCmdFrameSeq(uint _cmd_idx)
{

		this->f_header.f_cmd_idx[0] = _cmd_idx % 256;
		this->f_header.f_cmd_idx[1] = _cmd_idx /256 % 256;	
		this->f_header.f_cmd_idx[2] = _cmd_idx /256 /256% 256;
		this->f_header.f_cmd_idx[3] = _cmd_idx /256 /256 /256 % 256;
					
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
uint CMD_CTRL_DATA::GetCmdFrameSeq()
{
	const uint ucharMax = 256;
	uint seq_t= this->f_header.f_cmd_idx[0]+
				this->f_header.f_cmd_idx[1] *ucharMax + 
				this->f_header.f_cmd_idx[2] *ucharMax *ucharMax +
				this->f_header.f_cmd_idx[3] *ucharMax *ucharMax *ucharMax;

//	Q_ASSERT(seq_t != 0);
	return seq_t;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
QString CMD_CTRL_DATA::GetCmdFrameSeqStr()
{
	uint time_t = GetCmdFrameSeq();
	
	return QString::number(time_t);
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
QString CMD_CTRL_DATA::GetCmdFrameSeqTimeStr()
{
	 uint time_t=GetCmdFrameSeq();

	 QDateTime qdt = QDateTime::fromTime_t(time_t);

	return qdt.toString(QString("yyyyMMdd.hhmmss"));
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void CMD_CTRL_DATA::From(const CMD_CTRL_DATA * _data)
{
	this->f_data = _data->f_data;
	this->copy(_data);
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void CMD_CTRL_DATA::Move(const CMD_CTRL_DATA * _p)
{
	this->f_data = std::move(_p->f_data);
	this->copy(_p);
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void CMD_CTRL_DATA::copy(const CMD_CTRL_DATA * _p)
{
	this->f_header = _p->f_header;
	this->f_data_size = _p->f_data_size;
	this->f_crc = _p->f_crc;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/