CMAKE_MINIMUM_REQUIRED(VERSION 3.8.1)
###############################################################################
set(GSLICR_LIB
engines/gSLICr_core_engine.h
engines/gSLICr_seg_engine.h
engines/gSLICr_seg_engine_GPU.h
engines/gSLICr_seg_engine_shared.h
engines/gSLICr_core_engine.cpp
engines/gSLICr_seg_engine.cpp
engines/gSLICr_seg_engine_GPU.cu
objects/gSLICr_settings.h
objects/gSLICr_spixel_info.h
gSLICr_defines.h
gSLICr.h
)
###############################################################################
#set(CUDA_NVCC_FLAGS -gencode arch=compute_30,code=sm_30;-G;-g)
###############################################################################
#cuda_add_library(gSLICr_lib
#			${GSLICR_LIB})
###############################################################################
cuda_add_library(gSLICr_lib
			${GSLICR_LIB}
			OPTIONS -gencode arch=compute_30,code=compute_30)
###############################################################################
target_link_libraries(gSLICr_lib ${CUDA_LIBRARY})
###############################################################################