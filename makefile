# SPI Ionia Comprehensive Makefile
# Southeastern Policy Institute, 2023

# Project Name and Version
IONIA_NAME:= IONIA
IONIA_VER := 0x0003

# Debug Flag
DEBUG     := DEBUG

# Project Definitions
DEFS      := $(DEBUG) IONIA_VER=$(IONIA_VER) _IONIA=\"$(IONIA_NAME)\"
UNDEFS    := UNICODE _UNICODE

# Commands
PREFIX    := i686-linux-gnu-
AR        := $(PREFIX)ar
AS        := nasm
CC        := $(PREFIX)gcc
CPP       := $(PREFIX)g++
LD        := $(PREFIX)ld
STRIP     := $(PREFIX)strip

# Directories
SRCDIR    := src
INCDIR    := inc
BINDIR    := bin
OBJDIR    := obj
RESDIR    := res
LIBDIR    := lib

# Output File
OUTPUT    := $(BINDIR)/$(shell echo $(IONIA_NAME) | tr A-Z a-z).img

# Source Files
SRC       := $(wildcard $(SRCDIR)/*/*.*)

# Intermediate Files
OBJ       := $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SRC:.cpp=.o))
OBJ       := $(OBJ:.c=.o)
OBJ       := $(OBJ:.asm=.o)

# Sub-projects
REQS      := $(filter-out kernel boot,\
             $(subst $(SRCDIR)/,,$(wildcard $(SRCDIR)/*)))
BOOT      := $(filter $(OBJDIR)/boot/%,$(OBJ))
KERNEL    := $(filter $(OBJDIR)/kernel/%,$(OBJ))

# Required Libraries
LIBS      := idt c cxx crt

# All of the intermediate and output files (for cleanup later)
CLEAN     := $(OBJ) $(OUTPUT) $(REQS:%=$(LIBDIR)/lib%.a)

# To make sure things get linked in the correct order
LINK_LIST := $(BOOT) $(KERNEL) $(REQS:%=$(LIBDIR)/lib%.a)

# Flags
ASFLAGS   := -f elf
CFLAGS    := -c -O -ffreestanding -Wall -x c -std=gnu20 -fno-pie \
             -fno-asynchronous-unwind-tables -fno-exceptions \
             $(INCDIR:%=-I%) $(DEFS:%=-D%) $(UNDEFS:%=-U%)
CPPFLAGS  := -c -O -nostdinc++ -std=c++11 -ffreestanding -Wall -fno-pie \
             -fno-asynchronous-unwind-tables -fcheck-new -fno-exceptions \
             $(INCDIR:%=-I%) $(DEFS:%=-D%) $(UNDEFS:%=-U%)
LDFLAGS   := -nostdlib -Bsymbolic \
             $(LIBDIR:%=-L%) -T$(RESDIR)/link.ld

# Rules
.PHONY : all clean test

# C++ Sources
$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@echo "===== \e[91m$@\e[39m ====="
	$(CPP) $(CPPFLAGS) -o $@ $<

# C Sources
$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@echo "===== \e[91m$@\e[39m ====="
	$(CC) $(CFLAGS) -o $@ $<

# Assembler Sources
$(OBJDIR)/%.o : $(SRCDIR)/%.asm
	@echo "===== \e[96m$@\e[39m ====="
	$(AS) $(ASFLAGS) -o $@ $<

# Sub-project archives
$(LIBDIR)/lib%.a : $(OBJ)
	@echo "===== \e[94m$@\e[39m ====="
	$(AR) rcs $@ $(filter $(OBJDIR)/$(patsubst $(LIBDIR)/lib%.a,%,$@)/%,$^)

# Project Image
$(BINDIR)/%.img : $(LINK_LIST)
	@echo "===== \e[92m$@\e[39m ====="
	$(LD) $(LDFLAGS) $(filter-out %.a,$^) $(LIBS:%=-l%) -o $@

all : $(OUTPUT)
	@echo "\e[92mDone\e[39m"!

test : $(OUTPUT)
	qemu-system-i386 -fda $(OUTPUT)

clean :
	@clear
	@echo "===== \e[92mCleaning...\e[39m ====="
	$(RM) $(CLEAN)
