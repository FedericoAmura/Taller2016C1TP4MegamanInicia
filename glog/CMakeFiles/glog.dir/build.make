# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/marcos/ClionProjects/Megaman/glog

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/marcos/ClionProjects/Megaman/glog

# Include any dependencies generated for this target.
include CMakeFiles/glog.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/glog.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/glog.dir/flags.make

CMakeFiles/glog.dir/src/demangle.cc.o: CMakeFiles/glog.dir/flags.make
CMakeFiles/glog.dir/src/demangle.cc.o: src/demangle.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marcos/ClionProjects/Megaman/glog/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/glog.dir/src/demangle.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/glog.dir/src/demangle.cc.o -c /home/marcos/ClionProjects/Megaman/glog/src/demangle.cc

CMakeFiles/glog.dir/src/demangle.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/glog.dir/src/demangle.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marcos/ClionProjects/Megaman/glog/src/demangle.cc > CMakeFiles/glog.dir/src/demangle.cc.i

CMakeFiles/glog.dir/src/demangle.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/glog.dir/src/demangle.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marcos/ClionProjects/Megaman/glog/src/demangle.cc -o CMakeFiles/glog.dir/src/demangle.cc.s

CMakeFiles/glog.dir/src/demangle.cc.o.requires:

.PHONY : CMakeFiles/glog.dir/src/demangle.cc.o.requires

CMakeFiles/glog.dir/src/demangle.cc.o.provides: CMakeFiles/glog.dir/src/demangle.cc.o.requires
	$(MAKE) -f CMakeFiles/glog.dir/build.make CMakeFiles/glog.dir/src/demangle.cc.o.provides.build
.PHONY : CMakeFiles/glog.dir/src/demangle.cc.o.provides

CMakeFiles/glog.dir/src/demangle.cc.o.provides.build: CMakeFiles/glog.dir/src/demangle.cc.o


CMakeFiles/glog.dir/src/logging.cc.o: CMakeFiles/glog.dir/flags.make
CMakeFiles/glog.dir/src/logging.cc.o: src/logging.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marcos/ClionProjects/Megaman/glog/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/glog.dir/src/logging.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/glog.dir/src/logging.cc.o -c /home/marcos/ClionProjects/Megaman/glog/src/logging.cc

CMakeFiles/glog.dir/src/logging.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/glog.dir/src/logging.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marcos/ClionProjects/Megaman/glog/src/logging.cc > CMakeFiles/glog.dir/src/logging.cc.i

CMakeFiles/glog.dir/src/logging.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/glog.dir/src/logging.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marcos/ClionProjects/Megaman/glog/src/logging.cc -o CMakeFiles/glog.dir/src/logging.cc.s

CMakeFiles/glog.dir/src/logging.cc.o.requires:

.PHONY : CMakeFiles/glog.dir/src/logging.cc.o.requires

CMakeFiles/glog.dir/src/logging.cc.o.provides: CMakeFiles/glog.dir/src/logging.cc.o.requires
	$(MAKE) -f CMakeFiles/glog.dir/build.make CMakeFiles/glog.dir/src/logging.cc.o.provides.build
.PHONY : CMakeFiles/glog.dir/src/logging.cc.o.provides

CMakeFiles/glog.dir/src/logging.cc.o.provides.build: CMakeFiles/glog.dir/src/logging.cc.o


CMakeFiles/glog.dir/src/raw_logging.cc.o: CMakeFiles/glog.dir/flags.make
CMakeFiles/glog.dir/src/raw_logging.cc.o: src/raw_logging.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marcos/ClionProjects/Megaman/glog/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/glog.dir/src/raw_logging.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/glog.dir/src/raw_logging.cc.o -c /home/marcos/ClionProjects/Megaman/glog/src/raw_logging.cc

CMakeFiles/glog.dir/src/raw_logging.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/glog.dir/src/raw_logging.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marcos/ClionProjects/Megaman/glog/src/raw_logging.cc > CMakeFiles/glog.dir/src/raw_logging.cc.i

CMakeFiles/glog.dir/src/raw_logging.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/glog.dir/src/raw_logging.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marcos/ClionProjects/Megaman/glog/src/raw_logging.cc -o CMakeFiles/glog.dir/src/raw_logging.cc.s

CMakeFiles/glog.dir/src/raw_logging.cc.o.requires:

.PHONY : CMakeFiles/glog.dir/src/raw_logging.cc.o.requires

CMakeFiles/glog.dir/src/raw_logging.cc.o.provides: CMakeFiles/glog.dir/src/raw_logging.cc.o.requires
	$(MAKE) -f CMakeFiles/glog.dir/build.make CMakeFiles/glog.dir/src/raw_logging.cc.o.provides.build
.PHONY : CMakeFiles/glog.dir/src/raw_logging.cc.o.provides

