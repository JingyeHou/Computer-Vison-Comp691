# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/houjingye/CLionProjects/Computer_vision1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/houjingye/CLionProjects/Computer_vision1/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Opencv_Test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Opencv_Test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Opencv_Test.dir/flags.make

CMakeFiles/Opencv_Test.dir/main.cpp.o: CMakeFiles/Opencv_Test.dir/flags.make
CMakeFiles/Opencv_Test.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/houjingye/CLionProjects/Computer_vision1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Opencv_Test.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Opencv_Test.dir/main.cpp.o -c /Users/houjingye/CLionProjects/Computer_vision1/main.cpp

CMakeFiles/Opencv_Test.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Opencv_Test.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/houjingye/CLionProjects/Computer_vision1/main.cpp > CMakeFiles/Opencv_Test.dir/main.cpp.i

CMakeFiles/Opencv_Test.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Opencv_Test.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/houjingye/CLionProjects/Computer_vision1/main.cpp -o CMakeFiles/Opencv_Test.dir/main.cpp.s

CMakeFiles/Opencv_Test.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/Opencv_Test.dir/main.cpp.o.requires

CMakeFiles/Opencv_Test.dir/main.cpp.o.provides: CMakeFiles/Opencv_Test.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Opencv_Test.dir/build.make CMakeFiles/Opencv_Test.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/Opencv_Test.dir/main.cpp.o.provides

CMakeFiles/Opencv_Test.dir/main.cpp.o.provides.build: CMakeFiles/Opencv_Test.dir/main.cpp.o


# Object files for target Opencv_Test
Opencv_Test_OBJECTS = \
"CMakeFiles/Opencv_Test.dir/main.cpp.o"

# External object files for target Opencv_Test
Opencv_Test_EXTERNAL_OBJECTS =

Opencv_Test: CMakeFiles/Opencv_Test.dir/main.cpp.o
Opencv_Test: CMakeFiles/Opencv_Test.dir/build.make
Opencv_Test: /usr/local/lib/libopencv_shape.3.2.0.dylib
Opencv_Test: /usr/local/lib/libopencv_stitching.3.2.0.dylib
Opencv_Test: /usr/local/lib/libopencv_superres.3.2.0.dylib
Opencv_Test: /usr/local/lib/libopencv_videostab.3.2.0.dylib
Opencv_Test: /usr/local/lib/libopencv_objdetect.3.2.0.dylib
Opencv_Test: /usr/local/lib/libopencv_calib3d.3.2.0.dylib
Opencv_Test: /usr/local/lib/libopencv_features2d.3.2.0.dylib
Opencv_Test: /usr/local/lib/libopencv_flann.3.2.0.dylib
Opencv_Test: /usr/local/lib/libopencv_highgui.3.2.0.dylib
Opencv_Test: /usr/local/lib/libopencv_ml.3.2.0.dylib
Opencv_Test: /usr/local/lib/libopencv_photo.3.2.0.dylib
Opencv_Test: /usr/local/lib/libopencv_video.3.2.0.dylib
Opencv_Test: /usr/local/lib/libopencv_videoio.3.2.0.dylib
Opencv_Test: /usr/local/lib/libopencv_imgcodecs.3.2.0.dylib
Opencv_Test: /usr/local/lib/libopencv_imgproc.3.2.0.dylib
Opencv_Test: /usr/local/lib/libopencv_core.3.2.0.dylib
Opencv_Test: CMakeFiles/Opencv_Test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/houjingye/CLionProjects/Computer_vision1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Opencv_Test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Opencv_Test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Opencv_Test.dir/build: Opencv_Test

.PHONY : CMakeFiles/Opencv_Test.dir/build

CMakeFiles/Opencv_Test.dir/requires: CMakeFiles/Opencv_Test.dir/main.cpp.o.requires

.PHONY : CMakeFiles/Opencv_Test.dir/requires

CMakeFiles/Opencv_Test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Opencv_Test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Opencv_Test.dir/clean

CMakeFiles/Opencv_Test.dir/depend:
	cd /Users/houjingye/CLionProjects/Computer_vision1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/houjingye/CLionProjects/Computer_vision1 /Users/houjingye/CLionProjects/Computer_vision1 /Users/houjingye/CLionProjects/Computer_vision1/cmake-build-debug /Users/houjingye/CLionProjects/Computer_vision1/cmake-build-debug /Users/houjingye/CLionProjects/Computer_vision1/cmake-build-debug/CMakeFiles/Opencv_Test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Opencv_Test.dir/depend

