# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /snap/cmake/73/bin/cmake

# The command to remove a file.
RM = /snap/cmake/73/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/davhor/Dropbox/CodeBase/Arduino/Pump_Control/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/davhor/Dropbox/CodeBase/Arduino/Pump_Control/build

# Include any dependencies generated for this target.
include CMakeFiles/Arduino_PS.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Arduino_PS.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Arduino_PS.dir/flags.make

CMakeFiles/Arduino_PS.dir/Arduino_PS.cpp.o: CMakeFiles/Arduino_PS.dir/flags.make
CMakeFiles/Arduino_PS.dir/Arduino_PS.cpp.o: /home/davhor/Dropbox/CodeBase/Arduino/Pump_Control/src/Arduino_PS.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/davhor/Dropbox/CodeBase/Arduino/Pump_Control/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Arduino_PS.dir/Arduino_PS.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Arduino_PS.dir/Arduino_PS.cpp.o -c /home/davhor/Dropbox/CodeBase/Arduino/Pump_Control/src/Arduino_PS.cpp

CMakeFiles/Arduino_PS.dir/Arduino_PS.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Arduino_PS.dir/Arduino_PS.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/davhor/Dropbox/CodeBase/Arduino/Pump_Control/src/Arduino_PS.cpp > CMakeFiles/Arduino_PS.dir/Arduino_PS.cpp.i

CMakeFiles/Arduino_PS.dir/Arduino_PS.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Arduino_PS.dir/Arduino_PS.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/davhor/Dropbox/CodeBase/Arduino/Pump_Control/src/Arduino_PS.cpp -o CMakeFiles/Arduino_PS.dir/Arduino_PS.cpp.s

CMakeFiles/Arduino_PS.dir/PS_func.cpp.o: CMakeFiles/Arduino_PS.dir/flags.make
CMakeFiles/Arduino_PS.dir/PS_func.cpp.o: /home/davhor/Dropbox/CodeBase/Arduino/Pump_Control/src/PS_func.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/davhor/Dropbox/CodeBase/Arduino/Pump_Control/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Arduino_PS.dir/PS_func.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Arduino_PS.dir/PS_func.cpp.o -c /home/davhor/Dropbox/CodeBase/Arduino/Pump_Control/src/PS_func.cpp

CMakeFiles/Arduino_PS.dir/PS_func.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Arduino_PS.dir/PS_func.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/davhor/Dropbox/CodeBase/Arduino/Pump_Control/src/PS_func.cpp > CMakeFiles/Arduino_PS.dir/PS_func.cpp.i

CMakeFiles/Arduino_PS.dir/PS_func.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Arduino_PS.dir/PS_func.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/davhor/Dropbox/CodeBase/Arduino/Pump_Control/src/PS_func.cpp -o CMakeFiles/Arduino_PS.dir/PS_func.cpp.s

CMakeFiles/Arduino_PS.dir/mock_arduino.cpp.o: CMakeFiles/Arduino_PS.dir/flags.make
CMakeFiles/Arduino_PS.dir/mock_arduino.cpp.o: /home/davhor/Dropbox/CodeBase/Arduino/Pump_Control/src/mock_arduino.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/davhor/Dropbox/CodeBase/Arduino/Pump_Control/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Arduino_PS.dir/mock_arduino.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Arduino_PS.dir/mock_arduino.cpp.o -c /home/davhor/Dropbox/CodeBase/Arduino/Pump_Control/src/mock_arduino.cpp

CMakeFiles/Arduino_PS.dir/mock_arduino.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Arduino_PS.dir/mock_arduino.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/davhor/Dropbox/CodeBase/Arduino/Pump_Control/src/mock_arduino.cpp > CMakeFiles/Arduino_PS.dir/mock_arduino.cpp.i

CMakeFiles/Arduino_PS.dir/mock_arduino.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Arduino_PS.dir/mock_arduino.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/davhor/Dropbox/CodeBase/Arduino/Pump_Control/src/mock_arduino.cpp -o CMakeFiles/Arduino_PS.dir/mock_arduino.cpp.s

CMakeFiles/Arduino_PS.dir/time.cpp.o: CMakeFiles/Arduino_PS.dir/flags.make
CMakeFiles/Arduino_PS.dir/time.cpp.o: /home/davhor/Dropbox/CodeBase/Arduino/Pump_Control/src/time.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/davhor/Dropbox/CodeBase/Arduino/Pump_Control/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Arduino_PS.dir/time.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Arduino_PS.dir/time.cpp.o -c /home/davhor/Dropbox/CodeBase/Arduino/Pump_Control/src/time.cpp

CMakeFiles/Arduino_PS.dir/time.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Arduino_PS.dir/time.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/davhor/Dropbox/CodeBase/Arduino/Pump_Control/src/time.cpp > CMakeFiles/Arduino_PS.dir/time.cpp.i

CMakeFiles/Arduino_PS.dir/time.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Arduino_PS.dir/time.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/davhor/Dropbox/CodeBase/Arduino/Pump_Control/src/time.cpp -o CMakeFiles/Arduino_PS.dir/time.cpp.s

# Object files for target Arduino_PS
Arduino_PS_OBJECTS = \
"CMakeFiles/Arduino_PS.dir/Arduino_PS.cpp.o" \
"CMakeFiles/Arduino_PS.dir/PS_func.cpp.o" \
"CMakeFiles/Arduino_PS.dir/mock_arduino.cpp.o" \
"CMakeFiles/Arduino_PS.dir/time.cpp.o"

# External object files for target Arduino_PS
Arduino_PS_EXTERNAL_OBJECTS =

Arduino_PS: CMakeFiles/Arduino_PS.dir/Arduino_PS.cpp.o
Arduino_PS: CMakeFiles/Arduino_PS.dir/PS_func.cpp.o
Arduino_PS: CMakeFiles/Arduino_PS.dir/mock_arduino.cpp.o
Arduino_PS: CMakeFiles/Arduino_PS.dir/time.cpp.o
Arduino_PS: CMakeFiles/Arduino_PS.dir/build.make
Arduino_PS: CMakeFiles/Arduino_PS.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/davhor/Dropbox/CodeBase/Arduino/Pump_Control/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable Arduino_PS"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Arduino_PS.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Arduino_PS.dir/build: Arduino_PS

.PHONY : CMakeFiles/Arduino_PS.dir/build

CMakeFiles/Arduino_PS.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Arduino_PS.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Arduino_PS.dir/clean

CMakeFiles/Arduino_PS.dir/depend:
	cd /home/davhor/Dropbox/CodeBase/Arduino/Pump_Control/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/davhor/Dropbox/CodeBase/Arduino/Pump_Control/src /home/davhor/Dropbox/CodeBase/Arduino/Pump_Control/src /home/davhor/Dropbox/CodeBase/Arduino/Pump_Control/build /home/davhor/Dropbox/CodeBase/Arduino/Pump_Control/build /home/davhor/Dropbox/CodeBase/Arduino/Pump_Control/build/CMakeFiles/Arduino_PS.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Arduino_PS.dir/depend

