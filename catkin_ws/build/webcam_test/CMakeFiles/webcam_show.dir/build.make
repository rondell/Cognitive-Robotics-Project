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
include webcam_test/CMakeFiles/webcam_show.dir/depend.make

# Include the progress variables for this target.
include webcam_test/CMakeFiles/webcam_show.dir/progress.make

# Include the compile flags for this target's objects.
include webcam_test/CMakeFiles/webcam_show.dir/flags.make

webcam_test/CMakeFiles/webcam_show.dir/src/webcam_show.cpp.o: webcam_test/CMakeFiles/webcam_show.dir/flags.make
webcam_test/CMakeFiles/webcam_show.dir/src/webcam_show.cpp.o: /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/src/webcam_test/src/webcam_show.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object webcam_test/CMakeFiles/webcam_show.dir/src/webcam_show.cpp.o"
	cd /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/build/webcam_test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/webcam_show.dir/src/webcam_show.cpp.o -c /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/src/webcam_test/src/webcam_show.cpp

webcam_test/CMakeFiles/webcam_show.dir/src/webcam_show.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webcam_show.dir/src/webcam_show.cpp.i"
	cd /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/build/webcam_test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/src/webcam_test/src/webcam_show.cpp > CMakeFiles/webcam_show.dir/src/webcam_show.cpp.i

webcam_test/CMakeFiles/webcam_show.dir/src/webcam_show.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webcam_show.dir/src/webcam_show.cpp.s"
	cd /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/build/webcam_test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/src/webcam_test/src/webcam_show.cpp -o CMakeFiles/webcam_show.dir/src/webcam_show.cpp.s

webcam_test/CMakeFiles/webcam_show.dir/src/webcam_show.cpp.o.requires:
.PHONY : webcam_test/CMakeFiles/webcam_show.dir/src/webcam_show.cpp.o.requires

webcam_test/CMakeFiles/webcam_show.dir/src/webcam_show.cpp.o.provides: webcam_test/CMakeFiles/webcam_show.dir/src/webcam_show.cpp.o.requires
	$(MAKE) -f webcam_test/CMakeFiles/webcam_show.dir/build.make webcam_test/CMakeFiles/webcam_show.dir/src/webcam_show.cpp.o.provides.build
.PHONY : webcam_test/CMakeFiles/webcam_show.dir/src/webcam_show.cpp.o.provides

webcam_test/CMakeFiles/webcam_show.dir/src/webcam_show.cpp.o.provides.build: webcam_test/CMakeFiles/webcam_show.dir/src/webcam_show.cpp.o

# Object files for target webcam_show
webcam_show_OBJECTS = \
"CMakeFiles/webcam_show.dir/src/webcam_show.cpp.o"

# External object files for target webcam_show
webcam_show_EXTERNAL_OBJECTS =

/home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/devel/lib/webcam_test/webcam_show: webcam_test/CMakeFiles/webcam_show.dir/src/webcam_show.cpp.o
/home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/devel/lib/webcam_test/webcam_show: webcam_test/CMakeFiles/webcam_show.dir/build.make
/home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/devel/lib/webcam_test/webcam_show: webcam_test/CMakeFiles/webcam_show.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/devel/lib/webcam_test/webcam_show"
	cd /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/build/webcam_test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/webcam_show.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
webcam_test/CMakeFiles/webcam_show.dir/build: /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/devel/lib/webcam_test/webcam_show
.PHONY : webcam_test/CMakeFiles/webcam_show.dir/build

webcam_test/CMakeFiles/webcam_show.dir/requires: webcam_test/CMakeFiles/webcam_show.dir/src/webcam_show.cpp.o.requires
.PHONY : webcam_test/CMakeFiles/webcam_show.dir/requires

webcam_test/CMakeFiles/webcam_show.dir/clean:
	cd /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/build/webcam_test && $(CMAKE_COMMAND) -P CMakeFiles/webcam_show.dir/cmake_clean.cmake
.PHONY : webcam_test/CMakeFiles/webcam_show.dir/clean

webcam_test/CMakeFiles/webcam_show.dir/depend:
	cd /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/src /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/src/webcam_test /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/build /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/build/webcam_test /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/build/webcam_test/CMakeFiles/webcam_show.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : webcam_test/CMakeFiles/webcam_show.dir/depend
