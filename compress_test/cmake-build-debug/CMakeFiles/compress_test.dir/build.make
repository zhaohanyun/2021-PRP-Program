# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/cmake-3.20.0/bin/cmake

# The command to remove a file.
RM = /opt/cmake-3.20.0/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zhaohanyun/Desktop/git_cv/compress_test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zhaohanyun/Desktop/git_cv/compress_test/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/compress_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/compress_test.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/compress_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/compress_test.dir/flags.make

CMakeFiles/compress_test.dir/main.cpp.o: CMakeFiles/compress_test.dir/flags.make
CMakeFiles/compress_test.dir/main.cpp.o: ../main.cpp
CMakeFiles/compress_test.dir/main.cpp.o: CMakeFiles/compress_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhaohanyun/Desktop/git_cv/compress_test/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/compress_test.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/compress_test.dir/main.cpp.o -MF CMakeFiles/compress_test.dir/main.cpp.o.d -o CMakeFiles/compress_test.dir/main.cpp.o -c /home/zhaohanyun/Desktop/git_cv/compress_test/main.cpp

CMakeFiles/compress_test.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compress_test.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhaohanyun/Desktop/git_cv/compress_test/main.cpp > CMakeFiles/compress_test.dir/main.cpp.i

CMakeFiles/compress_test.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compress_test.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhaohanyun/Desktop/git_cv/compress_test/main.cpp -o CMakeFiles/compress_test.dir/main.cpp.s

# Object files for target compress_test
compress_test_OBJECTS = \
"CMakeFiles/compress_test.dir/main.cpp.o"

# External object files for target compress_test
compress_test_EXTERNAL_OBJECTS =

compress_test: CMakeFiles/compress_test.dir/main.cpp.o
compress_test: CMakeFiles/compress_test.dir/build.make
compress_test: CMakeFiles/compress_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zhaohanyun/Desktop/git_cv/compress_test/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable compress_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/compress_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/compress_test.dir/build: compress_test
.PHONY : CMakeFiles/compress_test.dir/build

CMakeFiles/compress_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/compress_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/compress_test.dir/clean

CMakeFiles/compress_test.dir/depend:
	cd /home/zhaohanyun/Desktop/git_cv/compress_test/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zhaohanyun/Desktop/git_cv/compress_test /home/zhaohanyun/Desktop/git_cv/compress_test /home/zhaohanyun/Desktop/git_cv/compress_test/cmake-build-debug /home/zhaohanyun/Desktop/git_cv/compress_test/cmake-build-debug /home/zhaohanyun/Desktop/git_cv/compress_test/cmake-build-debug/CMakeFiles/compress_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/compress_test.dir/depend

