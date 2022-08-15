all: bin\\UmbrellaOS.img

bin\\UmbrellaOS.img: bin\\boot.bin
	type $^ > $@

bin\\boot.bin: src\\boot\\boot.asm
	nasm $< -f bin -o $@