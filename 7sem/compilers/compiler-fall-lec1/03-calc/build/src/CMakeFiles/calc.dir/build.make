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
CMAKE_SOURCE_DIR = /mnt/c/cicada-main/sibsutis/7sem/compilers/compiler-fall-lec1/03-calc

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/cicada-main/sibsutis/7sem/compilers/compiler-fall-lec1/03-calc/build

# Include any dependencies generated for this target.
include src/CMakeFiles/calc.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/calc.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/calc.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/calc.dir/flags.make

src/CMakeFiles/calc.dir/Calc.cpp.o: src/CMakeFiles/calc.dir/flags.make
src/CMakeFiles/calc.dir/Calc.cpp.o: ../src/Calc.cpp
src/CMakeFiles/calc.dir/Calc.cpp.o: src/CMakeFiles/calc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/cicada-main/sibsutis/7sem/compilers/compiler-fall-lec1/03-calc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/calc.dir/Calc.cpp.o"
	cd /mnt/c/cicada-main/sibsutis/7sem/compilers/compiler-fall-lec1/03-calc/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/calc.dir/Calc.cpp.o -MF CMakeFiles/calc.dir/Calc.cpp.o.d -o CMakeFiles/calc.dir/Calc.cpp.o -c /mnt/c/cicada-main/sibsutis/7sem/compilers/compiler-fall-lec1/03-calc/src/Calc.cpp

src/CMakeFiles/calc.dir/Calc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/calc.dir/Calc.cpp.i"
	cd /mnt/c/cicada-main/sibsutis/7sem/compilers/compiler-fall-lec1/03-calc/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/cicada-main/sibsutis/7sem/compilers/compiler-fall-lec1/03-calc/src/Calc.cpp > CMakeFiles/calc.dir/Calc.cpp.i

src/CMakeFiles/calc.dir/Calc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/calc.dir/Calc.cpp.s"
	cd /mnt/c/cicada-main/sibsutis/7sem/compilers/compiler-fall-lec1/03-calc/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/cicada-main/sibsutis/7sem/compilers/compiler-fall-lec1/03-calc/src/Calc.cpp -o CMakeFiles/calc.dir/Calc.cpp.s

src/CMakeFiles/calc.dir/CodeGen.cpp.o: src/CMakeFiles/calc.dir/flags.make
src/CMakeFiles/calc.dir/CodeGen.cpp.o: ../src/CodeGen.cpp
src/CMakeFiles/calc.dir/CodeGen.cpp.o: src/CMakeFiles/calc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/cicada-main/sibsutis/7sem/compilers/compiler-fall-lec1/03-calc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/calc.dir/CodeGen.cpp.o"
	cd /mnt/c/cicada-main/sibsutis/7sem/compilers/compiler-fall-lec1/03-calc/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/calc.dir/CodeGen.cpp.o -MF CMakeFiles/calc.dir/CodeGen.cpp.o.d -o CMakeFiles/calc.dir/CodeGen.cpp.o -c /mnt/c/cicada-main/sibsutis/7sem/compilers/compiler-fall-lec1/03-calc/src/CodeGen.cpp

src/CMakeFiles/calc.dir/CodeGen.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/calc.dir/CodeGen.cpp.i"
	cd /mnt/c/cicada-main/sibsutis/7sem/compilers/compiler-fall-lec1/03-calc/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/cicada-main/sibsutis/7sem/compilers/compiler-fall-lec1/03-calc/src/CodeGen.cpp > CMakeFiles/calc.dir/CodeGen.cpp.i

src/CMakeFiles/calc.dir/CodeGen.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/calc.dir/CodeGen.cpp.s"
	cd /mnt/c/cicada-main/sibsutis/7sem/compilers/compiler-fall-lec1/03-calc/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/cicada-main/sibsutis/7sem/compilers/compiler-fall-lec1/03-calc/src/CodeGen.cpp -o CMakeFiles/calc.dir/CodeGen.cpp.s

