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
CMAKE_SOURCE_DIR = /fsb/cjbrink1/EcEn390/LaserTag/ecen390

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag

# Include any dependencies generated for this target.
include lasertag/support/CMakeFiles/support.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include lasertag/support/CMakeFiles/support.dir/compiler_depend.make

# Include the progress variables for this target.
include lasertag/support/CMakeFiles/support.dir/progress.make

# Include the compile flags for this target's objects.
include lasertag/support/CMakeFiles/support.dir/flags.make

lasertag/support/CMakeFiles/support.dir/bufferTest.c.o: lasertag/support/CMakeFiles/support.dir/flags.make
lasertag/support/CMakeFiles/support.dir/bufferTest.c.o: support/bufferTest.c
lasertag/support/CMakeFiles/support.dir/bufferTest.c.o: lasertag/support/CMakeFiles/support.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object lasertag/support/CMakeFiles/support.dir/bufferTest.c.o"
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/support && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT lasertag/support/CMakeFiles/support.dir/bufferTest.c.o -MF CMakeFiles/support.dir/bufferTest.c.o.d -o CMakeFiles/support.dir/bufferTest.c.o -c /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/support/bufferTest.c

lasertag/support/CMakeFiles/support.dir/bufferTest.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/support.dir/bufferTest.c.i"
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/support && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/support/bufferTest.c > CMakeFiles/support.dir/bufferTest.c.i

lasertag/support/CMakeFiles/support.dir/bufferTest.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/support.dir/bufferTest.c.s"
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/support && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/support/bufferTest.c -o CMakeFiles/support.dir/bufferTest.c.s

lasertag/support/CMakeFiles/support.dir/filterTest.c.o: lasertag/support/CMakeFiles/support.dir/flags.make
lasertag/support/CMakeFiles/support.dir/filterTest.c.o: support/filterTest.c
lasertag/support/CMakeFiles/support.dir/filterTest.c.o: lasertag/support/CMakeFiles/support.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object lasertag/support/CMakeFiles/support.dir/filterTest.c.o"
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/support && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT lasertag/support/CMakeFiles/support.dir/filterTest.c.o -MF CMakeFiles/support.dir/filterTest.c.o.d -o CMakeFiles/support.dir/filterTest.c.o -c /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/support/filterTest.c

lasertag/support/CMakeFiles/support.dir/filterTest.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/support.dir/filterTest.c.i"
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/support && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/support/filterTest.c > CMakeFiles/support.dir/filterTest.c.i

lasertag/support/CMakeFiles/support.dir/filterTest.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/support.dir/filterTest.c.s"
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/support && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/support/filterTest.c -o CMakeFiles/support.dir/filterTest.c.s

lasertag/support/CMakeFiles/support.dir/histogram.c.o: lasertag/support/CMakeFiles/support.dir/flags.make
lasertag/support/CMakeFiles/support.dir/histogram.c.o: support/histogram.c
lasertag/support/CMakeFiles/support.dir/histogram.c.o: lasertag/support/CMakeFiles/support.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object lasertag/support/CMakeFiles/support.dir/histogram.c.o"
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/support && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT lasertag/support/CMakeFiles/support.dir/histogram.c.o -MF CMakeFiles/support.dir/histogram.c.o.d -o CMakeFiles/support.dir/histogram.c.o -c /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/support/histogram.c

lasertag/support/CMakeFiles/support.dir/histogram.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/support.dir/histogram.c.i"
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/support && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/support/histogram.c > CMakeFiles/support.dir/histogram.c.i

lasertag/support/CMakeFiles/support.dir/histogram.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/support.dir/histogram.c.s"
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/support && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/support/histogram.c -o CMakeFiles/support.dir/histogram.c.s

lasertag/support/CMakeFiles/support.dir/queueTest.c.o: lasertag/support/CMakeFiles/support.dir/flags.make
lasertag/support/CMakeFiles/support.dir/queueTest.c.o: support/queueTest.c
lasertag/support/CMakeFiles/support.dir/queueTest.c.o: lasertag/support/CMakeFiles/support.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object lasertag/support/CMakeFiles/support.dir/queueTest.c.o"
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/support && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT lasertag/support/CMakeFiles/support.dir/queueTest.c.o -MF CMakeFiles/support.dir/queueTest.c.o.d -o CMakeFiles/support.dir/queueTest.c.o -c /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/support/queueTest.c

lasertag/support/CMakeFiles/support.dir/queueTest.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/support.dir/queueTest.c.i"
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/support && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/support/queueTest.c > CMakeFiles/support.dir/queueTest.c.i

