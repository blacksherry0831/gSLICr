CMAKE_MINIMUM_REQUIRED(VERSION 3.8.1)
###############################################################################
C11_Config() 
###############################################################################
CONFIGQT()
###############################################################################
ConfigOpenCv()
###############################################################################
IF (CMAKE_SYSTEM_NAME MATCHES "Linux")  
 
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
	
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "FreeBSD")
   
ELSE ()  
   
ENDIF ()  
###############################################################################
SET(OPENCV_QT_SDK_SRCS

		
		OpencvQtBase.cpp
		
		)

ADD_LIBRARY(OPENCV_QT_SDK_LIB   STATIC    ${OPENCV_QT_SDK_SRCS})
###############################################################################