src/CMakeFiles/calc.dir/Lexer.cpp.o: src/CMakeFiles/calc.dir/flags.make
src/CMakeFiles/calc.dir/Lexer.cpp.o: ../src/Lexer.cpp
src/CMakeFiles/calc.dir/Lexer.cpp.o: src/CMakeFiles/calc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/cicada-main/sibsutis/7sem/compilers/compiler-fall-lec1/03-calc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/calc.dir/Lexer.cpp.o"
	cd /mnt/c/cicada-main/sibsutis/7sem/compilers/compiler-fall-lec1/03-calc/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/calc.dir/Lexer.cpp.o -MF CMakeFiles/calc.dir/Lexer.cpp.o.d -o CMakeFiles/calc.dir/Lexer.cpp.o -c /mnt/c/cicada-main/sibsutis/7sem/compilers/compiler-fall-lec1/03-calc/src/Lexer.cpp

src/CMakeFiles/calc.dir/Lexer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/calc.dir/Lexer.cpp.i"
	cd /mnt/c/cicada-main/sibsutis/7sem/compilers/compiler-fall-lec1/03-calc/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/cicada-main/sibsutis/7sem/compilers/compiler-fall-lec1/03-calc/src/Lexer.cpp > CMakeFiles/calc.dir/Lexer.cpp.i

src/CMakeFiles/calc.dir/Lexer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/calc.dir/Lexer.cpp.s"
	cd /mnt/c/cicada-main/sibsutis/7sem/compilers/compiler-fall-lec1/03-calc/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/cicada-main/sibsutis/7sem/compilers/compiler-fall-lec1/03-calc/src/Lexer.cpp -o CMakeFiles/calc.dir/Lexer.cpp.s

src/CMakeFiles/calc.dir/Parser.cpp.o: src/CMakeFiles/calc.dir/flags.make
src/CMakeFiles/calc.dir/Parser.cpp.o: ../src/Parser.cpp
src/CMakeFiles/calc.dir/Parser.cpp.o: src/CMakeFiles/calc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/cicada-main/sibsutis/7sem/compilers/compiler-fall-lec1/03-calc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/CMakeFiles/calc.dir/Parser.cpp.o"
	cd /mnt/c/cicada-main/sibsutis/7sem/compilers/compiler-fall-lec1/03-calc/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/calc.dir/Parser.cpp.o -MF CMakeFiles/calc.dir/Parser.cpp.o.d -o CMakeFiles/calc.dir/Parser.cpp.o -c /mnt/c/cicada-main/sibsutis/7sem/compilers/compiler-fall-lec1/03-calc/src/Parser.cpp

src/CMakeFiles/calc.dir/Parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/calc.dir/Parser.cpp.i"
	cd /mnt/c/cicada-main/sibsutis/7sem/compilers/compiler-fall-lec1/03-calc/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/cicada-main/sibsutis/7sem/compilers/compiler-fall-lec1/03-calc/src/Parser.cpp > CMakeFiles/calc.dir/Parser.cpp.i

src/CMakeFiles/calc.dir/Parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/calc.dir/Parser.cpp.s"
	cd /mnt/c/cicada-main/sibsutis/7sem/compilers/compiler-fall-lec1/03-calc/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/cicada-main/sibsutis/7sem/compilers/compiler-fall-lec1/03-calc/src/Parser.cpp -o CMakeFiles/calc.dir/Parser.cpp.s

src/CMakeFiles/calc.dir/Sema.cpp.o: src/CMakeFiles/calc.dir/flags.make
src/CMakeFiles/calc.dir/Sema.cpp.o: ../src/Sema.cpp
src/CMakeFiles/calc.dir/Sema.cpp.o: src/CMakeFiles/calc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/cicada-main/sibsutis/7sem/compilers/compiler-fall-lec1/03-calc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/CMakeFiles/calc.dir/Sema.cpp.o"
	cd /mnt/c/cicada-main/sibsutis/7sem/compilers/compiler-fall-lec1/03-calc/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/calc.dir/Sema.cpp.o -MF CMakeFiles/calc.dir/Sema.cpp.o.d -o CMakeFiles/calc.dir/Sema.cpp.o -c /mnt/c/cicada-main/sibsutis/7sem/compilers/compiler-fall-lec1/03-calc/src/Sema.cpp

