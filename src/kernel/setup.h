#ifndef SETUP_H_INCLUDED
#define SETUP_H_INCLUDED

/*
Kernel Setup
Sets kernel calls and prepares other stuff
*/

void vwait();

const char version[] = "PYunix microkernel v0.3.1-alpha";

// Kernel calls
void kernel_init();
void kernel_start();
void kernel_switch_to_real_root_filesystem();
void kernel_shutdown(bool reset);
void kernel_panic(const char* reason);
void kernel_oops(const char* reason);

void initramfs_load();
void init_system_start();
void init_system_create_startup_processes();

void process_manager_create_process(const char* name);
void process_manager_schedule();
void process_run(const char* name);
void process_wait(const char* name);
void process_allocate_memory(const char* name, int size);
void process_deallocate_memory(const char* name);

void memory_manager_allocate(const char* name, int size);
void memory_manager_free(const char* name);

void device_initialize(const char* name);
void device_manager_add_device(const char* name);
void device_manager_list_devices();

void clear_scr();
void __print(const char* name, const char* text, const char* color_n, bool time);

void clear_scr()
{
  const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
  write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 11);
}

typedef struct
{
    char name[50];
    char state[10];
    int memory_size;
} Process;

Process processes[100];
int process_count = 0;
int memory_allocations[100];
int device_count = 0;
char devices[100][50];

#endif // SETUP_H_INCLUDED
