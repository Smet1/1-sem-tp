# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/smet_k/Desktop/1_sem_cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/smet_k/Desktop/1_sem_cpp/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/1_sem_cpp.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/1_sem_cpp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/1_sem_cpp.dir/flags.make

CMakeFiles/1_sem_cpp.dir/project/src/main.cpp.o: CMakeFiles/1_sem_cpp.dir/flags.make
CMakeFiles/1_sem_cpp.dir/project/src/main.cpp.o: ../project/src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/smet_k/Desktop/1_sem_cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/1_sem_cpp.dir/project/src/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/1_sem_cpp.dir/project/src/main.cpp.o -c /Users/smet_k/Desktop/1_sem_cpp/project/src/main.cpp

CMakeFiles/1_sem_cpp.dir/project/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/1_sem_cpp.dir/project/src/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/smet_k/Desktop/1_sem_cpp/project/src/main.cpp > CMakeFiles/1_sem_cpp.dir/project/src/main.cpp.i

CMakeFiles/1_sem_cpp.dir/project/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/1_sem_cpp.dir/project/src/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/smet_k/Desktop/1_sem_cpp/project/src/main.cpp -o CMakeFiles/1_sem_cpp.dir/project/src/main.cpp.s

# Object files for target 1_sem_cpp
1_sem_cpp_OBJECTS = \
"CMakeFiles/1_sem_cpp.dir/project/src/main.cpp.o"

# External object files for target 1_sem_cpp
1_sem_cpp_EXTERNAL_OBJECTS =

1_sem_cpp: CMakeFiles/1_sem_cpp.dir/project/src/main.cpp.o
1_sem_cpp: CMakeFiles/1_sem_cpp.dir/build.make
1_sem_cpp: CMakeFiles/1_sem_cpp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/smet_k/Desktop/1_sem_cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 1_sem_cpp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/1_sem_cpp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/1_sem_cpp.dir/build: 1_sem_cpp

.PHONY : CMakeFiles/1_sem_cpp.dir/build

CMakeFiles/1_sem_cpp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/1_sem_cpp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/1_sem_cpp.dir/clean

CMakeFiles/1_sem_cpp.dir/depend:
	cd /Users/smet_k/Desktop/1_sem_cpp/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/smet_k/Desktop/1_sem_cpp /Users/smet_k/Desktop/1_sem_cpp /Users/smet_k/Desktop/1_sem_cpp/cmake-build-debug /Users/smet_k/Desktop/1_sem_cpp/cmake-build-debug /Users/smet_k/Desktop/1_sem_cpp/cmake-build-debug/CMakeFiles/1_sem_cpp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/1_sem_cpp.dir/depend

