# makfile configuration
COMMON_OBJECTS  = main.o  # Wdinterrupthandler.o
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h
LDFLAGS		= -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: light.elf

#additional rules for files
light.elf: ${COMMON_OBJECTS}
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ ../lib/Library.a

load: light.elf
	msp430loader.sh light.elf

clean:
	rm -f *.o *.elf

main.o: light.h

wdInterruptHandler.o:  light.h
