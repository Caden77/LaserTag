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
include lasertag/sound/CMakeFiles/sound.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include lasertag/sound/CMakeFiles/sound.dir/compiler_depend.make

# Include the progress variables for this target.
include lasertag/sound/CMakeFiles/sound.dir/progress.make

# Include the compile flags for this target's objects.
include lasertag/sound/CMakeFiles/sound.dir/flags.make

lasertag/sound/CMakeFiles/sound.dir/bcfire01_48k.wav.c.o: lasertag/sound/CMakeFiles/sound.dir/flags.make
lasertag/sound/CMakeFiles/sound.dir/bcfire01_48k.wav.c.o: sound/bcfire01_48k.wav.c
lasertag/sound/CMakeFiles/sound.dir/bcfire01_48k.wav.c.o: lasertag/sound/CMakeFiles/sound.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object lasertag/sound/CMakeFiles/sound.dir/bcfire01_48k.wav.c.o"
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/sound && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT lasertag/sound/CMakeFiles/sound.dir/bcfire01_48k.wav.c.o -MF CMakeFiles/sound.dir/bcfire01_48k.wav.c.o.d -o CMakeFiles/sound.dir/bcfire01_48k.wav.c.o -c /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/sound/bcfire01_48k.wav.c

lasertag/sound/CMakeFiles/sound.dir/bcfire01_48k.wav.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sound.dir/bcfire01_48k.wav.c.i"
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/sound && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/sound/bcfire01_48k.wav.c > CMakeFiles/sound.dir/bcfire01_48k.wav.c.i

lasertag/sound/CMakeFiles/sound.dir/bcfire01_48k.wav.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sound.dir/bcfire01_48k.wav.c.s"
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/sound && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/sound/bcfire01_48k.wav.c -o CMakeFiles/sound.dir/bcfire01_48k.wav.c.s

lasertag/sound/CMakeFiles/sound.dir/gameBoyStartup.wav.c.o: lasertag/sound/CMakeFiles/sound.dir/flags.make
lasertag/sound/CMakeFiles/sound.dir/gameBoyStartup.wav.c.o: sound/gameBoyStartup.wav.c
lasertag/sound/CMakeFiles/sound.dir/gameBoyStartup.wav.c.o: lasertag/sound/CMakeFiles/sound.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object lasertag/sound/CMakeFiles/sound.dir/gameBoyStartup.wav.c.o"
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/sound && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT lasertag/sound/CMakeFiles/sound.dir/gameBoyStartup.wav.c.o -MF CMakeFiles/sound.dir/gameBoyStartup.wav.c.o.d -o CMakeFiles/sound.dir/gameBoyStartup.wav.c.o -c /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/sound/gameBoyStartup.wav.c

lasertag/sound/CMakeFiles/sound.dir/gameBoyStartup.wav.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sound.dir/gameBoyStartup.wav.c.i"
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/sound && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/sound/gameBoyStartup.wav.c > CMakeFiles/sound.dir/gameBoyStartup.wav.c.i

lasertag/sound/CMakeFiles/sound.dir/gameBoyStartup.wav.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sound.dir/gameBoyStartup.wav.c.s"
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/sound && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/sound/gameBoyStartup.wav.c -o CMakeFiles/sound.dir/gameBoyStartup.wav.c.s

lasertag/sound/CMakeFiles/sound.dir/gameOver48k.wav.c.o: lasertag/sound/CMakeFiles/sound.dir/flags.make
lasertag/sound/CMakeFiles/sound.dir/gameOver48k.wav.c.o: sound/gameOver48k.wav.c
lasertag/sound/CMakeFiles/sound.dir/gameOver48k.wav.c.o: lasertag/sound/CMakeFiles/sound.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object lasertag/sound/CMakeFiles/sound.dir/gameOver48k.wav.c.o"
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/sound && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT lasertag/sound/CMakeFiles/sound.dir/gameOver48k.wav.c.o -MF CMakeFiles/sound.dir/gameOver48k.wav.c.o.d -o CMakeFiles/sound.dir/gameOver48k.wav.c.o -c /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/sound/gameOver48k.wav.c

