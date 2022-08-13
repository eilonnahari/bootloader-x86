
#include "ports.h"

const char rfc[] = "Hello Serial Port";
const char rfc[] = "Hello Serial Port";

void kmain() {
   //asm volatile("hlt");
   //const char color = 0x1B;
   //const char* hello = "Hello from cpp file!";
   unsigned char *vidmem = (unsigned char *)0xB8000;
   for (int i = 0; i < sizeof(rfc); i++)
   {
      *vidmem++ = rfc[i];
      *vidmem++ = 0xF;
   }
   init_serial();
   serial_write_text(PORT, rfc);
}