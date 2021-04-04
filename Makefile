PROJECT = lpc_strarter

SOURCES := ./src/main.c 
SOURCES += ./core/cmsis/driver_library/src/lpc17xx_gpio.c
SOURCES += ./core/cmsis/driver_library/src/lpc17xx_libcfg_default.c


DEVICE_OBJECTS = ./core/device/src/system_LPC17xx.o ./core/device/src/startup_ARMCM3.o
OBJECTS = $(SOURCES:.c=.o) $(DEVICE_OBJECTS)

INCLUDE_PATHS = -I. -I./core -I./core/cmsis/inc -I./core/device/inc -I./core/cmsis/driver_library/inc

LINKER_SCRIPT = ./LPC1768.ld


AS      = arm-none-eabi-as
CC      = arm-none-eabi-gcc
CPP     = arm-none-eabi-g++
LD      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

CPU = -mcpu=cortex-m3 -mthumb

CC_FLAGS = $(CPU) -c -Os -fno-common -fmessage-length=0 -Wall -fno-exceptions -ffunction-sections -fdata-sections 

LD_FLAGS = $(CPU) -Wl,--gc-sections --specs=nano.specs 
LD_SYS_LIBS = -lm -lc -lgcc -lnosys

all: $(PROJECT).bin


clean:
	rm -f $(PROJECT).bin $(PROJECT).elf $(OBJECTS)

.s.o:
	$(AS) $(CPU) -o $@ $<

.c.o:
	$(CC)  $(CC_FLAGS) $(CC_SYMBOLS) -std=gnu99   $(INCLUDE_PATHS) -o $@ $<

.cpp.o:
	$(CPP) $(CC_FLAGS) $(CC_SYMBOLS) -std=gnu++98 $(INCLUDE_PATHS) -o $@ $<


$(PROJECT).elf: $(OBJECTS) $(SYS_OBJECTS)
	$(LD) $(LD_FLAGS) -T$(LINKER_SCRIPT) $(LIBRARY_PATHS) -o $@ $^ $(LIBRARIES) $(LD_SYS_LIBS) 

$(PROJECT).bin: $(PROJECT).elf
	$(OBJCOPY) -O binary $< $@