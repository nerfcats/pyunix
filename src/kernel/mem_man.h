#ifndef MEM_MAN_H_INCLUDED
#define MEM_MAN_H_INCLUDED

void vwait();

void memory_manager_allocate(const char* name, int size)
{
    for (int i = 0; i < process_count; i++)
    {
        if (strcmp(processes[i].name, name) == 0)
        {
            processes[i].memory_size = size;
            break;
        }
    }
    sprintf(formatted_str, "Allocated %dMB to %s", size, name);
    __print("MemoryServer", formatted_str, "none", false);
}

void memory_manager_free(const char* name)
{
    for (int i = 0; i < process_count; i++)
    {
        if (strcmp(processes[i].name, name) == 0)
        {
            processes[i].memory_size = 0;
            break;
        }
    }
    sprintf(formatted_str, "Freed memory from %s", name);
    __print("MemoryServer", formatted_str, "none", false);
}

#endif // MEM_MAN_H_INCLUDED
