CMAKE_MINIMUM_REQUIRED(VERSION 3.8.1)
######################################
CONFIGQT()
ConfigCUDA()
ConfigOpenCv()
######################################
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
######################################
   
# Tell CMake to create the helloworld executable
					
CUDA_ADD_EXECUTABLE(EXE_NAV
							main_nav.cpp
					)

TARGET_LINK_LIBRARIES(EXE_NAV
							SGV)
				
######################################
