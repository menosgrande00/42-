#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

int main()
{
    char *line;
    int i = 0;
    int fd;

    fd = open("test.txt", O_RDWR);
    while(i < 3)
    {
        line = get_next_line(fd);
        printf("%s", line);
        free(line);
        i++;
    }
    return (0);
}
