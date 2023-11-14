# makfile configuration
COMMON_OBJECTS  = main.o
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h
LDFLAGS		= -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as


all: light.elf

#additional rules for files
light.elf: ${COMMON_OBJECTS} main.o StateMachine.o light.o switch.o ../lib/Library.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

load: light.elf
	msp430loader.sh light.elf

main.o: light.h StateMachine.h switch.h

light.o: light.c light.h

switch.o: StateMachine.h

StateMachine.o: light.h stateMachine.h

clean:
	rm -f *.o *.elf
