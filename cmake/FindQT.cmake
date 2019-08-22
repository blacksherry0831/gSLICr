cmake_minimum_required(VERSION 3.1.0)
###############################################################################
macro(CONFIGQT)


######################################
IF (CMAKE_SYSTEM_NAME MATCHES "Linux")  
   
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")  
	
	
 
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "FreeBSD")  
   
ELSE ()  
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")  
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")
######################################


	set(CMAKE_INCLUDE_CURRENT_DIR ON) 
	set(CMAKE_AUTOMOC ON)
	
###############################################################################
SET(QT_USE_QTMAIN TRUE)
SET(QT_DONT_USE_QTGUI TRUE)
###############################################################################
	
	FIND_PACKAGE(Qt5Core)
	FIND_PACKAGE(Qt5Gui)
	FIND_PACKAGE(Qt5Xml CONFIG REQUIRED)
	find_package(Qt5Widgets CONFIG REQUIRED)
	FIND_PACKAGE(Qt5SerialPort)
	FIND_PACKAGE(Qt5Network)
	
	LINK_LIBRARIES(		
					Qt5::Xml
					Qt5::Widgets
					Qt5::Core
					Qt5::Gui
					Qt5::SerialPort
					Qt5::Network)
	
	INCLUDE_DIRECTORIES(	
					${Qt5Xml_INCLUDES}
					${Qt5Widgets_INCLUDES}
					${Qt5Core_INCLUDES}
					${Qt5Gui_INCLUDES}
					${Qt5SerialPort_INCLUDES}
					${Qt5Network_INCLUDES})
  
endmacro()
###############################################################################