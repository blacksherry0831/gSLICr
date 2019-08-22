#pragma once
/*-----------------------------------*/
#include  "qt_basic.h"
/*-----------------------------------*/

/*-------------------------------------*/
/**
*
*
*/
/*-------------------------------------*/
class CMD_CTRL_DATA
{
public:
	/*-----------------------------------*/
	/**
	*
	*/
	/*-----------------------------------*/
	enum DEV {
		DEV_IPC = 0x00,
		DEV_PLC = 0x01,
		DEV_PLC_LR = 0x11,
		DEV_FPGA_ARM = 0x02,
		DEV_IPC_DATA_CENTER_101 = 0x65,
		DEV_IPC_DATA_CENTER_102 = 0x66,
		DEV_IPC_DATA_CENTER_103 = 0x67,
	};
	/*-----------------------------------*/
	/**
	*
	*/
	/*-----------------------------------*/
	enum CMD_TYPE {
		CT_HEART = 'h',
		CT_QUERY = 'q',
		CT_CTRL = 'c',
		CT_RESP = 'r',
		CT_STATUS = 's',
		CT_CMD = 'c',
		CT_IMG = 'I'
	};
	/*-----------------------------------*/
	/**
	*
	*/
	/*-----------------------------------*/
	enum CMD_TYPE_02 {
		

		CT_BEAT = 'b',
		
		CT_LR_RUN_2 = 0x20,
		CT_ROLLER_Q = 0x10
	};
	/*-----------------------------------*/
	/**
	*
	*/
	/*-----------------------------------*/
	enum CMD_TYPE_02_C {

		CT_START = 0x00,
		CT_STOP = 0x01,

		CT_START_00 = 0x10,
		CT_STOP_00 = 0x11,
		CT_START_01 = 0x20,
		CT_STOP_01 = 0x21,
	};
	/*-----------------------------------*/
	/**
	*
	*/
	/*-----------------------------------*/
	enum CMD_TYPE_02_I {

		CT_IMG_FRAME = 'F',
		CT_IMG_RECT = 'R',
		CT_IMG_MODE_CHANGE = 'M',
		CT_IMG_SIGMA_CHANGE = 'S',
		CT_IMG_MASK_CHANGE = 'K',

	};
	/*-----------------------------------*/
	/**
	*
	*/
	/*-----------------------------------*/
	enum CMD_TYPE_02_RESP {

		CT_OK = 0x00,
		CT_ERROR = 0x01,
		CT_NONE = 0x02,
	};
	/*-----------------------------------*/
	/**
	*
	*/
	/*-----------------------------------*/
	enum BodyHearBeatResp
	{
		HB_RESP = 'r',
		HB_NONE = 'n',
		HB_NOTHING = 0x00,
	};
	/*-----------------------------------*/
	/**
	*
	*/
	/*-----------------------------------*/
	enum BodyRollerQualified
	{
		Qualified =0x00 ,
		UnQualified = 0x01,
	};
	/*-----------------------------------*/
	/**
	*
	*/
	/*-----------------------------------*/
public:
	typedef struct {
		unsigned char f_header[4];
		unsigned char f_reserve[2];
		unsigned char f_cmd_idx[4];
		unsigned char f_dst_dev[2];
		unsigned char f_src_dev[2];
		unsigned char f_cmd[2];
		unsigned char f_data_len[2];

	}CMD_CTRL_HEADER;
public:
	CMD_CTRL_DATA(CMD_CTRL_DATA* _p);
	CMD_CTRL_DATA();
	~CMD_CTRL_DATA();

/*-------------------------------------*/
public:
		CMD_CTRL_HEADER f_header;
		std::vector<unsigned char> f_data;
		size_t f_data_size;
		unsigned char f_crc;

/*-------------------------------------*/
protected:
	void initHeader();
	void initHeaderBodySize(int _body_size);
	void SetCmdParam(const int _data);
	void init();
	void destory();
protected:
	void initPc2Arm();
	void initpc2plcLR();
	void initpc2pc();
	void initCRC();
public:
	void From(const CMD_CTRL_DATA *_data);
	void Move(const CMD_CTRL_DATA * _p);
private:
	void copy(const CMD_CTRL_DATA * _p);
public:
	void SetDataSize(const int _body_size = 2);
public:
	std::vector<unsigned char> Data();
public:
	static int UChar2Int(const unsigned char* const _data, const int _size);
	static int Int2UChar(int _size,unsigned char *_data );

public:
	static int GetCMDBodySize(CMD_CTRL_DATA::CMD_CTRL_HEADER* _cmd);


	void initHearbeatCmd(int _need_resp);
	
	void initHeaderCmd(int _cmd00,int _cmd01);

	void SetCmdFrameSeq(uint _cmd_idx);
	QString GetCmdFrameSeqStr();
	QString GetCmdFrameSeqTimeStr();
public:
	uint GetCmdFrameSeq();
};