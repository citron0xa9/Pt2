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
CMAKE_SOURCE_DIR = /home/erik/Documents/UNI/Pt_2/git/Pt2/Uebung3/code

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/erik/Documents/UNI/Pt_2/git/Pt2/Uebung3/code/build

# Include any dependencies generated for this target.
include CMakeFiles/emailcheck.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/emailcheck.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/emailcheck.dir/flags.make

CMakeFiles/emailcheck.dir/src/emailcheck.cpp.o: CMakeFiles/emailcheck.dir/flags.make
CMakeFiles/emailcheck.dir/src/emailcheck.cpp.o: ../src/emailcheck.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/erik/Documents/UNI/Pt_2/git/Pt2/Uebung3/code/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/emailcheck.dir/src/emailcheck.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/emailcheck.dir/src/emailcheck.cpp.o -c /home/erik/Documents/UNI/Pt_2/git/Pt2/Uebung3/code/src/emailcheck.cpp

CMakeFiles/emailcheck.dir/src/emailcheck.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/emailcheck.dir/src/emailcheck.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/erik/Documents/UNI/Pt_2/git/Pt2/Uebung3/code/src/emailcheck.cpp > CMakeFiles/emailcheck.dir/src/emailcheck.cpp.i

CMakeFiles/emailcheck.dir/src/emailcheck.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/emailcheck.dir/src/emailcheck.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/erik/Documents/UNI/Pt_2/git/Pt2/Uebung3/code/src/emailcheck.cpp -o CMakeFiles/emailcheck.dir/src/emailcheck.cpp.s

CMakeFiles/emailcheck.dir/src/emailcheck.cpp.o.requires:
.PHONY : CMakeFiles/emailcheck.dir/src/emailcheck.cpp.o.requires

CMakeFiles/emailcheck.dir/src/emailcheck.cpp.o.provides: CMakeFiles/emailcheck.dir/src/emailcheck.cpp.o.requires
	$(MAKE) -f CMakeFiles/emailcheck.dir/build.make CMakeFiles/emailcheck.dir/src/emailcheck.cpp.o.provides.build
.PHONY : CMakeFiles/emailcheck.dir/src/emailcheck.cpp.o.provides

CMakeFiles/emailcheck.dir/src/emailcheck.cpp.o.provides.build: CMakeFiles/emailcheck.dir/src/emailcheck.cpp.o

# Object files for target emailcheck
emailcheck_OBJECTS = \
"CMakeFiles/emailcheck.dir/src/emailcheck.cpp.o"

# External object files for target emailcheck
emailcheck_EXTERNAL_OBJECTS =

emailcheck: CMakeFiles/emailcheck.dir/src/emailcheck.cpp.o
emailcheck: CMakeFiles/emailcheck.dir/build.make
emailcheck: CMakeFiles/emailcheck.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable emailcheck"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/emailcheck.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/emailcheck.dir/build: emailcheck
.PHONY : CMakeFiles/emailcheck.dir/build

CMakeFiles/emailcheck.dir/requires: CMakeFiles/emailcheck.dir/src/emailcheck.cpp.o.requires
.PHONY : CMakeFiles/emailcheck.dir/requires

CMakeFiles/emailcheck.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/emailcheck.dir/cmake_clean.cmake
.PHONY : CMakeFiles/emailcheck.dir/clean

CMakeFiles/emailcheck.dir/depend:
	cd /home/erik/Documents/UNI/Pt_2/git/Pt2/Uebung3/code/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/erik/Documents/UNI/Pt_2/git/Pt2/Uebung3/code /home/erik/Documents/UNI/Pt_2/git/Pt2/Uebung3/code /home/erik/Documents/UNI/Pt_2/git/Pt2/Uebung3/code/build /home/erik/Documents/UNI/Pt_2/git/Pt2/Uebung3/code/build /home/erik/Documents/UNI/Pt_2/git/Pt2/Uebung3/code/build/CMakeFiles/emailcheck.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/emailcheck.dir/depend

