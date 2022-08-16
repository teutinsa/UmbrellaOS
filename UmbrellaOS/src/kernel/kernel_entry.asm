[bits 64]
[extern kmain]
push 0x8000
call kmain
jmp $