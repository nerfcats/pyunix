#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

double get_elapsed_time_ms();

void __print(const char* name, const char* text, const char* color_n, bool time)
{

    if (time == 1) 
    {
        if (color_n == "blue") {
            printf("[%f][\033[1m%s%s%s]: %s\n", get_elapsed_time_ms(), KBLU, name, KNRM, text);
        } else {
            printf("[%f][\033[1m%s%s%s]: %s\n", get_elapsed_time_ms(), KNRM, name, KNRM, text);
        }
    } else 
    {
        printf("[\033[1m%s%s]: %s\n", name, KNRM, text);
    }
}

