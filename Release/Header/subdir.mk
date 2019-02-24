################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Header/GameOver.cpp 

OBJS += \
./Header/GameOver.o 

CPP_DEPS += \
./Header/GameOver.d 


# Each subdirectory must supply rules for building sources it contributes
Header/%.o: ../Header/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++1y -I../lib -I../Header -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


