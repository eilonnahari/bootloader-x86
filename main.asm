BITS 16
org 0x7c00

CODE_SEG equ 0x08

start:
cli                         ;   Disable interrupts
xor ax, ax
mov ds, ax                  ; Reset Data segement register
lgdt [gdt_desc]             ; Load GDT

mov eax, cr0
or eax, 1
mov cr0, eax                ; Enable protected mode

jmp CODE_SEG:clear_pipe          ; Far jump to clear instruction pipeline from 16 bit instructions

clear_pipe:
mov ax, 0x10                 ; Set data and stack segments (code is set by the far jump)
mov ds, ax
mov ss, ax

mov esp, 090000h
Mov ax,0F01h            ;set ax to CGA character code (white smile)
Mov [0B8000h],ax      ;put ax on first character of CGA video
hang:
   jmp hang

gdt:

gdt_null:
dd 0
dd 0

gdt_code:
dw 0FFFFh                   ; Limit (4GB)
dw 0                        ; Base Address

db 0                        ; Base Address
db 10011010b                ; Type, Privelege Level, Present
db 11001111b                ; Limit (Byte), Reserved (2 bits), Size (bit), Granularity (Bit)
db 0                        ; Base Address


gdt_data:
dw 0FFFFh                   ; Limit (4GB)
dw 0                        ; Base Address

db 0                        ; Base Address
db 10010010b                ; Type, Privelege Level, Present
db 11001111b                ; Limit (Byte), Reserved (2 bits), Big (bit), Granularity (Bit)
db 0                        ; Base Address
;gdt_end:

gdt_desc:
dw gdt_desc - gdt
dd gdt


times 510 - ($ - $$) db 0  ; Pad with zeros for magic to be at 510
dw 0xAA55   ; Magic