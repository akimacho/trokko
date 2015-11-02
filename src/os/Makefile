# ============================================================================
#   Name        : Makefile for operating system
# ============================================================================

PREFIX  = ~/Projects/trokko/tools
ARCH    = h8300-elf
BINDIR  = $(PREFIX)/bin
ADDNAME = $(ARCH)-

# specify the tool
AR      = $(BINDIR)/$(ADDNAME)ar
AS      = $(BINDIR)/$(ADDNAME)as
CC      = $(BINDIR)/$(ADDNAME)gcc
LD      = $(BINDIR)/$(ADDNAME)ld
NM      = $(BINDIR)/$(ADDNAME)nm
OBJCOPY = $(BINDIR)/$(ADDNAME)objcopy
OBJDUMP = $(BINDIR)/$(ADDNAME)objdump
RANLIB  = $(BINDIR)/$(ADDNAME)ranlib
STRIP   = $(BINDIR)/$(ADDNAME)strip

# compile source code
OBJS    = startup.o main.o
OBJS   += lib.o serial.o

# executable file
TARGET  = trokko

# compile options
CFLAGS  = -Wall -mh -nostdinc -nostdlib -fno-builtin
CFLAGS += -I.
CFLAGS += -Os
CFLAGS += -DTOROKKO

# link options
LFLAGS  = -static -T ld.scr -L.

.SUFFIXES: .c .o
.SUFFIXES: .s .o

all :           $(TARGET)

$(TARGET) :	$(OBJS)
		$(CC) $(OBJS) -o $(TARGET) $(CFLAGS) $(LFLAGS)
		cp $(TARGET) $(TARGET).elf
		$(STRIP) $(TARGET)

.c.o :		$<
		$(CC) -c $(CFLAGS) $<
        
.s.o :		$<
		$(CC) -c $(CFLAGS) $<

clean : 	
		rm -f $(OBJS) $(TARGET) $(TARGET).elf

