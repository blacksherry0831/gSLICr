CMAKE_MINIMUM_REQUIRED(VERSION 3.8.1)
project(gSLICr.ex)
###############################################################################
option (BUILDING_RELEASE_MODE
        "" ON)
###############################################################################
if(BUILDING_RELEASE_MODE)
	SET(CMAKE_BUILD_TYPE "Release")
else()
	SET(CMAKE_BUILD_TYPE "Debug")
endif()
###############################################################################
option (BUILDING_OPENCV_LIB
        "" ON)
###############################################################################
if(BUILDING_OPENCV_LIB)
	SET(NEED_OPENCV		ON)
endif()
###############################################################################
	SET(NEED_CUDA		ON)
###############################################################################
INCLUDE(cmake/FindOpencv.cmake)
INCLUDE(cmake/FindQT.cmake)
INCLUDE(cmake/setCUDA.cmake)
#INCLUDE(cmake/SetMFC.cmake)
INCLUDE(cmake/LinuxPrepare.cmake)
###############################################################################
C11_Config()
ConfigOpenCv()
ConfigCUDA()

###############################################################################
IF(MSVC_IDE)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  add_definitions(-DUSING_CMAKE=1)
ELSE(MSVC_IDE)
  set(CFLAGS_WARN "-Wall -Wextra -Wno-unused-parameter -Wno-strict-aliasing")
  set(CMAKE_CXX_FLAGS "-fPIC -O3 -march=native ${CFLAGS_WARN} ${CMAKE_CXX_FLAGS}")
ENDIF(MSVC_IDE)
###############################################################################
###############################################################################
include_directories(${CMAKE_SOURCE_DIR})
###############################################################################
ADD_SUBDIRECTORY(cuda_Lib)
ADD_SUBDIRECTORY(gSLICr_Lib)
###############################################################################
ADD_SUBDIRECTORY(ORUtils)
ADD_SUBDIRECTORY(MY_SDK_LIB)
ADD_SUBDIRECTORY(ROS_LIB)
ADD_SUBDIRECTORY(QT_SDK_LIB)
ADD_SUBDIRECTORY(OPENCV_QT_SDK_LIB)
ADD_SUBDIRECTORY(SGVBaseCode)
ADD_SUBDIRECTORY(MemcpyCv_gSLICr)

ADD_SUBDIRECTORY(TRAFFIC_SIGN_LIB)

###############################################################################
ADD_SUBDIRECTORY(Fuzzy)
###############################################################################
ADD_SUBDIRECTORY(nav.autolabor)
###############################################################################
ADD_SUBDIRECTORY(main.nav)
###############################################################################
ADD_SUBDIRECTORY(SGV)
###############################################################################
ADD_SUBDIRECTORY(recognize.traffic.sign)
###############################################################################
add_executable(demo demo.cpp)
target_link_libraries(demo gSLICr_lib )
###############################################################################