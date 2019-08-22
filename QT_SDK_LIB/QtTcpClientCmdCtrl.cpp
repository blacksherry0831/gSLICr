//#include "stdafx.h"
#include "QtTcpClientCmdCtrl.hpp"
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
QtTcpClientCmdCtrl::QtTcpClientCmdCtrl(QObject *parent):QtTcpClientBase(parent)
{
	
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
QtTcpClientCmdCtrl::~QtTcpClientCmdCtrl(void)
{


}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
int QtTcpClientCmdCtrl::SendHearbeatCmd(int _need_resp)
{
	CMD_CTRL cmd;
	cmd.getHeartBeatCmd(_need_resp);
	return this->Send_1_cmd(&cmd);
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
int  QtTcpClientCmdCtrl::Send_1_cmd(CMD_CTRL *_cmd)
{
	std::vector<unsigned char> data = _cmd->Data();
	return this->WriteMy((char*)data.data(), data.size());
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
int  QtTcpClientCmdCtrl::Read_1_cmd(CMD_CTRL *_cmd)
{
	const int HeaderSize = sizeof(CMD_CTRL_DATA::CMD_CTRL_HEADER);
	int DataALLSize_ = -1;
	int BodySize_ = -1;
	int READSIZE=HeaderSize;

#if TRUE
	_cmd->SetIpAddrRemote((QTcpSocket*)this);
#endif // TRUE
	

	if (mSocketRun==FALSE){
		return FALSE;
	}

	do {
	
		if (this->m_buffer.size() < HeaderSize) {
			if (this->ReadAllMy(HeaderSize) == SOCKET_STATUS::Error) return FALSE;
		}else {
			if (DataALLSize_ != -1 && this->m_buffer.size() < DataALLSize_) {
				if (this->ReadAllMy(DataALLSize_ - HeaderSize) == SOCKET_STATUS::Error) return FALSE;
			}		
		}
				
		const int CurrentBuffSize = this->m_buffer.size();

		while (CurrentBuffSize>=HeaderSize)
		{
			if (CurrentBuffSize >= HeaderSize) {			

				if ((m_buffer[0] == 'Y') &&
					(m_buffer[1] == 'j') &&
					(m_buffer[2] == 'k') &&
					(m_buffer[3] == 'j')) {					

						char *  header_data = m_buffer.data();

						BodySize_ = CMD_CTRL_DATA::GetCMDBodySize((CMD_CTRL_DATA::CMD_CTRL_HEADER*) header_data);

						if (BodySize_ < 2)	BodySize_ = 2;

						DataALLSize_ = HeaderSize + BodySize_ + 1;

						if (DataALLSize_ != -1 && CurrentBuffSize >= DataALLSize_) {
							_cmd->Parse(m_buffer.data(), DataALLSize_);
							m_buffer.remove(0, DataALLSize_);
							return TRUE;
						}

					break;
				}
				else
				{
					Q_ASSERT(0);
					m_buffer.remove(0, 1);
				}

			}




		}
					
		if (this->IsSocketAlive()==FALSE) {
			return FALSE;
		}

	} while (mSocketRun);
	// a frame is ok
	



	return TRUE;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
int QtTcpClientCmdCtrl::Read_1_cmd_fast(CMD_CTRL * _cmd)
{
	

	return TRUE;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
int QtTcpClientCmdCtrl::getByteTcpRead()
{
	int data_result = 0xffffffff;
	const int GET_IDX = 0;
	const int GET_SIZE = 1;
	
	if (this->m_buffer.size()>0){

		data_result = this->m_buffer.at(GET_IDX);

		this->m_buffer.remove(GET_IDX, GET_SIZE);

	}

	return  data_result;

}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
