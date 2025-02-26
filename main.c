#include "mlx_linux/mlx.h"
#include "libft/libft.h"
#include "get_next_line/get_next_line.h"

//int check_extention

int main(void)
{
    int     fd;
    char    *result;
    fd = open("tst.txt", O_RDONLY);
    result = get_next_line(fd);
    //printf("Result is %s\n", result);
    while (result)	
    {
        printf("RESULT--->>>%s", result);
        free(result);
        result = get_next_line(fd);
    }
    free(result);
    return (0);
}