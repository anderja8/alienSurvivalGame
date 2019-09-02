# Program name: Project5_Anderson_Jacob
# Author: Jacob Anderson
# Date: 11/26/18
# Description: Creates a space invasion video game. The goal is to find a radio,
# activate it, and survive for 10 turns while aliens hunt you.

# This makefile is inspired by the example makefile from Oregon State.
# Available at: https://oregonstate.instructure.com/courses/1692879/files/71792854

# Which compiler to use
CXX = g++

# Which flags to pas to compiler
CXXFLAGS = -std=c++0x
CXXFLAGS += -Wall
CXXFLAGS += -pedantic-errors

# Variable name for my objects
OBJS = Alien.o Board.o inputValidation.o Instructions.o Main.o NormalSpace.o Player.o Space.o Turret.o Wormhole.o

# Variable name for my sources (.cpp)
SRCS = Alien.cpp Board.cpp inputValidation.cpp Instructions.cpp Main.cpp NormalSpace.cpp Player.cpp Space.cpp Turret.cpp Wormhole.cpp

# Variable name for my headers (.hpp)
HEADERS = Alien.hpp Board.hpp inputValidation.hpp Instructions.hpp NormalSpace.hpp Player.hpp Space.hpp Turret.hpp Wormhole.hpp

# Command to compile my executable from my objects
Project5_Anderson_Jacob: ${OBJS} ${HEADERS}
	${CXX} ${OBJS} -o Project5_Anderson_Jacob.exe

# Command to compile my objects from my sources
${OBJS}: ${SRCS}
	${CXX} ${CXXFLAGS} -c -g $(@:.o=.cpp)

# Command to clean the files
clean:
	rm ${OBJS} Project5_Anderson_Jacob.exe