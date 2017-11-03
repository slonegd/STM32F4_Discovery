##########################################################################################################################
# File automatically-generated by tool: [projectgenerator] version: [2.24.1] date: [Fri Aug 18 13:20:33 MSK 2017]
##########################################################################################################################

# ------------------------------------------------
# Generic Makefile (based on gcc)
#
# ChangeLog :
#	2017-02-10 - Several enhancements + project update mode
#   2015-07-22 - first version
# ------------------------------------------------

######################################
# target
######################################
TARGET = STM32F4_DISCOVERY


######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT = -O2


#######################################
# paths
#######################################
# source path
SOURCES_DIR =  
SOURCES_DIR += Application 
SOURCES_DIR += mcu_files 
SOURCES_DIR += mcu_files/CMSIS 
SOURCES_DIR += src 
SOURCES_DIR += src/usrlib
SOURCES_DIR += src/usrlib/uc_hal
SOURCES_DIR += src/usrlib/uc_hal/stm32f4_ral


# firmware library path
PERIFLIB_PATH = 

# Build path
BUILD_DIR = build

######################################
# source
######################################
# C sources
C_SOURCES = mcu_files/system_stm32f4xx.c 
 
# C++ sourses
CPP_SOURCES = 
CPP_SOURCES += src/main.cpp 


# ASM sources
ASM_SOURCES = mcu_files/startup_stm32f405xx.s


######################################
# firmware library
######################################
PERIFLIB_SOURCES = 


#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
#PREFIX = /home/slonegd/Code/gcc-arm-none-eabi-6-2017-q2-update/bin/arm-none-eabi-
#PREFIX = /home/dvk/code/gcc-arm-none-eabi-6-2017-q1-update/bin/arm-none-eabi-

CPP = $(PREFIX)g++
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
AR = $(PREFIX)ar
SZ = $(PREFIX)size
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 
#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m4

# fpu
FPU = -mfpu=fpv4-sp-d16

# float-abi
FLOAT-ABI = -mfloat-abi=hard

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS = -DSTM32F405xx


# AS includes
AS_INCLUDES = 

# C includes
C_INCLUDES =  
C_INCLUDES += -Imcu_files 
C_INCLUDES += -Imcu_files/CMSIS 
C_INCLUDES += -Isrc 
C_INCLUDES += -Isrc/usrlib 
C_INCLUDES += -Isrc/usrlib/uc_hal
C_INCLUDES += -Isrc/usrlib/uc_hal/stm32f4_ral


# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections 

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2 
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"


#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = mcu_files/STM32F405RGTx_FLASH.ld

# libraries
LIBS = -lc -lm -lnosys
LIBDIR =
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(CPP_SOURCES:.cpp=.o)))
vpath %.cpp $(sort $(dir $(CPP_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -std=c99 -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.cpp Makefile | $(BUILD_DIR) 
	$(CPP) -c $(CFLAGS) -std=c++1y -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.cpp=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir $@		

#######################################
# clean up
#######################################
clean:
	-rm -fR .dep $(BUILD_DIR)

flash_stlink:
#	/home/dvk/code/stlink/build/Release/st-flash write $(BUILD_DIR)/$(TARGET).bin 0x8000000
#	/home/slonegd/Code/stlink/build/Release/st-flash write $(BUILD_DIR)/$(TARGET).bin 0x8000000
	st-flash write $(BUILD_DIR)/$(TARGET).bin 0x8000000

util:
	/home/slonegd/Code/stlink/build/Release/src/gdbserver/st-util

debug: clean all flash_stlink util
  
#######################################
# dependencies
#######################################
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)

# *** EOF ***