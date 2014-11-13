################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Servidor/Servidor.cpp \
../src/Servidor/main.cpp 

OBJS += \
./src/Servidor/Servidor.o \
./src/Servidor/main.o 

CPP_DEPS += \
./src/Servidor/Servidor.d \
./src/Servidor/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/Servidor/%.o: ../src/Servidor/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DSERVIDOR -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


