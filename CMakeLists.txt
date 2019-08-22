CMAKE_MINIMUM_REQUIRED(VERSION 3.8.1)
project(gSLICr)
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
INCLUDE(cmake/SetMFC.cmake)
INCLUDE(cmake/LinuxPrepare.cmake)
###############################################################################
C11_Config()
ConfigOpenCv()
ConfigCUDA()
ConfigMFC_2()
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
###############################################################################
ADD_SUBDIRECTORY(ORUtils)
ADD_SUBDIRECTORY(MY_SDK_LIB)
ADD_SUBDIRECTORY(QT_SDK_LIB)
ADD_SUBDIRECTORY(SGVBaseCode)
ADD_SUBDIRECTORY(MemcpyCv_gSLICr)
###############################################################################
ADD_SUBDIRECTORY(main.nav)
###############################################################################
ADD_SUBDIRECTORY(SGV)
###############################################################################
set(GSLICR_LIB
gSLICr_Lib/engines/gSLICr_core_engine.h
gSLICr_Lib/engines/gSLICr_seg_engine.h
gSLICr_Lib/engines/gSLICr_seg_engine_GPU.h
gSLICr_Lib/engines/gSLICr_seg_engine_shared.h
gSLICr_Lib/engines/gSLICr_core_engine.cpp
gSLICr_Lib/engines/gSLICr_seg_engine.cpp
gSLICr_Lib/engines/gSLICr_seg_engine_GPU.cu
gSLICr_Lib/objects/gSLICr_settings.h
gSLICr_Lib/objects/gSLICr_spixel_info.h
gSLICr_Lib/gSLICr_defines.h
gSLICr_Lib/gSLICr.h
)
###############################################################################
SOURCE_GROUP(engines FILES ${GSLICR_LIB})
###############################################################################
cuda_add_library(gSLICr_lib
			${GSLICR_LIB}
			NVTimer.h
			OPTIONS -gencode arch=compute_30,code=compute_30)
target_link_libraries(gSLICr_lib ${CUDA_LIBRARY})
###############################################################################
add_executable(demo demo.cpp)
target_link_libraries(demo gSLICr_lib )
###############################################################################