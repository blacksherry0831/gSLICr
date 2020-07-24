#cmake最低版本需求，不加入此行会受到警告信息
CMAKE_MINIMUM_REQUIRED(VERSION 3.8.1)
###############################################################################
C11_Config()  
###############################################################################
 CONFIGQT()
###############################################################################
SET(ROS_LIB_SRCS
		
	ROSBasic.cpp
	
	rosbridge_v2_0_protocol.cpp
	
	std_msgs_Header.cpp
	
	sensor_msgs_ChannelFloat32.cpp
	sensor_msgs_PointCloud.cpp

	geometry_msgs_Transform.cpp
	geometry_msgs_TransformStamped.cpp
	tf_tfMessage.cpp

	advertise_a_topic.cpp
	
	


	)
	
ADD_LIBRARY(ROS_LIB   STATIC    ${ROS_LIB_SRCS})
###############################################################################
	
##############################################################################

##############################################################################
