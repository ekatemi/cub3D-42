#include "mlx_linux/mlx.h"
#include "libft/libft.h"
#include "cub_3d.h"

int is_empty_or_whitespace(char *str)
{
    if (str == NULL)
        return (1);
    
    while (*str)
    {
        if (*str != ' ' && *str != '\f' && *str != '\r' && *str != '\t'
            && *str != '\v' && *str != '\n') // Check for non-whitespace characters
            return (0);
        str++;
    }
    return (1); //all whitespace
}


//int fillMatrix

int main(int argc, char **argv)
{
    char *file = getFilename(argc, argv);
    if (!file)
        return (1);
        
    int     fd;
    char    *result;
    //char    **matrix;
    
    fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        perror("Error\nFailed to open file\n");
        return (1);  // Return a non-zero value to indicate an error
    }
    result = get_next_line(fd); //if result is empty line skip to next
    //printf("Result is %s\n", result);
    while (result)	
    {
        if (is_empty_or_whitespace(result))
        {
            free(result);
            result = get_next_line(fd);  // Continue to the next line
            continue;
        }
        printf("RESULT--->>>%s", result);
        free(result);
        result = get_next_line(fd);
    }
    free(result);
    close(fd);
    return (0);
}