lasertag/sound/CMakeFiles/sound.dir/gameOver48k.wav.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sound.dir/gameOver48k.wav.c.i"
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/sound && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/sound/gameOver48k.wav.c > CMakeFiles/sound.dir/gameOver48k.wav.c.i

lasertag/sound/CMakeFiles/sound.dir/gameOver48k.wav.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sound.dir/gameOver48k.wav.c.s"
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/sound && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/sound/gameOver48k.wav.c -o CMakeFiles/sound.dir/gameOver48k.wav.c.s

lasertag/sound/CMakeFiles/sound.dir/gunEmpty48k.wav.c.o: lasertag/sound/CMakeFiles/sound.dir/flags.make
lasertag/sound/CMakeFiles/sound.dir/gunEmpty48k.wav.c.o: sound/gunEmpty48k.wav.c
lasertag/sound/CMakeFiles/sound.dir/gunEmpty48k.wav.c.o: lasertag/sound/CMakeFiles/sound.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object lasertag/sound/CMakeFiles/sound.dir/gunEmpty48k.wav.c.o"
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/sound && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT lasertag/sound/CMakeFiles/sound.dir/gunEmpty48k.wav.c.o -MF CMakeFiles/sound.dir/gunEmpty48k.wav.c.o.d -o CMakeFiles/sound.dir/gunEmpty48k.wav.c.o -c /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/sound/gunEmpty48k.wav.c

lasertag/sound/CMakeFiles/sound.dir/gunEmpty48k.wav.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sound.dir/gunEmpty48k.wav.c.i"
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/sound && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/sound/gunEmpty48k.wav.c > CMakeFiles/sound.dir/gunEmpty48k.wav.c.i

lasertag/sound/CMakeFiles/sound.dir/gunEmpty48k.wav.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sound.dir/gunEmpty48k.wav.c.s"
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/sound && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/sound/gunEmpty48k.wav.c -o CMakeFiles/sound.dir/gunEmpty48k.wav.c.s

lasertag/sound/CMakeFiles/sound.dir/ouch48k.wav.c.o: lasertag/sound/CMakeFiles/sound.dir/flags.make
lasertag/sound/CMakeFiles/sound.dir/ouch48k.wav.c.o: sound/ouch48k.wav.c
lasertag/sound/CMakeFiles/sound.dir/ouch48k.wav.c.o: lasertag/sound/CMakeFiles/sound.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object lasertag/sound/CMakeFiles/sound.dir/ouch48k.wav.c.o"
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/sound && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT lasertag/sound/CMakeFiles/sound.dir/ouch48k.wav.c.o -MF CMakeFiles/sound.dir/ouch48k.wav.c.o.d -o CMakeFiles/sound.dir/ouch48k.wav.c.o -c /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/sound/ouch48k.wav.c

lasertag/sound/CMakeFiles/sound.dir/ouch48k.wav.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sound.dir/ouch48k.wav.c.i"
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/sound && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/sound/ouch48k.wav.c > CMakeFiles/sound.dir/ouch48k.wav.c.i

lasertag/sound/CMakeFiles/sound.dir/ouch48k.wav.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sound.dir/ouch48k.wav.c.s"
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/sound && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/sound/ouch48k.wav.c -o CMakeFiles/sound.dir/ouch48k.wav.c.s

lasertag/sound/CMakeFiles/sound.dir/pacmanDeath.wav.c.o: lasertag/sound/CMakeFiles/sound.dir/flags.make
lasertag/sound/CMakeFiles/sound.dir/pacmanDeath.wav.c.o: sound/pacmanDeath.wav.c
lasertag/sound/CMakeFiles/sound.dir/pacmanDeath.wav.c.o: lasertag/sound/CMakeFiles/sound.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object lasertag/sound/CMakeFiles/sound.dir/pacmanDeath.wav.c.o"
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/sound && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT lasertag/sound/CMakeFiles/sound.dir/pacmanDeath.wav.c.o -MF CMakeFiles/sound.dir/pacmanDeath.wav.c.o.d -o CMakeFiles/sound.dir/pacmanDeath.wav.c.o -c /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/sound/pacmanDeath.wav.c

