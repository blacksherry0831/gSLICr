#设置cmake版本号
CMAKE_MINIMUM_REQUIRED(VERSION 3.1.0)

#设置工程名称

#设置工程包含当前目录，非必须
set(CMAKE_INCLUDE_CURRENT_DIR ON) 

#设置自动生成moc文件
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()


C11_Config()
ConfigOpenCv()
ConfigCUDA()
#查找需要的Qt库文件，最好每一个库都要写，Qt也会根据依赖关系自动添加
CONFIGQT()

#查找当前文件夹中的所有源代码文件，也可以通过Set命令将所有文件设置为一个变量
FILE(GLOB SRC_FILES "./*.cxx") 
FILE(GLOB SRC_FILES "./*.cpp") 
#同理，查找当前文件夹中所有的头文件
FILE(GLOB HEAD_FILES "./*.h") 
#同理，查找当前文件夹中所有的ui文件
FILE(GLOB UI_FILES "./*.ui") 
#通过Ui文件生成对应的头文件，一定要添加
qt5_wrap_ui(WRAP_FILES ${UI_FILES})

#添加第三方库 ffmpeg
SET(FFMPEG_INCLUDE_DIRS	"./ffmpeg/include")
SET(FFMPEG_LIBRARY_DIRS	"./ffmpeg/lib")
INCLUDE_DIRECTORIES(${FFMPEG_INCLUDE_DIRS})
LINK_DIRECTORIES(${FFMPEG_LIBRARY_DIRS})


SET(FFMPEG_LIB
	avcodec
	avdevice
	avfilter
	avformat
	avutil
	postproc
	swresample
	swscale)


#创建工程文件
add_executable(EXE_NAV_AUTOLABOR ${SRC_FILES} ${HEAD_FILES} ${RCC_FILES} ${WRAP_FILES})

target_link_libraries(EXE_NAV_AUTOLABOR
						${FFMPEG_LIB}
						QT_SDK_LIB
						SGV
						)