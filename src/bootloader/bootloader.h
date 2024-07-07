#ifndef BOOTLOADER_H_INCLUDED
#define BOOTLOADER_H_INCLUDED

void vwait();

// Bootloader calls
void bootloader_load_kernel();
void kernel_init();
void kernel_start();

void bootloader_load_kernel()
{
    printf("Loading PYunix kernel...");
    vwait();
    kernel_init();
    printf("done.\n\n");
    kernel_start();
}

#endif // BOOTLOADER_H_INCLUDED