CMakeFiles/glog.dir/src/raw_logging.cc.o.provides.build: CMakeFiles/glog.dir/src/raw_logging.cc.o


CMakeFiles/glog.dir/src/symbolize.cc.o: CMakeFiles/glog.dir/flags.make
CMakeFiles/glog.dir/src/symbolize.cc.o: src/symbolize.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marcos/ClionProjects/Megaman/glog/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/glog.dir/src/symbolize.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/glog.dir/src/symbolize.cc.o -c /home/marcos/ClionProjects/Megaman/glog/src/symbolize.cc

CMakeFiles/glog.dir/src/symbolize.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/glog.dir/src/symbolize.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marcos/ClionProjects/Megaman/glog/src/symbolize.cc > CMakeFiles/glog.dir/src/symbolize.cc.i

CMakeFiles/glog.dir/src/symbolize.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/glog.dir/src/symbolize.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marcos/ClionProjects/Megaman/glog/src/symbolize.cc -o CMakeFiles/glog.dir/src/symbolize.cc.s

CMakeFiles/glog.dir/src/symbolize.cc.o.requires:

.PHONY : CMakeFiles/glog.dir/src/symbolize.cc.o.requires

CMakeFiles/glog.dir/src/symbolize.cc.o.provides: CMakeFiles/glog.dir/src/symbolize.cc.o.requires
	$(MAKE) -f CMakeFiles/glog.dir/build.make CMakeFiles/glog.dir/src/symbolize.cc.o.provides.build
.PHONY : CMakeFiles/glog.dir/src/symbolize.cc.o.provides

CMakeFiles/glog.dir/src/symbolize.cc.o.provides.build: CMakeFiles/glog.dir/src/symbolize.cc.o


CMakeFiles/glog.dir/src/utilities.cc.o: CMakeFiles/glog.dir/flags.make
CMakeFiles/glog.dir/src/utilities.cc.o: src/utilities.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marcos/ClionProjects/Megaman/glog/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/glog.dir/src/utilities.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/glog.dir/src/utilities.cc.o -c /home/marcos/ClionProjects/Megaman/glog/src/utilities.cc

CMakeFiles/glog.dir/src/utilities.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/glog.dir/src/utilities.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marcos/ClionProjects/Megaman/glog/src/utilities.cc > CMakeFiles/glog.dir/src/utilities.cc.i

CMakeFiles/glog.dir/src/utilities.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/glog.dir/src/utilities.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marcos/ClionProjects/Megaman/glog/src/utilities.cc -o CMakeFiles/glog.dir/src/utilities.cc.s

CMakeFiles/glog.dir/src/utilities.cc.o.requires:

.PHONY : CMakeFiles/glog.dir/src/utilities.cc.o.requires

CMakeFiles/glog.dir/src/utilities.cc.o.provides: CMakeFiles/glog.dir/src/utilities.cc.o.requires
	$(MAKE) -f CMakeFiles/glog.dir/build.make CMakeFiles/glog.dir/src/utilities.cc.o.provides.build
.PHONY : CMakeFiles/glog.dir/src/utilities.cc.o.provides

CMakeFiles/glog.dir/src/utilities.cc.o.provides.build: CMakeFiles/glog.dir/src/utilities.cc.o


CMakeFiles/glog.dir/src/vlog_is_on.cc.o: CMakeFiles/glog.dir/flags.make
CMakeFiles/glog.dir/src/vlog_is_on.cc.o: src/vlog_is_on.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marcos/ClionProjects/Megaman/glog/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/glog.dir/src/vlog_is_on.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/glog.dir/src/vlog_is_on.cc.o -c /home/marcos/ClionProjects/Megaman/glog/src/vlog_is_on.cc

CMakeFiles/glog.dir/src/vlog_is_on.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/glog.dir/src/vlog_is_on.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marcos/ClionProjects/Megaman/glog/src/vlog_is_on.cc > CMakeFiles/glog.dir/src/vlog_is_on.cc.i

CMakeFiles/glog.dir/src/vlog_is_on.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/glog.dir/src/vlog_is_on.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marcos/ClionProjects/Megaman/glog/src/vlog_is_on.cc -o CMakeFiles/glog.dir/src/vlog_is_on.cc.s

CMakeFiles/glog.dir/src/vlog_is_on.cc.o.requires:

.PHONY : CMakeFiles/glog.dir/src/vlog_is_on.cc.o.requires

CMakeFiles/glog.dir/src/vlog_is_on.cc.o.provides: CMakeFiles/glog.dir/src/vlog_is_on.cc.o.requires
	$(MAKE) -f CMakeFiles/glog.dir/build.make CMakeFiles/glog.dir/src/vlog_is_on.cc.o.provides.build
.PHONY : CMakeFiles/glog.dir/src/vlog_is_on.cc.o.provides

