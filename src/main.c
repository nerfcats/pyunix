#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <sys/time.h>

#include "bios/bios.h"
#include "bootloader/bootloader.h"
#include "kernel/kernel.h"
#include "terminal/terminal.h"

// Global variable to store the start time
struct timeval start_time;

void vwait()
{
    // Adds a simulated delay running everything. Comment the following code to disable.
    // srand(time(NULL));
    // usleep((rand() % 50000) + 50000);
}

// Function to record the start time
void record_start_time() {
    gettimeofday(&start_time, NULL);
}

// Function to get the elapsed time in seconds
double get_elapsed_time_ms() {
    struct timeval current_time;
    gettimeofday(&current_time, NULL);

    // Calculate elapsed time in seconds
    double elapsed_time = (current_time.tv_sec - start_time.tv_sec);      // seconds

    elapsed_time += (current_time.tv_usec - start_time.tv_usec) / 1000000.0;   // microseconds to seconds
    return elapsed_time;
}

int main()
{
    record_start_time();

    bios_initialize(); // Initialize the system and start the kernel

    // Add devices
    device_manager_add_device("Terminal");
    device_manager_list_devices();

    // Start the terminal
    terminal_start();

    // Shutdown the system if loop broke
    __print("kernel", "Terminal exited", "blue", true);
    kernel_shutdown(false);
    return 0;
}
