cmake_minimum_required(VERSION 2.8.3)
project(active_contour)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  genmsg
  std_msgs
  geometry_msgs
  message_generation
)

find_package (OpenCV REQUIRED)

#set variables
set(INCLUDE_DIR include)
set(SRC_DIR src)
set(LIB_DIR libs)
set(Chanvese_LIBS Chanvese)

#MSG DEP
add_message_files(
  FILES
  snake.msg
)

generate_messages(
   DEPENDENCIES
   geometry_msgs
   std_msgs
 )

catkin_package(CATKIN_DEPENDS message_runtime)

include_directories( ${OpenCV_DIR} ${catkin_INCLUDE_DIRS} ${INCLUDE_DIR} ${LIB_DIR})

add_executable(main src/main.cpp)
add_library (Chanvese 
	${LIB_DIR}/chanvese/chanvese.c
	${LIB_DIR}/chanvese/chanvese.h
	${LIB_DIR}/chanvese/contour.c
	${LIB_DIR}/chanvese/contour.h)
add_dependencies(main my_package_generate_messages_cpp)
target_link_libraries(main ${catkin_LIBRARIES} ${OpenCV_LIBS} ${Chanvese_LIBS}) 



#add_executable(prova src/prova.cpp)
#target_link_libraries(prova ${catkin_LIBRARIES} ${Chanvese_LIBS} ${OpenCV_LIBS})
