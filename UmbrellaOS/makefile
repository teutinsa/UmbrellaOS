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
	nasm $< -f elf64 -o $@

bin/kernel.bin: tmp/kernel_entry.o tmp/kernel.o tmp/Terminal.o tmp/String.o tmp/Utils.o tmp/Memory.o
	x86_64-elf-ld -o $@ -T link.ld $^

tmp/kernel.o: src/kernel/main.c
	x86_64-elf-gcc -ffreestanding -m64 -g -c $^ -o $@

tmp/Terminal.o: src/kernel/Terminal.c
	x86_64-elf-gcc -ffreestanding -m64 -g -c $^ -o $@

tmp/Terminal.o: src/kernel/Terminal.c
	x86_64-elf-gcc -ffreestanding -m64 -g -c $^ -o $@

tmp/String.o: src/kernel/String.c
	x86_64-elf-gcc -ffreestanding -m64 -g -c $^ -o $@

tmp/Utils.o: src/kernel/Utils.c
	x86_64-elf-gcc -ffreestanding -m64 -g -c $^ -o $@

tmp/Memory.o: src/kernel/Memory.c
	x86_64-elf-gcc -ffreestanding -m64 -g -c $^ -o $@