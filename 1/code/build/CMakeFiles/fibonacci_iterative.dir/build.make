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
CMAKE_SOURCE_DIR = /home/erik/Documents/UNI/Pt_2/Uebungen/1/code

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/erik/Documents/UNI/Pt_2/Uebungen/1/code/build

# Include any dependencies generated for this target.
include CMakeFiles/fibonacci_iterative.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/fibonacci_iterative.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/fibonacci_iterative.dir/flags.make

CMakeFiles/fibonacci_iterative.dir/src/fibonacci_iterative.cpp.o: CMakeFiles/fibonacci_iterative.dir/flags.make
CMakeFiles/fibonacci_iterative.dir/src/fibonacci_iterative.cpp.o: ../src/fibonacci_iterative.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/erik/Documents/UNI/Pt_2/Uebungen/1/code/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/fibonacci_iterative.dir/src/fibonacci_iterative.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/fibonacci_iterative.dir/src/fibonacci_iterative.cpp.o -c /home/erik/Documents/UNI/Pt_2/Uebungen/1/code/src/fibonacci_iterative.cpp

CMakeFiles/fibonacci_iterative.dir/src/fibonacci_iterative.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fibonacci_iterative.dir/src/fibonacci_iterative.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/erik/Documents/UNI/Pt_2/Uebungen/1/code/src/fibonacci_iterative.cpp > CMakeFiles/fibonacci_iterative.dir/src/fibonacci_iterative.cpp.i

CMakeFiles/fibonacci_iterative.dir/src/fibonacci_iterative.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fibonacci_iterative.dir/src/fibonacci_iterative.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/erik/Documents/UNI/Pt_2/Uebungen/1/code/src/fibonacci_iterative.cpp -o CMakeFiles/fibonacci_iterative.dir/src/fibonacci_iterative.cpp.s

CMakeFiles/fibonacci_iterative.dir/src/fibonacci_iterative.cpp.o.requires:
.PHONY : CMakeFiles/fibonacci_iterative.dir/src/fibonacci_iterative.cpp.o.requires

CMakeFiles/fibonacci_iterative.dir/src/fibonacci_iterative.cpp.o.provides: CMakeFiles/fibonacci_iterative.dir/src/fibonacci_iterative.cpp.o.requires
	$(MAKE) -f CMakeFiles/fibonacci_iterative.dir/build.make CMakeFiles/fibonacci_iterative.dir/src/fibonacci_iterative.cpp.o.provides.build
.PHONY : CMakeFiles/fibonacci_iterative.dir/src/fibonacci_iterative.cpp.o.provides

CMakeFiles/fibonacci_iterative.dir/src/fibonacci_iterative.cpp.o.provides.build: CMakeFiles/fibonacci_iterative.dir/src/fibonacci_iterative.cpp.o

# Object files for target fibonacci_iterative
fibonacci_iterative_OBJECTS = \
"CMakeFiles/fibonacci_iterative.dir/src/fibonacci_iterative.cpp.o"

# External object files for target fibonacci_iterative
fibonacci_iterative_EXTERNAL_OBJECTS =

fibonacci_iterative: CMakeFiles/fibonacci_iterative.dir/src/fibonacci_iterative.cpp.o
fibonacci_iterative: CMakeFiles/fibonacci_iterative.dir/build.make
fibonacci_iterative: CMakeFiles/fibonacci_iterative.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable fibonacci_iterative"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/fibonacci_iterative.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/fibonacci_iterative.dir/build: fibonacci_iterative
.PHONY : CMakeFiles/fibonacci_iterative.dir/build

CMakeFiles/fibonacci_iterative.dir/requires: CMakeFiles/fibonacci_iterative.dir/src/fibonacci_iterative.cpp.o.requires
.PHONY : CMakeFiles/fibonacci_iterative.dir/requires

CMakeFiles/fibonacci_iterative.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/fibonacci_iterative.dir/cmake_clean.cmake
.PHONY : CMakeFiles/fibonacci_iterative.dir/clean

CMakeFiles/fibonacci_iterative.dir/depend:
	cd /home/erik/Documents/UNI/Pt_2/Uebungen/1/code/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/erik/Documents/UNI/Pt_2/Uebungen/1/code /home/erik/Documents/UNI/Pt_2/Uebungen/1/code /home/erik/Documents/UNI/Pt_2/Uebungen/1/code/build /home/erik/Documents/UNI/Pt_2/Uebungen/1/code/build /home/erik/Documents/UNI/Pt_2/Uebungen/1/code/build/CMakeFiles/fibonacci_iterative.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/fibonacci_iterative.dir/depend

