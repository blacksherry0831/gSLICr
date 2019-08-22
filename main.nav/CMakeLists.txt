CMAKE_MINIMUM_REQUIRED(VERSION 3.8.1)
######################################
CONFIGQT()
ConfigCUDA()
ConfigOpenCv()
######################################
ConfigMFC_2()
######################################
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
######################################
   
# Tell CMake to create the helloworld executable
					
add_executable(EXE_NAV
							main_nav.cpp
				)

TARGET_LINK_LIBRARIES(EXE_NAV
							SGV)
				
######################################
