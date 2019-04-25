#cmake最低版本需求，不加入此行会受到警告信息
CMAKE_MINIMUM_REQUIRED(VERSION 3.8.1)
#项目名称
project(ZYNQ)



find_package(Threads REQUIRED) 

IF(UNIX)
   SET(MY_MATH_LIB m)
ELSE(UNIX)
   SET(MY_MATH_LIB)
ENDIF(UNIX)
  
	
include_directories(${PROJECT_SOURCE_DIR}/)

set (SRC_FILES 
		helloworld.c
		server_iptables.c)
###############################################################################
IF (CMAKE_SYSTEM_NAME MATCHES "Linux")  
 
		ADD_EXECUTABLE(TEST_IMAGE ${SRC_FILES})
		set(TEST_IMAGE_LIB ${MY_MATH_LIB})
		if(CMAKE_THREAD_LIBS_INIT)  
			set(TEST_IMAGE_LIB  
							${TEST_IMAGE_LIB}
							${CMAKE_THREAD_LIBS_INIT})
		endif() 		
		target_link_libraries(TEST_IMAGE 
										${TEST_IMAGE_LIB})  	
   
 
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")

 ConfigMFC_2()
 

 
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "FreeBSD")
   
ELSE ()  
   
ENDIF ()  


 
   