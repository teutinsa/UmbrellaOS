[bits 64]
[extern kmain]

section .text

push 0x8000
call kmain
jmp $

outb:
	push rbp
	mov rbp, rsp

	mov rsp, rbp
	pop rbp
	ret

section .data


section .bss
