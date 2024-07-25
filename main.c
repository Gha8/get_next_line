#include <fcntl.h>
#include "get_next_line_bonus.h"
int main(void)
{
    int fd = open("empty",O_RDONLY);
    // int fd2 = open("main.c",O_RDONLY);
    
    int i = 0;
    while (i < 40)
    {
        char *str = get_next_line(fd);
        printf("%s", str);
        // char *str2= get_next_line(fd2);
        // printf("%s",str2);
        free(str);
        // free(str2);
        i++;
    }
}