CMakeFiles/glog.dir/src/vlog_is_on.cc.o.provides.build: CMakeFiles/glog.dir/src/vlog_is_on.cc.o


CMakeFiles/glog.dir/src/signalhandler.cc.o: CMakeFiles/glog.dir/flags.make
CMakeFiles/glog.dir/src/signalhandler.cc.o: src/signalhandler.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marcos/ClionProjects/Megaman/glog/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/glog.dir/src/signalhandler.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/glog.dir/src/signalhandler.cc.o -c /home/marcos/ClionProjects/Megaman/glog/src/signalhandler.cc

CMakeFiles/glog.dir/src/signalhandler.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/glog.dir/src/signalhandler.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marcos/ClionProjects/Megaman/glog/src/signalhandler.cc > CMakeFiles/glog.dir/src/signalhandler.cc.i

CMakeFiles/glog.dir/src/signalhandler.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/glog.dir/src/signalhandler.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marcos/ClionProjects/Megaman/glog/src/signalhandler.cc -o CMakeFiles/glog.dir/src/signalhandler.cc.s

CMakeFiles/glog.dir/src/signalhandler.cc.o.requires:

.PHONY : CMakeFiles/glog.dir/src/signalhandler.cc.o.requires

CMakeFiles/glog.dir/src/signalhandler.cc.o.provides: CMakeFiles/glog.dir/src/signalhandler.cc.o.requires
	$(MAKE) -f CMakeFiles/glog.dir/build.make CMakeFiles/glog.dir/src/signalhandler.cc.o.provides.build
.PHONY : CMakeFiles/glog.dir/src/signalhandler.cc.o.provides

CMakeFiles/glog.dir/src/signalhandler.cc.o.provides.build: CMakeFiles/glog.dir/src/signalhandler.cc.o


# Object files for target glog
glog_OBJECTS = \
"CMakeFiles/glog.dir/src/demangle.cc.o" \
"CMakeFiles/glog.dir/src/logging.cc.o" \
"CMakeFiles/glog.dir/src/raw_logging.cc.o" \
"CMakeFiles/glog.dir/src/symbolize.cc.o" \
"CMakeFiles/glog.dir/src/utilities.cc.o" \
"CMakeFiles/glog.dir/src/vlog_is_on.cc.o" \
"CMakeFiles/glog.dir/src/signalhandler.cc.o"

# External object files for target glog
glog_EXTERNAL_OBJECTS =

libglog.a: CMakeFiles/glog.dir/src/demangle.cc.o
libglog.a: CMakeFiles/glog.dir/src/logging.cc.o
libglog.a: CMakeFiles/glog.dir/src/raw_logging.cc.o
libglog.a: CMakeFiles/glog.dir/src/symbolize.cc.o
libglog.a: CMakeFiles/glog.dir/src/utilities.cc.o
libglog.a: CMakeFiles/glog.dir/src/vlog_is_on.cc.o
libglog.a: CMakeFiles/glog.dir/src/signalhandler.cc.o
libglog.a: CMakeFiles/glog.dir/build.make
libglog.a: CMakeFiles/glog.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/marcos/ClionProjects/Megaman/glog/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX static library libglog.a"
	$(CMAKE_COMMAND) -P CMakeFiles/glog.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/glog.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/glog.dir/build: libglog.a

.PHONY : CMakeFiles/glog.dir/build

CMakeFiles/glog.dir/requires: CMakeFiles/glog.dir/src/demangle.cc.o.requires
CMakeFiles/glog.dir/requires: CMakeFiles/glog.dir/src/logging.cc.o.requires
CMakeFiles/glog.dir/requires: CMakeFiles/glog.dir/src/raw_logging.cc.o.requires
CMakeFiles/glog.dir/requires: CMakeFiles/glog.dir/src/symbolize.cc.o.requires
CMakeFiles/glog.dir/requires: CMakeFiles/glog.dir/src/utilities.cc.o.requires
CMakeFiles/glog.dir/requires: CMakeFiles/glog.dir/src/vlog_is_on.cc.o.requires
CMakeFiles/glog.dir/requires: CMakeFiles/glog.dir/src/signalhandler.cc.o.requires

.PHONY : CMakeFiles/glog.dir/requires

CMakeFiles/glog.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/glog.dir/cmake_clean.cmake
.PHONY : CMakeFiles/glog.dir/clean

CMakeFiles/glog.dir/depend:
	cd /home/marcos/ClionProjects/Megaman/glog && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/marcos/ClionProjects/Megaman/glog /home/marcos/ClionProjects/Megaman/glog /home/marcos/ClionProjects/Megaman/glog /home/marcos/ClionProjects/Megaman/glog /home/marcos/ClionProjects/Megaman/glog/CMakeFiles/glog.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/glog.dir/depend

