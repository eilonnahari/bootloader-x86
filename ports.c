#include "ports.h"

#define PORT 0x3F8
#define COM2 0x2F8
#define COM3 0x3E8
#define COM4 0x2E8

#define NULL (0)

void outb(short unsigned int port, unsigned char value)
{
	asm volatile("outb %0, %1"
				 :
				 : "a"(value), "Nd"(port));
}

unsigned char inb(short unsigned int port)
{
	unsigned char ret;
	asm volatile("inb %1, %0"
				 : "=a"(ret)
				 : "Nd"(port));
	return ret;
}

int init_serial() {
   outb(PORT + 1, 0x00);    // Disable all interrupts
   outb(PORT + 3, 0x80);    // Enable DLAB (set baud rate divisor)
   outb(PORT + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
   outb(PORT + 1, 0x00);    //                  (hi byte)
   outb(PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
   outb(PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
   outb(PORT + 4, 0x0B);    // IRQs enabled, RTS/DSR set
   outb(PORT + 4, 0x1E);    // Set in loopback mode, test the serial chip
   outb(PORT + 0, 0xAE);    // Test serial chip (send byte 0xAE and check if serial returns same byte)
 
   // Check if serial is faulty (i.e: not same byte as sent)
   if(inb(PORT + 0) != 0xAE) {
      return 1;
   }
 
   // If serial is not faulty set it in normal operation mode
   // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
   outb(PORT + 4, 0x0F);
   return 0;
}

void serial_write_text(int serial_port, const char *text)
{
	while (text != 0)
	{
		while ((inb(serial_port + 5) & 0x20) == 0);
		outb(serial_port, *text);
        text++;
	}
}