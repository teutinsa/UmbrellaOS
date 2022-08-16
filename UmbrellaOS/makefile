all: bin/UmbrellaOS.img

clear:
	del -q bin/

rebuild: clear bin/UmbrellaOS.img

bin/UmbrellaOS.img: bin/boot.bin bin/kernel.bin bin/zeros.bin
	cat $^ > $@

bin/boot.bin: src/boot/boot.asm
	nasm $< -f bin -o $@

bin/zeros.bin: src/boot/zeros.asm
	nasm $< -f bin -o $@

bin/kernel.bin: tmp/kernel_entry.o tmp/kernel.o
	i686-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

tmp/kernel_entry.o: src/kernel/kernel_entry.asm
	nasm $< -f elf -o $@

tmp/kernel.o: src/kernel/main.cpp
	i686-elf-gcc -ffreestanding -m32 -g -c $< -o $@