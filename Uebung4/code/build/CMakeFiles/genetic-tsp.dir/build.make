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
CMAKE_SOURCE_DIR = /home/erik/Documents/UNI/Pt_2/git/Pt2/Uebung4/code

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/erik/Documents/UNI/Pt_2/git/Pt2/Uebung4/code/build

# Include any dependencies generated for this target.
include CMakeFiles/genetic-tsp.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/genetic-tsp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/genetic-tsp.dir/flags.make

CMakeFiles/genetic-tsp.dir/src/genetic-tsp.cpp.o: CMakeFiles/genetic-tsp.dir/flags.make
CMakeFiles/genetic-tsp.dir/src/genetic-tsp.cpp.o: ../src/genetic-tsp.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/erik/Documents/UNI/Pt_2/git/Pt2/Uebung4/code/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/genetic-tsp.dir/src/genetic-tsp.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/genetic-tsp.dir/src/genetic-tsp.cpp.o -c /home/erik/Documents/UNI/Pt_2/git/Pt2/Uebung4/code/src/genetic-tsp.cpp

CMakeFiles/genetic-tsp.dir/src/genetic-tsp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/genetic-tsp.dir/src/genetic-tsp.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/erik/Documents/UNI/Pt_2/git/Pt2/Uebung4/code/src/genetic-tsp.cpp > CMakeFiles/genetic-tsp.dir/src/genetic-tsp.cpp.i

CMakeFiles/genetic-tsp.dir/src/genetic-tsp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/genetic-tsp.dir/src/genetic-tsp.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/erik/Documents/UNI/Pt_2/git/Pt2/Uebung4/code/src/genetic-tsp.cpp -o CMakeFiles/genetic-tsp.dir/src/genetic-tsp.cpp.s

CMakeFiles/genetic-tsp.dir/src/genetic-tsp.cpp.o.requires:
.PHONY : CMakeFiles/genetic-tsp.dir/src/genetic-tsp.cpp.o.requires

CMakeFiles/genetic-tsp.dir/src/genetic-tsp.cpp.o.provides: CMakeFiles/genetic-tsp.dir/src/genetic-tsp.cpp.o.requires
	$(MAKE) -f CMakeFiles/genetic-tsp.dir/build.make CMakeFiles/genetic-tsp.dir/src/genetic-tsp.cpp.o.provides.build
.PHONY : CMakeFiles/genetic-tsp.dir/src/genetic-tsp.cpp.o.provides

CMakeFiles/genetic-tsp.dir/src/genetic-tsp.cpp.o.provides.build: CMakeFiles/genetic-tsp.dir/src/genetic-tsp.cpp.o

# Object files for target genetic-tsp
genetic__tsp_OBJECTS = \
"CMakeFiles/genetic-tsp.dir/src/genetic-tsp.cpp.o"

# External object files for target genetic-tsp
genetic__tsp_EXTERNAL_OBJECTS =

genetic-tsp: CMakeFiles/genetic-tsp.dir/src/genetic-tsp.cpp.o
genetic-tsp: CMakeFiles/genetic-tsp.dir/build.make
genetic-tsp: CMakeFiles/genetic-tsp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable genetic-tsp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/genetic-tsp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/genetic-tsp.dir/build: genetic-tsp
.PHONY : CMakeFiles/genetic-tsp.dir/build

CMakeFiles/genetic-tsp.dir/requires: CMakeFiles/genetic-tsp.dir/src/genetic-tsp.cpp.o.requires
.PHONY : CMakeFiles/genetic-tsp.dir/requires

CMakeFiles/genetic-tsp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/genetic-tsp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/genetic-tsp.dir/clean

CMakeFiles/genetic-tsp.dir/depend:
	cd /home/erik/Documents/UNI/Pt_2/git/Pt2/Uebung4/code/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/erik/Documents/UNI/Pt_2/git/Pt2/Uebung4/code /home/erik/Documents/UNI/Pt_2/git/Pt2/Uebung4/code /home/erik/Documents/UNI/Pt_2/git/Pt2/Uebung4/code/build /home/erik/Documents/UNI/Pt_2/git/Pt2/Uebung4/code/build /home/erik/Documents/UNI/Pt_2/git/Pt2/Uebung4/code/build/CMakeFiles/genetic-tsp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/genetic-tsp.dir/depend
