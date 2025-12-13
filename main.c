#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *get_next_line(int fd); // make sure to include your gnl header if needed

int main(void)
{
    int fd = open("test.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        return 1;
    }

    char *line;
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line); // line already contains '\n' if present
        free(line);
    }

    close(fd);
    return 0;
}