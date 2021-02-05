CMAKE_MINIMUM_REQUIRED(VERSION 3.8.1)
######################################
ConfigOpenCv()
######################################
SET(TRAFFIC_SIGN_SRCS

							TrafficSignParam.cpp
							TrafficSignTemplete.cpp
							
							TrafficSignMethodBase.cpp
							TrafficSignMethod.cpp
							TrafficSignMethodHu.cpp
							
							TrafficSignPropertyBase.cpp
							TrafficSignProperty.cpp
							TrafficSignPropertyHu.cpp
							
							TrafficSignResult.cpp
	
	)
######################################
	
ADD_LIBRARY(TRAFFIC_SIGN_LIB   STATIC    ${TRAFFIC_SIGN_SRCS})

				
######################################
