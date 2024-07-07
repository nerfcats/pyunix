#ifndef PANIC_H_INCLUDED
#define PANIC_H_INCLUDED

void vwait();

void kernel_panic(const char* reason)
{
    /*
    Print panic reason
    List devices from device manager
    Hang the system
    */
    vwait();
    printf("\n-[ KERNEL PANIC START\n");
    printf("KERNEL PANIC! ):\n");
    printf("Kernel panic - not syncing: %s\n\n", reason);
    // Additional actions to handle kernel panic can be added here
    vwait();
    device_manager_list_devices();
    printf("Version string: %s\n", version);
    printf("Dumping memory\n");
    for (int i = 0; i < process_count; i++)
    {
        printf("  - %s: %dMB\n", processes[i].name, processes[i].memory_size);
    }
    printf("Please report this error on Github if possible!\n");
    printf("\nKERNEL PANIC END ]-\n");

    // Hang the system to prevent other stuff from happening
    for (;; )
    {
        usleep(1);
    }
}

void kernel_oops(const char* reason)
{
    vwait();
    printf("\nKernel oops! O:\n");
    printf("Kernel oops -  %s\n\n", reason);
    // Additional actions to handle kernel panic can be added here
    vwait();
    device_manager_list_devices();
    printf("Version string: %s\n", version);
    printf("Dumping memory\n");
    for (int i = 0; i < process_count; i++)
    {
        printf("  - %s: %dMB\n", processes[i].name, processes[i].memory_size);
    }
    printf("Please report this error on Github if possible!\n");
    printf("\nPress ENTER to continue (things may break)\n");
    getchar();
}

#endif // PANIC_H_INCLUDED
