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



void printInput(t_data data)
{
    printf("NO %s \n", data.NO);
    printf("SO %s \n", data.SO);
    printf("WE %s \n", data.WE);
    printf("EA %s \n", data.EA);
    printf("Floor %d, %d, %d \n", data.floor.r,data.floor.g, data.floor.b);
    printf("Ceiling %d, %d, %d \n", data.ceiling.r,data.ceiling.g, data.ceiling.b);
}

// void trim_trailing_spaces(char *str)
// {
//     int len = ft_strlen(str);

//     // Find the last non-space character
//     while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t'))
//     {
//         str[len - 1] = '\0';  // Null-terminate the string at the last non-space character
//         len--;
//     }
// }

int extractPath(char *str, t_data *data)
{
    if (!str || !data)
        return (0);
    int i = 0;
    char **target = NULL;
    char *identifier = NULL;//just for print error

    while (str[i] == ' ') //skip spaces at the beginning
    {
        i++;
    }

    if (ft_strncmp(&str[i], "NO", 2) == 0)
    {
       target = &data->NO;
       identifier = "NO";
    }   
    else if (ft_strncmp(&str[i], "SO", 2) == 0)
    {
        target = &data->SO;
        identifier = "SO";
    }  
    else if (ft_strncmp(&str[i], "WE", 2) == 0)
    {
        target = &data->WE;
        identifier = "WE";
    }
    else if (ft_strncmp(&str[i], "EA", 2) == 0)
    {
        target = &data->EA;
        identifier = "EA";
    }
    //no valid identifier for path found
    if (!target || ( str[i + 2] != ' ' && str[i + 2] != '\0'))
        return (0);
    i += 2;
    
    while (str[i] == ' ')
        i++;

    if (*target != NULL)//duplicated
    {
        printf("Error: duplicated identifier %s\n", identifier);
        return (-1);
    }

    *target = ft_strdup(&str[i]);

    return (1);
}

int parseColor(t_location *l, char *str)
{
    int i = 0;
    char **arr;
    int num;
    arr = ft_split(str, ',');
    if (!arr)
        return (0); //error
    


    while (arr[i])
	{
		printf("%s\n", arr[i]);
		num = ft_atoi(arr[i]);
        if (num != -1)
            l->r = num;
        free(arr[i]);
		i++;
	}
    if (arr[i] != '\0')
///add error handling, more than 3 
	free(arr);  
}

int extractTexture(char *str, t_data *data)
{
    if (!str || !data)
        return (0);
    int i = 0;
    char **target = NULL;
    char identifier = NULL;//just for print error

    while (str[i] == ' ') //skip spaces at the beginning
    {
        i++;
    }

    if (ft_strncmp(&str[i], "F", 1) == 0)
    {
       target = &data->floor;
       identifier = 'F';
    }   
    else if (ft_strncmp(&str[i], "C", 1) == 0)
    {
        target = &data->ceiling;
        identifier = 'C';
    }  
   
    //no valid identifier for path found
    if (!target || ( str[i + 1] != ' ' && str[i + 1] != '\0'))
        return (0);
    i += 1;
    
    while (str[i] == ' ')
        i++;

    if (*target != NULL)//duplicated
    {
        printf("Error: duplicated identifier %s\n", identifier);
        return (-1);
    }

    *target = ft_strdup(&str[i]);

    return (1);
}

int main(int argc, char **argv)
{
    t_data data;

    inputDataInit(&data);
    printInput(data); //just to check

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