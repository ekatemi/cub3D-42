#include "libft/libft.h"
#include <stdio.h>
#include "cub_3d.h"

//int check_extention 1 ok, 0 not ok
int checkExtention(char *str)
{
    if (str == NULL)
        return (1);

    char *ptr = ft_strrchr(str, '.'); //last occurance
    if (!ptr || ptr == str) //no . found or . at the beginning
        return 0;
    ptr++;
    return (!ft_strcmp("cub", ptr));
}

char* getFilename(int arg, char **argv)
{
    if (arg != 2)
    {
        printf("Error\ninput should be <./cub3D> <file.cub>\n");
        return NULL;
    }
    char *str=argv[1];
    if (!checkExtention(str))
    {
        perror("Error\nonly .cub extention allowed and filename required\n");
        return NULL;
    }
    return (str);
}

//check if path is valid and return valid fd or -1
int checkPath(char *str)
{
    int fd;

    fd = -1;
    if (*str == '.' && *(str + 1) == '/' )
    {
        fd = errOpen(str);
    }
    return fd;
}

int	ft_isspace(char c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r' || c == ' ');
}

int is_empty_or_whitespace(char *str)
{
    if (str == NULL)
        return (1);
    
    while (*str)
    {
        if (!ft_isspace(*str)) // Check for non-whitespace characters
            return (0);
        str++;
    }
    return (1); //all whitespace
}