################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/EntityState.cpp \
../Source/GameState.cpp \
../Source/IdleState.cpp \
../Source/JumpState.cpp \
../Source/Level.cpp \
../Source/LevelParser.cpp \
../Source/MainGero.cpp \
../Source/MenuState.cpp \
../Source/ObjectBox2D.cpp \
../Source/ObjectSfml.cpp \
../Source/ParserXML.cpp \
../Source/PassedLevel.cpp \
../Source/PauseState.cpp \
../Source/RunState.cpp \
../Source/SelectAnimation.cpp \
../Source/State.cpp \
../Source/StateStack.cpp \
../Source/StatusBar.cpp \
../Source/TitleState.cpp \
../Source/Utility.cpp \
../Source/WalkState.cpp \
../Source/World.cpp \
../Source/main.cpp 

OBJS += \
./Source/EntityState.o \
./Source/GameState.o \
./Source/IdleState.o \
./Source/JumpState.o \
./Source/Level.o \
./Source/LevelParser.o \
./Source/MainGero.o \
./Source/MenuState.o \
./Source/ObjectBox2D.o \
./Source/ObjectSfml.o \
./Source/ParserXML.o \
./Source/PassedLevel.o \
./Source/PauseState.o \
./Source/RunState.o \
./Source/SelectAnimation.o \
./Source/State.o \
./Source/StateStack.o \
./Source/StatusBar.o \
./Source/TitleState.o \
./Source/Utility.o \
./Source/WalkState.o \
./Source/World.o \
./Source/main.o 

CPP_DEPS += \
./Source/EntityState.d \
./Source/GameState.d \
./Source/IdleState.d \
./Source/JumpState.d \
./Source/Level.d \
./Source/LevelParser.d \
./Source/MainGero.d \
./Source/MenuState.d \
./Source/ObjectBox2D.d \
./Source/ObjectSfml.d \
./Source/ParserXML.d \
./Source/PassedLevel.d \
./Source/PauseState.d \
./Source/RunState.d \
./Source/SelectAnimation.d \
./Source/State.d \
./Source/StateStack.d \
./Source/StatusBar.d \
./Source/TitleState.d \
./Source/Utility.d \
./Source/WalkState.d \
./Source/World.d \
./Source/main.d 


# Each subdirectory must supply rules for building sources it contributes
Source/%.o: ../Source/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++1y -I../lib -I../Header -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


