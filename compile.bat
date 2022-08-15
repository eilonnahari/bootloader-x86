"C:\Program Files\NASM\nasm.exe" main.asm -f bin -o boot.bin

gcc -c -g -Os -m32 -ffreestanding -nostdlib -lgcc -Wall -Werror -I. -o kernel.o kernel.c
gcc -c -g -Os -m32 -ffreestanding -nostdlib -lgcc -Wall -Werror -I. -o ports.o ports.c
ld -m i386pe -Tlinker.ld -static -nostdlib --nmagic -o kernel.elf kernel.o ports.o
objcopy -O binary kernel.elf kernel.bin   
copy /B boot.bin+kernel.bin final.bin