CMAKE_MINIMUM_REQUIRED(VERSION 3.8.1)
###############################################################################
C11_Config() 
###############################################################################
 CONFIGQT()
###############################################################################



IF (CMAKE_SYSTEM_NAME MATCHES "Linux")  
 
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
	ConfigMFC_2()
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "FreeBSD")
   
ELSE ()  
   
ENDIF ()  
###############################################################################

SET(QT_SDK_SRCS

		IPrintQ.cpp
		QBase.cpp
		
		CMD_CTRL_DATA.cpp
		CMD_CTRL.cpp
		CMD_CTRL_Q.cpp
		
		QtMsgCmdQ.cpp
				
		QtThreadBase.cpp
		QtThreadBaseCmdQ.cpp
				
		QtTcpClientBase.cpp
		QtTcpClientCmdCtrl.cpp)

ADD_LIBRARY(QT_SDK_LIB   STATIC    ${QT_SDK_SRCS})
###############################################################################
	
##############################################################################

##############################################################################
