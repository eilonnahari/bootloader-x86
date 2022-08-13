ENTRY(_kmain);
SECTIONS
{    
    . = 0x1000;    
    .text : AT(0x1000)
    {
        _text = .;
        *(.text);
        _text_end = .;
    }
    .data : AT(0x2000)
    {
        _data = .;
        *(.data);
        *(.rdata*);
        _data_end = .;
    }    
    /DISCARD/ :
    {
        *(.note*);
        *(.iplt*);
        *(.igot*);
        *(.rel*);
        *(.comment);
        /* add any unwanted sections spewed out by your version of gcc and flags here */    
    }
}