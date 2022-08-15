#include "ports.h"

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

int init_serial(int serial_port) {
   outb(serial_port + 1, 0x00);    // Disable all interrupts
   outb(serial_port + 3, 0x80);    // Enable DLAB (set baud rate divisor)
   outb(serial_port + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
   outb(serial_port + 1, 0x00);    //                  (hi byte)
   outb(serial_port + 3, 0x03);    // 8 bits, no parity, one stop bit
   outb(serial_port + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
   outb(serial_port + 4, 0x0B);    // IRQs enabled, RTS/DSR set
   outb(serial_port + 4, 0x1E);    // Set in loopback mode, test the serial chip
   outb(serial_port + 0, 0xAE);    // Test serial chip (send byte 0xAE and check if serial returns same byte)
 
   // Check if serial is faulty (i.e: not same byte as sent)
   if(inb(serial_port + 0) != 0xAE) {
      return 1;
   }
 
   // If serial is not faulty set it in normal operation mode
   // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
   outb(serial_port + 4, 0x0F);
   return 0;
}

void serial_write_bytes(int serial_port, const unsigned char *bytes, int size)
{
	for (int i = 0; i < size; i++)
	{
		while ((inb(serial_port + 5) & 0x20) == 0);
		outb(serial_port, bytes[i]);
	}
}