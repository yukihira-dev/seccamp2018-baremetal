CFLAGS=-mfloat-abi=soft -mlittle-endian
CFLAGS+=-fno-builtin -nostartfiles -std=c11 -O0 -g
LDFLAGS=-static -nostdlib
CC=arm-unknown-eabi-gcc
LD=arm-unknown-eabi-ld

myprog.bin: myprog.elf
	arm-unknown-eabi-objcopy -O binary $^ $@

myprog.elf: ldscript.lds start.o main.o deep.o
	$(LD) $(LDFLAGS) -T ldscript.lds start.o main.o deep.o -L/home/yukihira/x-tools/arm-unknown-eabi/arm-unknown-eabi/lib -lm -lc `$(CC) -print-libgcc-file-name` -o $@

main.o: main.c
	$(CC) $(CFLAGS) -lm -lgcc -lc -c -o $@ $^

deep.o: deeplearning.c
	$(CC) $(CFLAGS) -lm -lgcc -lc -c -o $@ $^

start.o: start.S
	$(CC) $(CFLAGS) -c -o $@ $^

all: myprog.bin

clean:
	rm myprog.bin myprog.elf main.o start.o
