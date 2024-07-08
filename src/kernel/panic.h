#ifndef PANIC_H_INCLUDED
#define PANIC_H_INCLUDED

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <execinfo.h>  // Include for backtrace functions
#include <sys/sysinfo.h>

void vwait();

// Function to get total memory usage
int get_total_memory_usage() {
    struct sysinfo info;
    sysinfo(&info);
    return (info.totalram - info.freeram) / (1024 * 1024);
}

// Function to get CPU information
void get_cpu_info(char* cpu_name, int* cores, int* speed_mhz) {
    FILE* fp;
    char buffer[128];

    // Get CPU name
    fp = fopen("/proc/cpuinfo", "r");
    if (fp != NULL) {
        while (fgets(buffer, sizeof(buffer), fp)) {
            if (strncmp(buffer, "model name", 10) == 0) {
                strcpy(cpu_name, strchr(buffer, ':') + 2);
                cpu_name[strlen(cpu_name) - 1] = '\0'; // Remove the newline character
                break;
            }
        }
        fclose(fp);
    }

    // Get number of cores
    *cores = sysconf(_SC_NPROCESSORS_ONLN);

    // Get CPU speed
    fp = fopen("/proc/cpuinfo", "r");
    if (fp != NULL) {
        while (fgets(buffer, sizeof(buffer), fp)) {
            if (strncmp(buffer, "cpu MHz", 7) == 0) {
                *speed_mhz = (int)strtof(strchr(buffer, ':') + 2, NULL);
                break;
            }
        }
        fclose(fp);
    }
}

void kernel_panic(const char* reason)
{
    const char* panic_reason = reason;
    vwait();
    printf("\n-[ kernel panic: %s\n", panic_reason);
    printf("KERNEL PANIC! ):\n");
    printf("Kernel panic - not syncing: %s\n\n", reason);

    // Print CPU information
    char cpu_name[128];
    int cores, speed_mhz;
    get_cpu_info(cpu_name, &cores, &speed_mhz);
    printf("CPU Name: %s\n", cpu_name);
    printf("CPU Cores: %d\n", cores);
    printf("CPU Speed: %d MHz\n", speed_mhz);

    // Print memory usage of the program
    printf("Total Memory Usage: %d MB\n", get_total_memory_usage());

    // Backtrace and symbols
    void* callstack[128];
    int frames = backtrace(callstack, 128);
    char** strs = backtrace_symbols(callstack, frames);
    if (strs != NULL) {
        printf("Backtrace:\n");
        for (int i = 0; i < frames; ++i) {
            printf("  %s\n", strs[i]);
        }
        free(strs);
    }

    vwait();
    device_manager_list_devices();
    printf("Version string: %s\n", version);
    printf("Dumping memory\n");
    for (int i = 0; i < process_count; i++)
    {
        printf("  - %s: %dMB\n", processes[i].name, processes[i].memory_size);
    }
    printf("Please report this error on Github if possible!\n");
    printf("\n-[ end kernel panic: %s\n", panic_reason);

    __print("kernel", "Hanging system due to kernel panic. Ctrl+C to exit.", "blue", true);

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