src/CMakeFiles/calc.dir/Sema.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/calc.dir/Sema.cpp.i"
	cd /mnt/c/cicada-main/sibsutis/7sem/compilers/compiler-fall-lec1/03-calc/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/cicada-main/sibsutis/7sem/compilers/compiler-fall-lec1/03-calc/src/Sema.cpp > CMakeFiles/calc.dir/Sema.cpp.i

src/CMakeFiles/calc.dir/Sema.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/calc.dir/Sema.cpp.s"
	cd /mnt/c/cicada-main/sibsutis/7sem/compilers/compiler-fall-lec1/03-calc/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/cicada-main/sibsutis/7sem/compilers/compiler-fall-lec1/03-calc/src/Sema.cpp -o CMakeFiles/calc.dir/Sema.cpp.s

# Object files for target calc
calc_OBJECTS = \
"CMakeFiles/calc.dir/Calc.cpp.o" \
"CMakeFiles/calc.dir/CodeGen.cpp.o" \
"CMakeFiles/calc.dir/Lexer.cpp.o" \
"CMakeFiles/calc.dir/Parser.cpp.o" \
"CMakeFiles/calc.dir/Sema.cpp.o"

# External object files for target calc
calc_EXTERNAL_OBJECTS =

src/calc: src/CMakeFiles/calc.dir/Calc.cpp.o
src/calc: src/CMakeFiles/calc.dir/CodeGen.cpp.o
src/calc: src/CMakeFiles/calc.dir/Lexer.cpp.o
src/calc: src/CMakeFiles/calc.dir/Parser.cpp.o
src/calc: src/CMakeFiles/calc.dir/Sema.cpp.o
src/calc: src/CMakeFiles/calc.dir/build.make
src/calc: /usr/lib/llvm-14/lib/libLLVMCore.a
src/calc: /usr/lib/llvm-14/lib/libLLVMBinaryFormat.a
src/calc: /usr/lib/llvm-14/lib/libLLVMRemarks.a
src/calc: /usr/lib/llvm-14/lib/libLLVMBitstreamReader.a
src/calc: /usr/lib/llvm-14/lib/libLLVMSupport.a
src/calc: /usr/lib/x86_64-linux-gnu/libz.so
src/calc: /usr/lib/x86_64-linux-gnu/libtinfo.so
src/calc: /usr/lib/llvm-14/lib/libLLVMDemangle.a
src/calc: src/CMakeFiles/calc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/cicada-main/sibsutis/7sem/compilers/compiler-fall-lec1/03-calc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable calc"
	cd /mnt/c/cicada-main/sibsutis/7sem/compilers/compiler-fall-lec1/03-calc/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/calc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/calc.dir/build: src/calc
.PHONY : src/CMakeFiles/calc.dir/build

src/CMakeFiles/calc.dir/clean:
	cd /mnt/c/cicada-main/sibsutis/7sem/compilers/compiler-fall-lec1/03-calc/build/src && $(CMAKE_COMMAND) -P CMakeFiles/calc.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/calc.dir/clean

src/CMakeFiles/calc.dir/depend:
	cd /mnt/c/cicada-main/sibsutis/7sem/compilers/compiler-fall-lec1/03-calc/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/cicada-main/sibsutis/7sem/compilers/compiler-fall-lec1/03-calc /mnt/c/cicada-main/sibsutis/7sem/compilers/compiler-fall-lec1/03-calc/src /mnt/c/cicada-main/sibsutis/7sem/compilers/compiler-fall-lec1/03-calc/build /mnt/c/cicada-main/sibsutis/7sem/compilers/compiler-fall-lec1/03-calc/build/src /mnt/c/cicada-main/sibsutis/7sem/compilers/compiler-fall-lec1/03-calc/build/src/CMakeFiles/calc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/calc.dir/depend
