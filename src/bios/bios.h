#ifndef BIOS_H_INCLUDED
#define BIOS_H_INCLUDED

// BIOS calls
void bios_initialize();
void load_kernel();
void bootloader_load_kernel();

void bios_initialize()
{
    bootloader_load_kernel();
}

#endif // BIOS_H_INCLUDED
