#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

void vwait();

void initramfs_load()
{
    sprintf(formatted_str, "Loading initial RAM disk...");
    __print("initramfs", formatted_str, "none", false);
    vwait();
}

void init_system_start()
{
    sprintf(formatted_str, "Starting system services and processes...");
    __print("init", formatted_str, "none", false);
    vwait();
    init_system_create_startup_processes();
    process_manager_schedule();
}

void init_system_create_startup_processes()
{
    process_manager_create_process("init");
    memory_manager_allocate("init", 32);
    process_manager_create_process("MemoryServer");
    memory_manager_allocate("MemoryServer", 64);
    process_manager_create_process("ProcessServer");
    memory_manager_allocate("ProcessServer", 32);
}

#endif // INIT_H_INCLUDED
