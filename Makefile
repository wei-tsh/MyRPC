# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

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
CMAKE_SOURCE_DIR = /home/wei2/MyRPC

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wei2/MyRPC

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/wei2/MyRPC/CMakeFiles /home/wei2/MyRPC//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/wei2/MyRPC/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named Client

# Build rule for target.
Client: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 Client
.PHONY : Client

# fast build rule for target.
Client/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Client.dir/build.make CMakeFiles/Client.dir/build
.PHONY : Client/fast

#=============================================================================
# Target rules for targets named Server

# Build rule for target.
Server: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 Server
.PHONY : Server

# fast build rule for target.
Server/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Server.dir/build.make CMakeFiles/Server.dir/build
.PHONY : Server/fast

RpcClient.o: RpcClient.cpp.o
.PHONY : RpcClient.o

# target to build an object file
RpcClient.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Client.dir/build.make CMakeFiles/Client.dir/RpcClient.cpp.o
.PHONY : RpcClient.cpp.o

RpcClient.i: RpcClient.cpp.i
.PHONY : RpcClient.i

# target to preprocess a source file
RpcClient.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Client.dir/build.make CMakeFiles/Client.dir/RpcClient.cpp.i
.PHONY : RpcClient.cpp.i

RpcClient.s: RpcClient.cpp.s
.PHONY : RpcClient.s

# target to generate assembly for a file
RpcClient.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Client.dir/build.make CMakeFiles/Client.dir/RpcClient.cpp.s
.PHONY : RpcClient.cpp.s

RpcServer.o: RpcServer.cpp.o
.PHONY : RpcServer.o

# target to build an object file
RpcServer.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Server.dir/build.make CMakeFiles/Server.dir/RpcServer.cpp.o
.PHONY : RpcServer.cpp.o

RpcServer.i: RpcServer.cpp.i
.PHONY : RpcServer.i

# target to preprocess a source file
RpcServer.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Server.dir/build.make CMakeFiles/Server.dir/RpcServer.cpp.i
.PHONY : RpcServer.cpp.i

RpcServer.s: RpcServer.cpp.s
.PHONY : RpcServer.s

# target to generate assembly for a file
RpcServer.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Server.dir/build.make CMakeFiles/Server.dir/RpcServer.cpp.s
.PHONY : RpcServer.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... Client"
	@echo "... Server"
	@echo "... RpcClient.o"
	@echo "... RpcClient.i"
	@echo "... RpcClient.s"
	@echo "... RpcServer.o"
	@echo "... RpcServer.i"
	@echo "... RpcServer.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