lasertag/support/CMakeFiles/support.dir/queueTest.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/support.dir/queueTest.c.s"
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/support && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/support/queueTest.c -o CMakeFiles/support.dir/queueTest.c.s

lasertag/support/CMakeFiles/support.dir/runningModes.c.o: lasertag/support/CMakeFiles/support.dir/flags.make
lasertag/support/CMakeFiles/support.dir/runningModes.c.o: support/runningModes.c
lasertag/support/CMakeFiles/support.dir/runningModes.c.o: lasertag/support/CMakeFiles/support.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object lasertag/support/CMakeFiles/support.dir/runningModes.c.o"
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/support && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT lasertag/support/CMakeFiles/support.dir/runningModes.c.o -MF CMakeFiles/support.dir/runningModes.c.o.d -o CMakeFiles/support.dir/runningModes.c.o -c /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/support/runningModes.c

lasertag/support/CMakeFiles/support.dir/runningModes.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/support.dir/runningModes.c.i"
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/support && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/support/runningModes.c > CMakeFiles/support.dir/runningModes.c.i

lasertag/support/CMakeFiles/support.dir/runningModes.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/support.dir/runningModes.c.s"
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/support && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/support/runningModes.c -o CMakeFiles/support.dir/runningModes.c.s

lasertag/support/CMakeFiles/support.dir/timer_ps.c.o: lasertag/support/CMakeFiles/support.dir/flags.make
lasertag/support/CMakeFiles/support.dir/timer_ps.c.o: support/timer_ps.c
lasertag/support/CMakeFiles/support.dir/timer_ps.c.o: lasertag/support/CMakeFiles/support.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object lasertag/support/CMakeFiles/support.dir/timer_ps.c.o"
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/support && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT lasertag/support/CMakeFiles/support.dir/timer_ps.c.o -MF CMakeFiles/support.dir/timer_ps.c.o.d -o CMakeFiles/support.dir/timer_ps.c.o -c /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/support/timer_ps.c

lasertag/support/CMakeFiles/support.dir/timer_ps.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/support.dir/timer_ps.c.i"
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/support && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/support/timer_ps.c > CMakeFiles/support.dir/timer_ps.c.i

lasertag/support/CMakeFiles/support.dir/timer_ps.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/support.dir/timer_ps.c.s"
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/support && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/support/timer_ps.c -o CMakeFiles/support.dir/timer_ps.c.s

# Object files for target support
support_OBJECTS = \
"CMakeFiles/support.dir/bufferTest.c.o" \
"CMakeFiles/support.dir/filterTest.c.o" \
"CMakeFiles/support.dir/histogram.c.o" \
"CMakeFiles/support.dir/queueTest.c.o" \
"CMakeFiles/support.dir/runningModes.c.o" \
"CMakeFiles/support.dir/timer_ps.c.o"

# External object files for target support
support_EXTERNAL_OBJECTS =

lasertag/support/libsupport.a: lasertag/support/CMakeFiles/support.dir/bufferTest.c.o
lasertag/support/libsupport.a: lasertag/support/CMakeFiles/support.dir/filterTest.c.o
lasertag/support/libsupport.a: lasertag/support/CMakeFiles/support.dir/histogram.c.o
lasertag/support/libsupport.a: lasertag/support/CMakeFiles/support.dir/queueTest.c.o
lasertag/support/libsupport.a: lasertag/support/CMakeFiles/support.dir/runningModes.c.o
lasertag/support/libsupport.a: lasertag/support/CMakeFiles/support.dir/timer_ps.c.o
lasertag/support/libsupport.a: lasertag/support/CMakeFiles/support.dir/build.make
lasertag/support/libsupport.a: lasertag/support/CMakeFiles/support.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking C static library libsupport.a"
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/support && $(CMAKE_COMMAND) -P CMakeFiles/support.dir/cmake_clean_target.cmake
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/support && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/support.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lasertag/support/CMakeFiles/support.dir/build: lasertag/support/libsupport.a
.PHONY : lasertag/support/CMakeFiles/support.dir/build

lasertag/support/CMakeFiles/support.dir/clean:
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/support && $(CMAKE_COMMAND) -P CMakeFiles/support.dir/cmake_clean.cmake
.PHONY : lasertag/support/CMakeFiles/support.dir/clean

lasertag/support/CMakeFiles/support.dir/depend:
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /fsb/cjbrink1/EcEn390/LaserTag/ecen390 /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/support /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/support /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/support/CMakeFiles/support.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lasertag/support/CMakeFiles/support.dir/depend

