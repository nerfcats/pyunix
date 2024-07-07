#ifndef DEV_MAN_H_INCLUDED
#define DEV_MAN_H_INCLUDED

void vwait();

void device_initialize(const char* name)
{
    printf("Device %s: Initialized\n", name);
    vwait();
}

void device_manager_add_device(const char* name)
{
    strcpy(devices[device_count], name);
    device_count++;
    device_initialize(name);
}

void device_manager_list_devices()
{
    sprintf(formatted_str, "Listing devices...");
    __print("DeviceServer", formatted_str, "none", false);
    for (int i = 0; i < device_count; i++)
    {
        printf("- %s\n", devices[i]);
    }
}

#endif // DEV_MAN_H_INCLUDED
