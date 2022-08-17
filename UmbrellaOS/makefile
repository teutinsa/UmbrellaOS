all: bin/UmbrellaOS.img

clear:
	rm -rfv bin/*
	rm -rfv tmp/*

rebuild: clear bin/UmbrellaOS.img

bin/UmbrellaOS.img: bin/boot.bin bin/kernel.bin bin/zeros.bin
	cat $^ > $@

bin/boot.bin: src/boot/boot.asm
	nasm $< -f bin -o $@

bin/zeros.bin: src/boot/zeros.asm
	nasm $< -f bin -o $@

tmp/kernel_entry.o: src/kernel/kernel_entry.asm
	nasm $< -f elf -o $@

bin/kernel.bin: tmp/kernel_entry.o tmp/kernel.o tmp/Terminal.o
	i686-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

tmp/kernel.o: src/kernel/main.cpp
	i686-elf-gcc -ffreestanding -g -c $^ -o $@

tmp/Terminal.o: src/kernel/Terminal.cpp
	i686-elf-gcc -ffreestanding -g -c $^ -o $@
