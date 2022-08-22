[bits 16]
[org 0x7C00]

KERNEL_LOC equ 0x8FD0

_start:
	mov [_BootDisk], dl
	
	xor ax, ax
	mov ds, ax
	mov es, ax
	mov ss, ax

	mov bp, 0x7BFF
	mov sp, bp

	push 0x7E00			; buffer
	push 1				; sectors to read
	push 2				; sector num
	call DiskRead
	jc .error

	push ebx
	pushfd
	pop eax
	mov ebx, eax
	xor eax, 0x200000
	push eax
	popfd
	pushfd
	pop eax
	cmp eax, ebx
	jnz .supported
	push _CpuErrorString
	call Print
	jmp .error
	.supported:

	mov eax, 0x80000000
	cpuid
	cmp eax, 0x80000001
	jb .no64
	mov eax, 0x80000001
	cpuid
	test edx, 1 << 29
	jnz .is64
	.no64:
	push _64ErrorString
	call Print
	jmp .error
	.is64:
	
	push 0x8000
	call MapMem
	
	push KERNEL_LOC		; buffer
	push 8				; sectors to read
	push 3				; sector num
	call DiskRead
	jc .error
	
	cli
	lgdt [GDT_descriptor]
	mov eax, cr0
	or eax, 1
	mov cr0, eax
	jmp CODE_SEG:protected_mode

	.error:
	jmp $

Print:
	push bp
	mov bp, sp
	mov bx, [bp+4]
	mov ah, 0x0E
	.loop:
	mov al, [bx]
	cmp al, 0
	je .end
	int 0x10
	inc bx
	jmp .loop
	.end:
	mov sp, bp
	pop bp
	ret 2

DiskRead:
	push bp
	mov bp, sp
	mov ah, 0x02
	mov al, [bp+6]
	mov ch, 0
	mov cl, [bp+4]
	mov dh, 0
	mov dl, [_BootDisk]
	mov bx, [bp+8]
	int 0x13
	jnc .end
	push _DiskErrorString
	call Print
	.end:
	mov sp, bp
	pop bp
	ret 6

MapMem:
	push bp
	mov bp, sp
	mov si, [bp+4]
	mov di, [bp+4]
	add di, 4
	xor ebx, ebx
	mov edx, 0x0534D4150
	mov eax, 0xE820
	mov [di+20], dword 1
	mov ecx, 24
	int 0x15
	jc .failed

	mov edx, 0x0534D4150
	cmp eax, edx
	jne .failed
	test ebx, ebx
	je .failed

	.loop:
		mov eax, 0xE820
		mov [di+20], dword 1
		mov ecx, 24
		int 0x15
		jc .finish
		mov edx, 0x0534D4150

		.jmpin:
		jcxz .skip
		cmp cl, 20
		jbe .notext
		test byte [di+20], 1
		je .skip
		
		.notext:
		mov ecx, [di+8]
		or ecx, [di+12]
		jz .skip
		inc dword [si]
		add di, 24
		
		.skip:
		test ebx, ebx
		jne .loop
		
		.finish:
		clc
		jmp .end
	.failed:
	push _MemErrorString
	call Print
	stc
	jmp .end
	.end:
	mov sp, bp
	pop bp
	ret 2

_BootDisk: db 0
_DiskErrorString: db "Disk read error!", 13, 10, 0
_MemErrorString: db "Memory mapping failed!", 13, 10, 0
_CpuErrorString: db "CPUID not supported!", 13, 10, 0
_64ErrorString: db "x64 bits not supported!", 13, 10, 0

CODE_SEG equ GDT_code - GDT_start
DATA_SEG equ GDT_data - GDT_start

GDT_start:
    GDT_null:
        dd 0x0
        dd 0x0
    GDT_code:
        dw 0xffff
        dw 0x0
        db 0x0
        db 0b10011010
        db 0b11001111
        db 0x0
    GDT_data:
        dw 0xffff
        dw 0x0
        db 0x0
        db 0b10010010
        db 0b11001111
        db 0x0
GDT_end:

GDT_descriptor:
    dw GDT_end - GDT_start - 1
    dd GDT_start

times 510-($-$$) db 0
dw 0xAA55

[bits 32]
protected_mode:
	mov ax, DATA_SEG
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	mov ebp, 0x90000
	mov esp, ebp

	call Clear
	
	mov ebx, VGA_MEM
	mov byte [ebx], 'P'
	inc ebx
	mov byte [ebx], 14

	mov eax, cr0
	and eax, ~(1 << 31)
	mov cr0, eax

	mov edi, 0x1000
	mov cr3, edi
	xor eax, eax
	mov ecx, 4096
	rep stosd
	mov edi, cr3

	mov dword [edi], 0x2003
	add edi, 0x1000
	mov dword [edi], 0x3003
	add edi, 0x1000
	mov dword [edi], 0x4003
	add edi, 0x1000
	mov ebx, 0x00000003
	mov ecx, 512

	.set_entry:
	mov dword [edi], ebx
	add ebx, 0x1000
	add edi, 8
	loop .set_entry

	mov eax, cr4
	or eax, 1 << 5
	mov cr4, eax

	mov ecx, 0xC0000080
	rdmsr
	or eax, 1 << 8
	wrmsr

	mov eax, cr0
	or eax, 1 << 31
	mov cr0, eax

	lgdt [GDT.Pointer]
	jmp GDT.Code:long_mode

	jmp $

Clear:
	push ebp
	mov ebp, esp
	mov ecx, VGA_SIZE
	mov eax, VGA_MEM
	.loop:
	mov byte [eax], 0
	inc eax
	loop .loop
	mov esp, ebp
	pop ebp
	ret

PRESENT			equ 1 << 7
NOT_SYS			equ 1 << 4
EXEC			equ 1 << 3
RW				equ 1 << 1
ACCESSED		equ 1 << 0

GRAN_4K			equ 1 << 7
SZ_32			equ 1 << 6
LONG_MODE		equ 1 << 5

GDT:
	.Null: equ $ - GDT
		dq 0
	.Code: equ $ - GDT
		dd 0xFFFF
		db 0
		db PRESENT | NOT_SYS | EXEC | RW
		db GRAN_4K | LONG_MODE | 0xF
		db 0
	.Data: equ $ - GDT
		dd 0xFFFF
		db 0
		db PRESENT | NOT_SYS | RW
		db GRAN_4K | SZ_32 | 0xF
		db 0
	.TSS: equ $ - GDT
		dd 0x00000068
		dd 0x00CF8900
	.Pointer:
		dw $ - GDT - 1
		dq GDT

[bits 64]
long_mode:
	cli
	mov ax, GDT.Data
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	mov rbx, VGA_MEM
	mov byte [rbx], 'L'
	inc rbx
	mov byte [rbx], 2

	jmp KERNEL_LOC

VGA_MEM equ 0xB8000
VGA_WIDTH equ 80
VGA_HEIGHT equ 25
VGA_STRIDE equ 2
VGA_SIZE equ VGA_WIDTH * VGA_STRIDE * VGA_HEIGHT
VGA_LENGTH equ VGA_WIDTH * VGA_HEIGHT

times 1024-($-$$) db 0