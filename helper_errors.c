#include "cub_3d.h"

int errOpen(char *file)
{
    int fd;

    fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        perror("Error\nFailed to open file\n");
        return (-1);  // Return a non-zero value to indicate an error
    }
    return (fd);
}
