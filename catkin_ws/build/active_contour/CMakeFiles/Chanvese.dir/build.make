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
include active_contour/CMakeFiles/Chanvese.dir/depend.make

# Include the progress variables for this target.
include active_contour/CMakeFiles/Chanvese.dir/progress.make

# Include the compile flags for this target's objects.
include active_contour/CMakeFiles/Chanvese.dir/flags.make

active_contour/CMakeFiles/Chanvese.dir/libs/chanvese/chanvese.c.o: active_contour/CMakeFiles/Chanvese.dir/flags.make
active_contour/CMakeFiles/Chanvese.dir/libs/chanvese/chanvese.c.o: /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/src/active_contour/libs/chanvese/chanvese.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object active_contour/CMakeFiles/Chanvese.dir/libs/chanvese/chanvese.c.o"
	cd /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/build/active_contour && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/Chanvese.dir/libs/chanvese/chanvese.c.o   -c /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/src/active_contour/libs/chanvese/chanvese.c

active_contour/CMakeFiles/Chanvese.dir/libs/chanvese/chanvese.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Chanvese.dir/libs/chanvese/chanvese.c.i"
	cd /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/build/active_contour && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/src/active_contour/libs/chanvese/chanvese.c > CMakeFiles/Chanvese.dir/libs/chanvese/chanvese.c.i

active_contour/CMakeFiles/Chanvese.dir/libs/chanvese/chanvese.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Chanvese.dir/libs/chanvese/chanvese.c.s"
	cd /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/build/active_contour && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/src/active_contour/libs/chanvese/chanvese.c -o CMakeFiles/Chanvese.dir/libs/chanvese/chanvese.c.s

active_contour/CMakeFiles/Chanvese.dir/libs/chanvese/chanvese.c.o.requires:
.PHONY : active_contour/CMakeFiles/Chanvese.dir/libs/chanvese/chanvese.c.o.requires

active_contour/CMakeFiles/Chanvese.dir/libs/chanvese/chanvese.c.o.provides: active_contour/CMakeFiles/Chanvese.dir/libs/chanvese/chanvese.c.o.requires
	$(MAKE) -f active_contour/CMakeFiles/Chanvese.dir/build.make active_contour/CMakeFiles/Chanvese.dir/libs/chanvese/chanvese.c.o.provides.build
.PHONY : active_contour/CMakeFiles/Chanvese.dir/libs/chanvese/chanvese.c.o.provides

active_contour/CMakeFiles/Chanvese.dir/libs/chanvese/chanvese.c.o.provides.build: active_contour/CMakeFiles/Chanvese.dir/libs/chanvese/chanvese.c.o

active_contour/CMakeFiles/Chanvese.dir/libs/chanvese/contour.c.o: active_contour/CMakeFiles/Chanvese.dir/flags.make
active_contour/CMakeFiles/Chanvese.dir/libs/chanvese/contour.c.o: /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/src/active_contour/libs/chanvese/contour.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object active_contour/CMakeFiles/Chanvese.dir/libs/chanvese/contour.c.o"
	cd /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/build/active_contour && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/Chanvese.dir/libs/chanvese/contour.c.o   -c /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/src/active_contour/libs/chanvese/contour.c

active_contour/CMakeFiles/Chanvese.dir/libs/chanvese/contour.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Chanvese.dir/libs/chanvese/contour.c.i"
	cd /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/build/active_contour && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/src/active_contour/libs/chanvese/contour.c > CMakeFiles/Chanvese.dir/libs/chanvese/contour.c.i

active_contour/CMakeFiles/Chanvese.dir/libs/chanvese/contour.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Chanvese.dir/libs/chanvese/contour.c.s"
	cd /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/build/active_contour && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/src/active_contour/libs/chanvese/contour.c -o CMakeFiles/Chanvese.dir/libs/chanvese/contour.c.s

active_contour/CMakeFiles/Chanvese.dir/libs/chanvese/contour.c.o.requires:
.PHONY : active_contour/CMakeFiles/Chanvese.dir/libs/chanvese/contour.c.o.requires

active_contour/CMakeFiles/Chanvese.dir/libs/chanvese/contour.c.o.provides: active_contour/CMakeFiles/Chanvese.dir/libs/chanvese/contour.c.o.requires
	$(MAKE) -f active_contour/CMakeFiles/Chanvese.dir/build.make active_contour/CMakeFiles/Chanvese.dir/libs/chanvese/contour.c.o.provides.build
.PHONY : active_contour/CMakeFiles/Chanvese.dir/libs/chanvese/contour.c.o.provides

active_contour/CMakeFiles/Chanvese.dir/libs/chanvese/contour.c.o.provides.build: active_contour/CMakeFiles/Chanvese.dir/libs/chanvese/contour.c.o

# Object files for target Chanvese
Chanvese_OBJECTS = \
"CMakeFiles/Chanvese.dir/libs/chanvese/chanvese.c.o" \
"CMakeFiles/Chanvese.dir/libs/chanvese/contour.c.o"

# External object files for target Chanvese
Chanvese_EXTERNAL_OBJECTS =

/home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/devel/lib/libChanvese.so: active_contour/CMakeFiles/Chanvese.dir/libs/chanvese/chanvese.c.o
/home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/devel/lib/libChanvese.so: active_contour/CMakeFiles/Chanvese.dir/libs/chanvese/contour.c.o
/home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/devel/lib/libChanvese.so: active_contour/CMakeFiles/Chanvese.dir/build.make
/home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/devel/lib/libChanvese.so: active_contour/CMakeFiles/Chanvese.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/devel/lib/libChanvese.so"
	cd /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/build/active_contour && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Chanvese.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
active_contour/CMakeFiles/Chanvese.dir/build: /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/devel/lib/libChanvese.so
.PHONY : active_contour/CMakeFiles/Chanvese.dir/build

active_contour/CMakeFiles/Chanvese.dir/requires: active_contour/CMakeFiles/Chanvese.dir/libs/chanvese/chanvese.c.o.requires
active_contour/CMakeFiles/Chanvese.dir/requires: active_contour/CMakeFiles/Chanvese.dir/libs/chanvese/contour.c.o.requires
.PHONY : active_contour/CMakeFiles/Chanvese.dir/requires

active_contour/CMakeFiles/Chanvese.dir/clean:
	cd /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/build/active_contour && $(CMAKE_COMMAND) -P CMakeFiles/Chanvese.dir/cmake_clean.cmake
.PHONY : active_contour/CMakeFiles/Chanvese.dir/clean

active_contour/CMakeFiles/Chanvese.dir/depend:
	cd /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/src /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/src/active_contour /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/build /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/build/active_contour /home/osboxes/Desktop/CR_project/Cognitive-Robotics-Project/catkin_ws/build/active_contour/CMakeFiles/Chanvese.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : active_contour/CMakeFiles/Chanvese.dir/depend