lasertag/sound/CMakeFiles/sound.dir/pacmanDeath.wav.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sound.dir/pacmanDeath.wav.c.i"
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/sound && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/sound/pacmanDeath.wav.c > CMakeFiles/sound.dir/pacmanDeath.wav.c.i

lasertag/sound/CMakeFiles/sound.dir/pacmanDeath.wav.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sound.dir/pacmanDeath.wav.c.s"
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/sound && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/sound/pacmanDeath.wav.c -o CMakeFiles/sound.dir/pacmanDeath.wav.c.s

lasertag/sound/CMakeFiles/sound.dir/powerUp48k.wav.c.o: lasertag/sound/CMakeFiles/sound.dir/flags.make
lasertag/sound/CMakeFiles/sound.dir/powerUp48k.wav.c.o: sound/powerUp48k.wav.c
lasertag/sound/CMakeFiles/sound.dir/powerUp48k.wav.c.o: lasertag/sound/CMakeFiles/sound.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object lasertag/sound/CMakeFiles/sound.dir/powerUp48k.wav.c.o"
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/sound && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT lasertag/sound/CMakeFiles/sound.dir/powerUp48k.wav.c.o -MF CMakeFiles/sound.dir/powerUp48k.wav.c.o.d -o CMakeFiles/sound.dir/powerUp48k.wav.c.o -c /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/sound/powerUp48k.wav.c

lasertag/sound/CMakeFiles/sound.dir/powerUp48k.wav.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sound.dir/powerUp48k.wav.c.i"
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/sound && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/sound/powerUp48k.wav.c > CMakeFiles/sound.dir/powerUp48k.wav.c.i

lasertag/sound/CMakeFiles/sound.dir/powerUp48k.wav.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sound.dir/powerUp48k.wav.c.s"
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/sound && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/sound/powerUp48k.wav.c -o CMakeFiles/sound.dir/powerUp48k.wav.c.s

lasertag/sound/CMakeFiles/sound.dir/screamAndDie48k.wav.c.o: lasertag/sound/CMakeFiles/sound.dir/flags.make
lasertag/sound/CMakeFiles/sound.dir/screamAndDie48k.wav.c.o: sound/screamAndDie48k.wav.c
lasertag/sound/CMakeFiles/sound.dir/screamAndDie48k.wav.c.o: lasertag/sound/CMakeFiles/sound.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object lasertag/sound/CMakeFiles/sound.dir/screamAndDie48k.wav.c.o"
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/sound && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT lasertag/sound/CMakeFiles/sound.dir/screamAndDie48k.wav.c.o -MF CMakeFiles/sound.dir/screamAndDie48k.wav.c.o.d -o CMakeFiles/sound.dir/screamAndDie48k.wav.c.o -c /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/sound/screamAndDie48k.wav.c

lasertag/sound/CMakeFiles/sound.dir/screamAndDie48k.wav.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sound.dir/screamAndDie48k.wav.c.i"
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/sound && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/sound/screamAndDie48k.wav.c > CMakeFiles/sound.dir/screamAndDie48k.wav.c.i

lasertag/sound/CMakeFiles/sound.dir/screamAndDie48k.wav.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sound.dir/screamAndDie48k.wav.c.s"
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/sound && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/sound/screamAndDie48k.wav.c -o CMakeFiles/sound.dir/screamAndDie48k.wav.c.s

