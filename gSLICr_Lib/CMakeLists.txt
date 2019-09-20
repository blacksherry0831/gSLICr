CMAKE_MINIMUM_REQUIRED(VERSION 3.8.1)
###############################################################################
set(GSLICR_LIB

gSLICr.h
gSLICr_defines.h

objects/gSLICr_settings.h
objects/gSLICr_spixel_info.h

engines/gSLICr_seg_engine_shared.h
engines/gSLICr_seg_engine_map.cpp

engines/gSLICr_core_engine.h
engines/gSLICr_core_engine.cpp

engines/gSLICr_core_engine_cluster.h
engines/gSLICr_core_engine_cluster.cpp

engines/gSLICr_seg_engine.h
engines/gSLICr_seg_engine.cpp

engines/gSLICr_seg_engine_GPU.h
engines/gSLICr_seg_engine_GPU.cu

engines/gSLICr_seg_engine_GPU_cluster.h
engines/gSLICr_seg_engine_GPU_cluster.cu

)
################################################################################
#	TITAN Z | nvcc_ARCH += -gencode=arch=compute_35,code="sm_35,compute_35"
################################################################################
#	set(CUDA_NVCC_FLAGS -gencode arch=compute_35,code=sm_35;-G;-g)
###############################################################################
IF (CMAKE_BUILD_TYPE STREQUAL "Debug")        
     SET(CUDA_NVCC_FLAGS 
			${CUDA_NVCC_FLAGS};
			-G;
			-g
		)     
		message(STATUS "CUDA>> DEBUG")
ELSE()
		message(STATUS "CUDA>> RELEASE")         
ENDIF()
###############################################################################
#IF(MSVC_IDE)
#	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
#	add_definitions(-DUSING_CMAKE=1)
#ELSE(MSVC_IDE)
#	set(CFLAGS_WARN "-Wall -Wextra -Wno-unused-parameter -Wno-strict-aliasing")
#	set(CMAKE_CXX_FLAGS "-fPIC -O3 -march=native ${CFLAGS_WARN} ${CMAKE_CXX_FLAGS}")
#ENDIF(MSVC_IDE)
###############################################################################
add_definitions(-D_USE_MATH_DEFINES)
###############################################################################
SET(CUDA_NVCC_FLAGS 
		${CUDA_NVCC_FLAGS};
		-gencode arch=compute_35,code=compute_35;
		)
###############################################################################
cuda_add_library(gSLICr_lib
			${GSLICR_LIB}
			)
###############################################################################
target_link_libraries(gSLICr_lib ${CUDA_LIBRARY})
###############################################################################
