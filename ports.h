
#define PORT 0x3F8

/*
    Initialize a serial port.

    @param serial_port  The serial port number.

    @return  0 for success, otherwise return 1.
*/
int init_serial(int serial_port);

/*
    Write a buffer to a serial port.

    @param serial_port  The serial port number.
    @param bytes        The buffer address.
    @param size         The buffer size.
*/
void serial_write_bytes(int serial_port, const unsigned char* bytes, int size);