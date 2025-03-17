#include "mlx_linux/mlx.h"
#include "libft/libft.h"
#include "cub_3d.h"

// int is_empty_or_whitespace(char *str)
// {
//     if (str == NULL)
//         return (1);
    
//     while (*str)
//     {
//         if (*str != ' ' && *str != '\f' && *str != '\r' && *str != '\t'
//             && *str != '\v' && *str != '\n') // Check for non-whitespace characters
//             return (0);
//         str++;
//     }
//     return (1); //all whitespace
// }


//int fillMatrix

int main(int argc, char **argv)
{
    char *file = getFilename(argc, argv);
    if (!file)
        return (1);
        
    int     fd;
    char    *result;
    //char    **matrix;
    
    fd = errOpen(file);
    if (fd == -1)
    {
       return (1); 
    }
    
    result = get_next_line(fd); //if result is empty line skip to next
    //printf("Result is %s\n", result);
    while (result)	
    {
        // if (is_empty_or_whitespace(result))
        // {
        //     free(result);
        //     result = get_next_line(fd);  // Continue to the next line
        //     continue;
        // }
        printf("RESULT--->>>%s", result);
        /*if not empty:
            define first chars (NO SO WE EA F C)
            skip spaces
            also check duplicated coordinates(if (!struct.NO) NO = "path" else err dupl)
            check the structure: path to file / r,g,b from 0 to 255
            fill structs
            if line is only 111111 it is start of the map
            /flag inside map = 1
            if flag inside map and empty line == error
            if line is 111111 and next lines are empty or eof is end of map
        */
        free(result);
        result = get_next_line(fd);
    }
    free(result);
    close(fd);
    return (0);
}