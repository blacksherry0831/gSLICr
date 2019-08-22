CMAKE_MINIMUM_REQUIRED(VERSION 3.8.1)

macro(ConfigCUDA)

 
IF (CMAKE_SYSTEM_NAME MATCHES "Linux")  
	  #Searching CUDA
	  FIND_PACKAGE(CUDA) 
	  #Include the FindCUDA script
	  INCLUDE(FindCUDA) 
	  set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} -std=c++11" )
ELSE (CMAKE_SYSTEM_NAME MATCHES "Windows")  
	  #Searching CUDA
	  FIND_PACKAGE(CUDA QUIET REQUIRED)	 
	  #Include the FindCUDA script
	  INCLUDE(FindCUDA) 
	  
	  include_directories(${CUDA_INCLUDE_DIRS})

	  
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")  

if(APPLE)
  set(CUDA_HOST_COMPILER /usr/bin/clang)
endif(APPLE)

endmacro()