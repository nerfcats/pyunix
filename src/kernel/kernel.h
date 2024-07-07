#ifndef KERNEL_H_INCLUDED
#define KERNEL_H_INCLUDED

#include <stdbool.h> // for bool type
#include <stdio.h>   // for printf
#include <string.h>  // for strcpy
#include <stdlib.h>  // for exit

void vwait();
void terminal_kill_process(const char* process, bool is_kernel);

/*
Main kernel
Provides very basic system calls.
Add more functionality by adding another module and defining it in "setup.h"
*/

char kernel_state[] = "running";

// Formatted string variables for the system to use
char formatted_str[50];

#include "setup.h"
#include "init.h"
#include "proc_man.h"
#include "mem_man.h"
#include "dev_man.h"
#include "panic.h"
#include "text.h"

void kernel_init()
{
    // Initialize Kernel components
    strcpy(kernel_state, "running");
}

void kernel_start()
{
    __print("kernel", "Initializing", "blue", true);
    vwait();
    initramfs_load();
    kernel_switch_to_real_root_filesystem();
    init_system_start();
    __print("kernel", "Initialization complete", "blue", true);
    vwait();
}

void kernel_switch_to_real_root_filesystem()
{
    __print("kernel", "Switching to root filesystem", "blue", true);
    vwait();
}

void kernel_shutdown(bool reset)
{
    __print("kernel", "Shutting down system", "blue", true);
    __print("kernel", "Stopping services", "blue", true);
    vwait();
    
    // Weird bug in which the loop doesn't terminate all processes, run the loop 100 times to make sure all processes are terminated
    for (int i = 0; i < 100; i++) 
    {
        for (int i = 0; i < process_count; i++)
        {
            terminal_kill_process(processes[i].name, true);
        }
    }

    __print("kernel", "Unmounting filesystem", "blue", true);
    vwait();
    __print("kernel", "Ready to power off", "blue", true);
    strcpy(kernel_state, "stopped");
    if (!reset)
    {
        exit(0);
    }
    bios_initialize();
}

#endif // KERNEL_H_INCLUDED

