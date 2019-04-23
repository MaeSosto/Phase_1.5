# Cross toolchain variables
# If these are not in your path, you can make them absolute.
XT_PRG_PREFIX = mipsel-linux-gnu-
CC = $(XT_PRG_PREFIX)gcc
LD = $(XT_PRG_PREFIX)ld

# uMPS2-related paths

# Simplistic search for the umps2 install. prefix. If you have umps2
# installed on some weird location, set UMPS2_DIR_PREFIX by hand.
ifneq ($(wildcard /usr/bin/umps2),)
    UMPS2_DIR_PREFIX = /usr
else
    UMPS2_DIR_PREFIX = /usr/local
endif

#Data and include paths
ifneq ($(wildcard $(UMPS2_DIR_PREFIX)/lib/umps2),)
    UMPS2_LIB_DIR = $(UMPS2_DIR_PREFIX)/lib/umps2
else
    UMPS2_LIB_DIR = /usr/lib/x86_64-linux-gnu/umps2
endif

UMPS2_DATA_DIR = $(UMPS2_DIR_PREFIX)/share/umps2
UMPS2_INCLUDE_DIR = $(UMPS2_DIR_PREFIX)/include/umps2

# Compiler options
CFLAGS_LANG = -ffreestanding -ansi
CFLAGS_MIPS = -mips1 -mfp32 -std=gnu11 -fno-stack-protector
CFLAGS = $(CFLAGS_LANG) $(CFLAGS_MIPS) -I $(UMPS2_INCLUDE_DIR) -I. -Wall

#Toolchain flags
CC_FLAGS = -mips1 -mfp32 -std=gnu11 -w -I $(UMPS2_INCLUDE_DIR) -c
LD_FLAGS = -o kernel
EU_FLAGS = -k

#Objects paths
CRTSO_PATH = $(UMPS2_LIB_DIR)/crtso.o
LIBUMPS_PATH = $(UMPS2_LIB_DIR)/libumps.o
UMPSCORE_PATH = $(UMPS2_DATA_DIR)/umpscore.ldscript

# Linker options
LDFLAGS = -G0 -nostdlib -T $(UMPSCORE_PATH)

# Add the location of crt*.S to the search path
VPATH = $(UMPS2_DATA_DIR)

.PHONY : all clean

all : utils.o pcb.o handler.o kernel.o p15test_rikaya_v0.o kernel.core.umps

kernel.core.umps : kernel
	umps2-elf2umps -k $<

##mipsel-linux-gnu-gcc -ansi -mips1 -mfp32 -std=gnu11 -fno-stack-protector -I /usr/local/include/umps2 -c kernel.c
kernel.o : kernel.c
	$(CC) $(CC_FLAGS) $<
     
pcb.o : pcb.c pcb.h
	$(CC) $(CC_FLAGS) $<
	
p15test_rikaya_v0.o : p15test_rikaya_v0.c
	$(CC) $(CC_FLAGS) $<

handler.o : handler.c handler.h
	$(CC) $(CC_FLAGS) $<

utils.o : utils.c
	$(CC) $(CC_FLAGS) $<
	
#mipsel-linux-gnu-ld -o kernel pcb.o handler.o p15test_rikaya_v0.o kernel.o /usr/local/lib/umps2/crtso.o
# /usr/local/lib/umps2/libumps.o -nostdlib -G0 -T /usr/local/share/umps2/umpscore.ldscript
kernel : kernel.o 
	$(LD) -o $@ $^ $(CRTSO_PATH) $(LIBUMPS_PATH) $(LDFLAGS)

clean :
	-rm -f *.o kernel kernel.*.umps

# Pattern rule for assembly modules
%.o : %.S
	$(CC) $(CFLAGS) -c -o $@ $<
