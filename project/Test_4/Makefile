# makfile configuration
COMMON_OBJECTS  = main.o
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h
LDFLAGS		= -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as



all: main.elf

#additional rules for files
main.elf: ${COMMON_OBJECTS} main.o assy.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

load: main.elf
	msp430loader.sh main.elf

main.o: assy.h


clean:
	rm -f *.o *.c~ *.h~ *~ *.c# *.elf
