# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/airat/Documents/21_school_projects/3D_Viewer_2_0/CPP4_3DViewer_v2.0-3-master/src/CMake/3D_Viewer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/airat/Documents/21_school_projects/3D_Viewer_2_0/CPP4_3DViewer_v2.0-3-master/src/CMake/3D_Viewer

# Utility rule file for gifimage_autogen.

# Include any custom commands dependencies for this target.
include QtGifImage-master/src/CMakeFiles/gifimage_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include QtGifImage-master/src/CMakeFiles/gifimage_autogen.dir/progress.make

QtGifImage-master/src/CMakeFiles/gifimage_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/airat/Documents/21_school_projects/3D_Viewer_2_0/CPP4_3DViewer_v2.0-3-master/src/CMake/3D_Viewer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target gifimage"
	cd /home/airat/Documents/21_school_projects/3D_Viewer_2_0/CPP4_3DViewer_v2.0-3-master/src/CMake/3D_Viewer/QtGifImage-master/src && /usr/bin/cmake -E cmake_autogen /home/airat/Documents/21_school_projects/3D_Viewer_2_0/CPP4_3DViewer_v2.0-3-master/src/CMake/3D_Viewer/QtGifImage-master/src/CMakeFiles/gifimage_autogen.dir/AutogenInfo.json Release

gifimage_autogen: QtGifImage-master/src/CMakeFiles/gifimage_autogen
gifimage_autogen: QtGifImage-master/src/CMakeFiles/gifimage_autogen.dir/build.make
.PHONY : gifimage_autogen

# Rule to build all files generated by this target.
QtGifImage-master/src/CMakeFiles/gifimage_autogen.dir/build: gifimage_autogen
.PHONY : QtGifImage-master/src/CMakeFiles/gifimage_autogen.dir/build

QtGifImage-master/src/CMakeFiles/gifimage_autogen.dir/clean:
	cd /home/airat/Documents/21_school_projects/3D_Viewer_2_0/CPP4_3DViewer_v2.0-3-master/src/CMake/3D_Viewer/QtGifImage-master/src && $(CMAKE_COMMAND) -P CMakeFiles/gifimage_autogen.dir/cmake_clean.cmake
.PHONY : QtGifImage-master/src/CMakeFiles/gifimage_autogen.dir/clean

QtGifImage-master/src/CMakeFiles/gifimage_autogen.dir/depend:
	cd /home/airat/Documents/21_school_projects/3D_Viewer_2_0/CPP4_3DViewer_v2.0-3-master/src/CMake/3D_Viewer && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/airat/Documents/21_school_projects/3D_Viewer_2_0/CPP4_3DViewer_v2.0-3-master/src/CMake/3D_Viewer /home/airat/Documents/21_school_projects/3D_Viewer_2_0/CPP4_3DViewer_v2.0-3-master/src/CMake/3D_Viewer/QtGifImage-master/src /home/airat/Documents/21_school_projects/3D_Viewer_2_0/CPP4_3DViewer_v2.0-3-master/src/CMake/3D_Viewer /home/airat/Documents/21_school_projects/3D_Viewer_2_0/CPP4_3DViewer_v2.0-3-master/src/CMake/3D_Viewer/QtGifImage-master/src /home/airat/Documents/21_school_projects/3D_Viewer_2_0/CPP4_3DViewer_v2.0-3-master/src/CMake/3D_Viewer/QtGifImage-master/src/CMakeFiles/gifimage_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : QtGifImage-master/src/CMakeFiles/gifimage_autogen.dir/depend
