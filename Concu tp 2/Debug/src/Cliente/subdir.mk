################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Cliente/Cliente.cpp \
../src/Cliente/main.cpp 

OBJS += \
./src/Cliente/Cliente.o \
./src/Cliente/main.o 

CPP_DEPS += \
./src/Cliente/Cliente.d \
./src/Cliente/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/Cliente/%.o: ../src/Cliente/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DCLIENTE -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


