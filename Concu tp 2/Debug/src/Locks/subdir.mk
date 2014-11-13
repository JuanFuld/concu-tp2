################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Locks/LockFile.cpp 

OBJS += \
./src/Locks/LockFile.o 

CPP_DEPS += \
./src/Locks/LockFile.d 


# Each subdirectory must supply rules for building sources it contributes
src/Locks/%.o: ../src/Locks/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DCLIENTE -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


