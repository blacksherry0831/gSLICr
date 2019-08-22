############C++11#############################
# Determines whether or not the compiler supports C++11
macro(check_for_cxx11_compiler _VAR)
    #message(STATUS "Checking for C++11 compiler")
    set(${_VAR})
    if((MSVC AND (MSVC10 OR MSVC11 OR MSVC12)) OR
       (CMAKE_COMPILER_IS_GNUCXX AND NOT ${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS 4.6) OR
       (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND NOT ${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS 3.1))
        set(${_VAR} 1)
        #message(STATUS "Checking for C++11 compiler - available")
    else()
        #message(STATUS "Checking for C++11 compiler - unavailable")
    endif()
endmacro()

# Sets the appropriate flag to enable C++11 support
macro(enable_cxx11)
    if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
		#message(STATUS "-std=c++11")
    endif()
endmacro()


macro(C11_Config)

SET(C11_OPTION  "-std=c++11" )
check_for_cxx11_compiler(CXX11_COMPILER)

# If a C++11 compiler is available, then set the appropriate flags
if(CXX11_COMPILER)
    enable_cxx11()
    #set(CMAKE_CXX_STANDARD 11)
    #set(CMAKE_CXX_STANDARD_REQUIRED ON)
  
	#message(STATUS "Checking for C++11 compiler - available")
endif()
#if(CMAKE_COMPILER_IS_GNUCXX)
#    add_definitions(-std=gnu++11)
#endif()
IF(CMAKE_COMPILER_IS_GNUCXX)
set (CMAKE_CXX_FLAGS "-fpermissive")
ENDIF()  

IF(CMAKE_COMPILER_IS_GNUCXX)
	IF(CXX11_COMPILER)
		 add_compile_options(${C11_OPTION})
	ENDIF() 
ENDIF(CMAKE_COMPILER_IS_GNUCXX) 

#set_property(TARGET tgt PROPERTY CXX_STANDARD 11)

#set( CMAKE_C_FLAGS   "-fstack-protector -fstack-protector-all" )
#set( CMAKE_C_FLAGS_DEBUG   "-O2 -Wall -ggdb" )
#set( CMAKE_C_FLAGS_RELEASE   "-Os -Wall" )

#set( CMAKE_CXX_FLAGS "-fstack-protector -fstack-protector-all" )
#set( CMAKE_CXX_FLAGS_DEBUG "-O2 -Wall -ggdb" )
#set( CMAKE_CXX_FLAGS_RELEASE "-Os -Wall" )


endmacro()
#############################################

function(SetCompilerFeatures TGT_NAME)
  #----------------------------------------------------------
  # Set C++11 compatibility.
  #----------------------------------------------------------
  if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    if(NOT(TGT_NAME STREQUAL ""))
      target_compile_features(${TGT_NAME} PUBLIC ${needed_features})
    endif()
  elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    # Pick a MSVC version that supports what you need.
    if (MSVC_VERSION LESS "1800")
      message(FATAL_ERROR "No suitable compiler exists.")
    endif()
  elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
    set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")
  else()
    message(FATAL_ERROR "No suitable compiler exists.")
  endif()
endfunction()