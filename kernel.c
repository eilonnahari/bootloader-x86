
#include "ports.h"
//#include "rfc_for_c.h"

const char welcome_str[] = "Inside Second Stage!";

void kmain() {
   unsigned char* video_mem = (unsigned char *)0xB8000;
   for (int i = 0; i < sizeof(welcome_str); i++)
   {
      *video_mem++ = welcome_str[i];
      *video_mem++ = 0xF;
   }
   if (init_serial(PORT) != 0) {
      serial_write_bytes(PORT, (unsigned char*)welcome_str, sizeof(welcome_str));
   }

   // Halt the CPU.
   asm volatile("hlt");
}