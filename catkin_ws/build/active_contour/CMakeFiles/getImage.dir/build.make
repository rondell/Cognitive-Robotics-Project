# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/build

# Include any dependencies generated for this target.
include active_contour/CMakeFiles/getImage.dir/depend.make

# Include the progress variables for this target.
include active_contour/CMakeFiles/getImage.dir/progress.make

# Include the compile flags for this target's objects.
include active_contour/CMakeFiles/getImage.dir/flags.make

active_contour/CMakeFiles/getImage.dir/src/getImage.cpp.o: active_contour/CMakeFiles/getImage.dir/flags.make
active_contour/CMakeFiles/getImage.dir/src/getImage.cpp.o: /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/src/active_contour/src/getImage.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object active_contour/CMakeFiles/getImage.dir/src/getImage.cpp.o"
	cd /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/build/active_contour && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/getImage.dir/src/getImage.cpp.o -c /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/src/active_contour/src/getImage.cpp

active_contour/CMakeFiles/getImage.dir/src/getImage.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/getImage.dir/src/getImage.cpp.i"
	cd /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/build/active_contour && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/src/active_contour/src/getImage.cpp > CMakeFiles/getImage.dir/src/getImage.cpp.i

active_contour/CMakeFiles/getImage.dir/src/getImage.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/getImage.dir/src/getImage.cpp.s"
	cd /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/build/active_contour && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/src/active_contour/src/getImage.cpp -o CMakeFiles/getImage.dir/src/getImage.cpp.s

active_contour/CMakeFiles/getImage.dir/src/getImage.cpp.o.requires:
.PHONY : active_contour/CMakeFiles/getImage.dir/src/getImage.cpp.o.requires

active_contour/CMakeFiles/getImage.dir/src/getImage.cpp.o.provides: active_contour/CMakeFiles/getImage.dir/src/getImage.cpp.o.requires
	$(MAKE) -f active_contour/CMakeFiles/getImage.dir/build.make active_contour/CMakeFiles/getImage.dir/src/getImage.cpp.o.provides.build
.PHONY : active_contour/CMakeFiles/getImage.dir/src/getImage.cpp.o.provides

active_contour/CMakeFiles/getImage.dir/src/getImage.cpp.o.provides.build: active_contour/CMakeFiles/getImage.dir/src/getImage.cpp.o

# Object files for target getImage
getImage_OBJECTS = \
"CMakeFiles/getImage.dir/src/getImage.cpp.o"

# External object files for target getImage
getImage_EXTERNAL_OBJECTS =

/home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/devel/lib/active_contour/getImage: active_contour/CMakeFiles/getImage.dir/src/getImage.cpp.o
/home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/devel/lib/active_contour/getImage: active_contour/CMakeFiles/getImage.dir/build.make
/home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/devel/lib/active_contour/getImage: /opt/ros/indigo/lib/libroscpp.so
/home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/devel/lib/active_contour/getImage: /usr/lib/x86_64-linux-gnu/libboost_signals.so
/home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/devel/lib/active_contour/getImage: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
/home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/devel/lib/active_contour/getImage: /opt/ros/indigo/lib/librosconsole.so
/home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/devel/lib/active_contour/getImage: /opt/ros/indigo/lib/librosconsole_log4cxx.so
/home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/devel/lib/active_contour/getImage: /opt/ros/indigo/lib/librosconsole_backend_interface.so
/home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/devel/lib/active_contour/getImage: /usr/lib/liblog4cxx.so
/home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/devel/lib/active_contour/getImage: /usr/lib/x86_64-linux-gnu/libboost_regex.so
/home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/devel/lib/active_contour/getImage: /opt/ros/indigo/lib/libxmlrpcpp.so
/home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/devel/lib/active_contour/getImage: /opt/ros/indigo/lib/libroscpp_serialization.so
/home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/devel/lib/active_contour/getImage: /opt/ros/indigo/lib/librostime.so
/home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/devel/lib/active_contour/getImage: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
/home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/devel/lib/active_contour/getImage: /opt/ros/indigo/lib/libcpp_common.so
/home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/devel/lib/active_contour/getImage: /usr/lib/x86_64-linux-gnu/libboost_system.so
/home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/devel/lib/active_contour/getImage: /usr/lib/x86_64-linux-gnu/libboost_thread.so
/home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/devel/lib/active_contour/getImage: /usr/lib/x86_64-linux-gnu/libpthread.so
/home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/devel/lib/active_contour/getImage: /usr/lib/x86_64-linux-gnu/libconsole_bridge.so
/home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/devel/lib/active_contour/getImage: active_contour/CMakeFiles/getImage.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/devel/lib/active_contour/getImage"
	cd /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/build/active_contour && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/getImage.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
active_contour/CMakeFiles/getImage.dir/build: /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/devel/lib/active_contour/getImage
.PHONY : active_contour/CMakeFiles/getImage.dir/build

active_contour/CMakeFiles/getImage.dir/requires: active_contour/CMakeFiles/getImage.dir/src/getImage.cpp.o.requires
.PHONY : active_contour/CMakeFiles/getImage.dir/requires

active_contour/CMakeFiles/getImage.dir/clean:
	cd /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/build/active_contour && $(CMAKE_COMMAND) -P CMakeFiles/getImage.dir/cmake_clean.cmake
.PHONY : active_contour/CMakeFiles/getImage.dir/clean

active_contour/CMakeFiles/getImage.dir/depend:
	cd /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/src /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/src/active_contour /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/build /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/build/active_contour /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/build/active_contour/CMakeFiles/getImage.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : active_contour/CMakeFiles/getImage.dir/depend

