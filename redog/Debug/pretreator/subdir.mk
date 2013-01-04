################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../pretreator/DataLoader.o \
../pretreator/TrainSetLoader.o \
../pretreator/UserIDTransfer.o 

CPP_SRCS += \
../pretreator/DataLoader.cpp \
../pretreator/TrainSetLoader.cpp \
../pretreator/UserIDTransfer.cpp 

OBJS += \
./pretreator/DataLoader.o \
./pretreator/TrainSetLoader.o \
./pretreator/UserIDTransfer.o 

CPP_DEPS += \
./pretreator/DataLoader.d \
./pretreator/TrainSetLoader.d \
./pretreator/UserIDTransfer.d 


# Each subdirectory must supply rules for building sources it contributes
pretreator/%.o: ../pretreator/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


