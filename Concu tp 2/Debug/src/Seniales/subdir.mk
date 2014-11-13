################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Seniales/SignalHandler.cpp 

OBJS += \
./src/Seniales/SignalHandler.o 

CPP_DEPS += \
./src/Seniales/SignalHandler.d 


# Each subdirectory must supply rules for building sources it contributes
src/Seniales/%.o: ../src/Seniales/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DCLIENTE -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


