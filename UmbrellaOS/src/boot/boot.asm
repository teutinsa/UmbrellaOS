[bits 16]
[org 0x7C00]

_start:
	mov [_BootDisk], dl

	xor ax, ax
	mov ds, ax
	mov es, ax
	mov ss, ax

	mov bp, 0x7BFF
	mov sp, bp

	push _TestString
	call Print

	push 0x7E00			; buffer
	push 1				; sectors to read
	push 2				; sector num
	call DiskRead
	jc .error

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

_TestString: db "Umbrella OS (C) 2022 Florian Schumacher", 13, 10, 0
_DiskErrorString: db "Disk read error!", 13, 10, 0
_BootDisk: db 0

times 510-($-$$) db 0
dw 0xAA55

_ExtraString: db "Extra string.", 13, 10, 0

times 1024-($-$$) db 0