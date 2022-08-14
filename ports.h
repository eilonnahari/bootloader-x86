
#define PORT 0x3F8

int init_serial();
void serial_write_text(int serial_port, const unsigned char *text, int size);