lasertag/sound/CMakeFiles/sound.dir/sound.c.o: lasertag/sound/CMakeFiles/sound.dir/flags.make
lasertag/sound/CMakeFiles/sound.dir/sound.c.o: sound/sound.c
lasertag/sound/CMakeFiles/sound.dir/sound.c.o: lasertag/sound/CMakeFiles/sound.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object lasertag/sound/CMakeFiles/sound.dir/sound.c.o"
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/sound && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT lasertag/sound/CMakeFiles/sound.dir/sound.c.o -MF CMakeFiles/sound.dir/sound.c.o.d -o CMakeFiles/sound.dir/sound.c.o -c /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/sound/sound.c

lasertag/sound/CMakeFiles/sound.dir/sound.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sound.dir/sound.c.i"
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/sound && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/sound/sound.c > CMakeFiles/sound.dir/sound.c.i

lasertag/sound/CMakeFiles/sound.dir/sound.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sound.dir/sound.c.s"
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/sound && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/sound/sound.c -o CMakeFiles/sound.dir/sound.c.s

# Object files for target sound
sound_OBJECTS = \
"CMakeFiles/sound.dir/bcfire01_48k.wav.c.o" \
"CMakeFiles/sound.dir/gameBoyStartup.wav.c.o" \
"CMakeFiles/sound.dir/gameOver48k.wav.c.o" \
"CMakeFiles/sound.dir/gunEmpty48k.wav.c.o" \
"CMakeFiles/sound.dir/ouch48k.wav.c.o" \
"CMakeFiles/sound.dir/pacmanDeath.wav.c.o" \
"CMakeFiles/sound.dir/powerUp48k.wav.c.o" \
"CMakeFiles/sound.dir/screamAndDie48k.wav.c.o" \
"CMakeFiles/sound.dir/sound.c.o"

# External object files for target sound
sound_EXTERNAL_OBJECTS =

lasertag/sound/libsound.a: lasertag/sound/CMakeFiles/sound.dir/bcfire01_48k.wav.c.o
lasertag/sound/libsound.a: lasertag/sound/CMakeFiles/sound.dir/gameBoyStartup.wav.c.o
lasertag/sound/libsound.a: lasertag/sound/CMakeFiles/sound.dir/gameOver48k.wav.c.o
lasertag/sound/libsound.a: lasertag/sound/CMakeFiles/sound.dir/gunEmpty48k.wav.c.o
lasertag/sound/libsound.a: lasertag/sound/CMakeFiles/sound.dir/ouch48k.wav.c.o
lasertag/sound/libsound.a: lasertag/sound/CMakeFiles/sound.dir/pacmanDeath.wav.c.o
lasertag/sound/libsound.a: lasertag/sound/CMakeFiles/sound.dir/powerUp48k.wav.c.o
lasertag/sound/libsound.a: lasertag/sound/CMakeFiles/sound.dir/screamAndDie48k.wav.c.o
lasertag/sound/libsound.a: lasertag/sound/CMakeFiles/sound.dir/sound.c.o
lasertag/sound/libsound.a: lasertag/sound/CMakeFiles/sound.dir/build.make
lasertag/sound/libsound.a: lasertag/sound/CMakeFiles/sound.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking C static library libsound.a"
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/sound && $(CMAKE_COMMAND) -P CMakeFiles/sound.dir/cmake_clean_target.cmake
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/sound && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sound.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lasertag/sound/CMakeFiles/sound.dir/build: lasertag/sound/libsound.a
.PHONY : lasertag/sound/CMakeFiles/sound.dir/build

lasertag/sound/CMakeFiles/sound.dir/clean:
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/sound && $(CMAKE_COMMAND) -P CMakeFiles/sound.dir/cmake_clean.cmake
.PHONY : lasertag/sound/CMakeFiles/sound.dir/clean

lasertag/sound/CMakeFiles/sound.dir/depend:
	cd /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /fsb/cjbrink1/EcEn390/LaserTag/ecen390 /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/sound /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/sound /fsb/cjbrink1/EcEn390/LaserTag/ecen390/lasertag/lasertag/sound/CMakeFiles/sound.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lasertag/sound/CMakeFiles/sound.dir/depend

