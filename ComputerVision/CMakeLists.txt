cmake_minimum_required(VERSION 2.8)

project( Cognitive-Robotics-Project )

find_package( OpenCV )

set(INCLUDE_DIR include)
set(SRC_DIR src)
set(LIB_DIR libs)

set(Chanvese_LIBS Chanvese)

include_directories( ${OpenCV_INCLUDE_DIRS} ${INCLUDE_DIR} ${LIB_DIR})

set(SOURCE_FILES 
	main.cpp
	${SRC_DIR}/Camera.cpp
	${INCLUDE_DIR}/Camera.h)

add_executable( Cognitive-Robotics-Project ${SOURCE_FILES})

add_library (Chanvese 
	${LIB_DIR}/chanvese/chanvese.c
	${LIB_DIR}/chanvese/chanvese.h
	${LIB_DIR}/chanvese/chanvesecli.c
	${LIB_DIR}/chanvese/chanvesecli.h
	${LIB_DIR}/chanvese/cliio.c
	${LIB_DIR}/chanvese/cliio.h
	${LIB_DIR}/chanvese/contour.c
	${LIB_DIR}/chanvese/contour.h)

target_link_libraries( Cognitive-Robotics-Project ${OpenCV_LIBS} ${Chanvese_LIBS} )