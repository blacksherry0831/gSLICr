CMAKE_MINIMUM_REQUIRED(VERSION 3.8.1)
######################################
ConfigOpenCv()
######################################
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
#set(CMAKE_AUTOMOC ON)
######################################
   
# Tell CMake to create the helloworld executable
					
CUDA_ADD_EXECUTABLE(EXE_TRAFFIC_SIGN
							TrafficSignParam.cpp
							TrafficSignTemplete.cpp
							TrafficSignMethod.cpp
							TrafficSignProperty.cpp
							main_traffic_sign.cpp
					)

TARGET_LINK_LIBRARIES(EXE_TRAFFIC_SIGN

								MY_SDK_LIB)
				
######################################
