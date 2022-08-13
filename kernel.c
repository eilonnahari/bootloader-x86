
#include "ports.h"

const char rfc[] = "Hello Serial Port!!!!!!!!!!";
const char init[] = "Init Serial";

void kmain() {
   //asm volatile("hlt");
   //const char color = 0x1B;
   //const char* hello = "Hello from cpp file!";
   init_serial();
   serial_write_text(PORT, rfc, sizeof(rfc));
   unsigned char* vidmem = (unsigned char *)0xB8000;
   for (int i = 0; i < sizeof(init); i++)
   {
      *vidmem++ = init[i];
      *vidmem++ = 0xF;
   }
}