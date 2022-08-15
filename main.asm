BITS 16
org 0x7c00

jmp start

CODE_SEG equ 0x08
DATA_SEG equ 0x10

GDT:
; Null descriptor
dd 0
dd 0

; Code descriptor
dw 0xFFFF                   ; Limit (4GB)
dw 0                        ; Base Address

db 0                        ; Base Address
db 10011010b                ; Type, Privelege Level, Present
db 11001111b                ; Limit (Byte), Reserved (2 bits), Size (bit), Granularity (Bit)
db 0                        ; Base Address

gdt_data:
dw 0xFFFF                   ; Limit (4GB)
dw 0                        ; Base Address

db 0                        ; Base Address
db 10010010b                ; Type, Privelege Level, Present
db 11001111b                ; Limit (Byte), Reserved (2 bits), Big (bit), Granularity (Bit)
db 0                        ; Base Address

GDT_DESC:
dw GDT_DESC - GDT -1
dd GDT

read_additional_sectors:
reset_drive:
    mov ah, 0
    int 0x13                ; The BIOS sets DL register for the number of the boot disk
    or ah, ah
    jnz reset_drive         ; If the call fails, then we assume the drive is not ready
    mov ax, 0           
    mov es, ax          
    mov bx, 0x1000
    mov ah, 02h
    mov al, 2Ch             ; Read 
    mov ch, 0
    mov cl, 02h
    mov dh, 0
    int 13h
    or ah, ah
    jnz reset_drive
    ret

start:
    cli                     ; Disable Interrupts
	xor	ax, ax				; Nullify segments
	mov	ds, ax

    call read_additional_sectors

    lgdt [GDT_DESC]         ; Load GDT

    ; Enable protected mode
    mov eax, cr0
    or eax, 1
    mov cr0, eax                

    jmp CODE_SEG:pmode_entry    ; Jump to protected mode

[BITS 32]
pmode_entry:
	mov ax, DATA_SEG
	mov ds, ax
	mov ss, ax
    mov ebp, 0x90000
    mov esp, 0x90000
    mov esi, prot_mod_wel
    call print_pmode
    jmp CODE_SEG:0x1000     ; Jump to our second stage C code.

; Prints a null terminated ASCII string
print_pmode:
    mov edi, 0xB8000
.loop:
    lodsb
    or al, al
    jz .end
    mov byte [edi], al
    inc edi
    mov byte [edi], 0x1B            ; Cyan Background
    inc edi
    jmp .loop
.end:
    ret

prot_mod_wel db "Im in Protected Mode!", 0

times 510 - ($ - $$) db 0  ; Pad with zeros for magic to be at 510
dw 0xAA55   ; Magic