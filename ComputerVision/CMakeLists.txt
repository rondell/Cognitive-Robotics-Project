cmake_minimum_required(VERSION 2.8)

project( Cognitive-Robotics-Project )

find_package( OpenCV )

set(INCLUDE_DIR include)
set(SRC_DIR src)
set(LIB_DIR lib)
set(CHANVESE_LIB Chanvese)

include_directories( ${OpenCV_INCLUDE_DIRS} ${LIB_DIR} ${INCLUDE_DIR})

set(SOURCE_FILES 
	main.cpp
	${SRC_DIR}/Camera.cpp
	${INCLUDE_DIR}/Camera.h
)

add_library (Chanvese 
	${LIB_DIR}/Chanvese.h
	${LIB_DIR}/Chanvese.c
	${LIB_DIR}/Contour.h
	${LIB_DIR}/Contour.c)

add_executable( Cognitive-Robotics-Project ${SOURCE_FILES})

target_link_libraries( Cognitive-Robotics-Project ${CHANVESE_LIB} ${OpenCV_LIBS} )