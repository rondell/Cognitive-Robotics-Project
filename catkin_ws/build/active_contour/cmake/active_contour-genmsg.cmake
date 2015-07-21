# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "active_contour: 1 messages, 0 services")

set(MSG_I_FLAGS "-Iactive_contour:/home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/src/active_contour/msg;-Igeometry_msgs:/opt/ros/indigo/share/geometry_msgs/cmake/../msg;-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(active_contour_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/src/active_contour/msg/snake.msg" NAME_WE)
add_custom_target(_active_contour_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "active_contour" "/home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/src/active_contour/msg/snake.msg" ""
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(active_contour
  "/home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/src/active_contour/msg/snake.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/active_contour
)

### Generating Services

### Generating Module File
_generate_module_cpp(active_contour
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/active_contour
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(active_contour_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(active_contour_generate_messages active_contour_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/src/active_contour/msg/snake.msg" NAME_WE)
add_dependencies(active_contour_generate_messages_cpp _active_contour_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(active_contour_gencpp)
add_dependencies(active_contour_gencpp active_contour_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS active_contour_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(active_contour
  "/home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/src/active_contour/msg/snake.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/active_contour
)

### Generating Services

### Generating Module File
_generate_module_lisp(active_contour
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/active_contour
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(active_contour_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(active_contour_generate_messages active_contour_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/src/active_contour/msg/snake.msg" NAME_WE)
add_dependencies(active_contour_generate_messages_lisp _active_contour_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(active_contour_genlisp)
add_dependencies(active_contour_genlisp active_contour_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS active_contour_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(active_contour
  "/home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/src/active_contour/msg/snake.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/active_contour
)

### Generating Services

### Generating Module File
_generate_module_py(active_contour
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/active_contour
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(active_contour_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(active_contour_generate_messages active_contour_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/src/active_contour/msg/snake.msg" NAME_WE)
add_dependencies(active_contour_generate_messages_py _active_contour_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(active_contour_genpy)
add_dependencies(active_contour_genpy active_contour_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS active_contour_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/active_contour)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/active_contour
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
add_dependencies(active_contour_generate_messages_cpp geometry_msgs_generate_messages_cpp)
add_dependencies(active_contour_generate_messages_cpp std_msgs_generate_messages_cpp)

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/active_contour)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/active_contour
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
add_dependencies(active_contour_generate_messages_lisp geometry_msgs_generate_messages_lisp)
add_dependencies(active_contour_generate_messages_lisp std_msgs_generate_messages_lisp)

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/active_contour)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/active_contour\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/active_contour
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
add_dependencies(active_contour_generate_messages_py geometry_msgs_generate_messages_py)
add_dependencies(active_contour_generate_messages_py std_msgs_generate_messages_py)
