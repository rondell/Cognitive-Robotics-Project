cmake_minimum_required(VERSION 2.8)

project( Cognitive-Robotics-Project )

find_package( OpenCV )

set(INCLUDE_DIR include)
set(LIB_DIR lib)

include_directories( ${OpenCV_INCLUDE_DIRS} ${INCLUDE_DIR})

set(SOURCE_FILES 
	main.cpp
)

add_executable( Cognitive-Robotics-Project ${SOURCE_FILES})

target_link_libraries( Cognitive-Robotics-Project ${OpenCV_LIBS} )