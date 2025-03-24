#include "mlx_linux/mlx.h"
#include "libft/libft.h"
#include "cub_3d.h"



//free 2D array
char	**free_matrix(char **arr_of_words, int col)
{
	int	i;

	i = 0;
	while (i < col && arr_of_words[i])
	{
		free(arr_of_words[i]);
		i++;
	}
	free(arr_of_words);
	return (NULL);
}

//helper
void printInput(t_data data)
{
    printf("PRINT DATA IN FILLED STRUCT\n");
    printf("NO %s \n", data.NO);
    printf("SO %s \n", data.SO);
    printf("WE %s \n", data.WE);
    printf("EA %s \n", data.EA);
    printf("Filled %d \n", data.filled);
    printf("Floor %d, %d, %d \n", data.F.r,data.F.g, data.F.b);
    printf("Ceiling %d, %d, %d \n", data.C.r,data.C.g, data.C.b);
}


//parse string like this "255,0,4" andd assign to F or C
int fillColor(t_location *l, char *str)
{
    int i;
    char **arr;

    i = 0;
    arr = ft_split(str, ','); // Split string into 3 components
    if (!arr)
        return (0); // Allocation error

    // Count elements
    while (arr[i])
        i++;
    
    if (i != 3) {
        printf("Error:\n 3 parameters [R,G,B]\n");
        free_matrix(arr, 3);
        return (0); //err
    }

    // Convert strings to numbers
    l->r = ft_atoi(arr[0]);
    l->g = ft_atoi(arr[1]);
    l->b = ft_atoi(arr[2]);

    if (l->r == -1 || l->g == -1 || l->b == -1) {
        printf("Error: Invalid RGB value (must be 0-255 and only digits)\n");
        free_matrix(arr, 3);
        return (0); //err
    }
    free_matrix(arr, 3);
    return (1); // Ok
}

// int extractColor(char *str, t_data *data)
// {
//     if (!str || !data)
//         return (0);
//     int i = 0;
    
//     while (ft_isspace(str[i])) //skip spaces at the beginning
//     {
//         i++;
//     }

//     if (ft_strncmp(&str[i], "F", 1) == 0 && )
//     {
//         if (data->F.r != -1)
//         {
//             printf("Error: duplicated identifier F\n");
//             return (-1);
//         }
//         fillColor(&data->F, str[i]);
//     }   
//     else if (ft_strncmp(&str[i], "C", 1) == 0)
//     {
//         if (data->C.r != -1)
//         {
//             printf("Error: duplicated identifier C\n");
//             return (-1);
//         }
//         fillColor(&data->C, str[i]);
//     }
//     else
   
//     //no valid identifier found
//     if (!loc_target || ( str[i + 1] != ' ' && str[i + 1] != '\0'))
//         return (0);
//     i += 1;
    
//     while (ft_isspace(str[i]))
//         i++;

//     if (loc_target != NULL)//duplicated
//     {
//         printf("Error: duplicated identifier %s\n", identifier);
//         return (-1);
//     }

//     loc_target = ft_strdup(&str[i]);

//     return (1);
// }





int checkIdentifier(char *str, char **target, char *id) //id "NO"
{
    size_t id_len = ft_strlen(id); //len 2

    while (ft_isspace(*str))
        str++;
    printf("str[0] is %c %c \n", str[0], str[1]);
    if (ft_strncmp(str, id, id_len) == 0 && ft_isspace(*(str + id_len)))
    {
        str += id_len;
        // Skip spaces
        while (ft_isspace(*str))
            str++;

        printf("target is %s\n", *target);
        if (*target != NULL)
        {
            printf("Error: Duplicated identifier %s\n", id);
            return (0); // Input error, return immediately
        }
        *target = ft_strdup(str);  // Assign the duplicated string to NO or SO
        printf("target is %s\n", *target);
        if (!*target)
            return (0); // Allocation error

        return (1);  // Success
    }
    printf("failed to match\n");//no matches
    return (0);  // Return 0 if the identifier does not match
}

int parseInput(char *str, t_data *data)
{
    if (!str || !data)
        return (0);

    // If it's a map line, return success
    if (str[0] == '1')
        return (1);//????????

    if (checkIdentifier(str, &(data->NO), "NO"))
        return (1);
    if (checkIdentifier(str, &(data->SO), "SO"))
        return (1);
    if (checkIdentifier(str, &(data->WE), "WE"))
        return (1);
    if (checkIdentifier(str, &(data->EA), "EA"))
        return (1);
    // if (checkIdentifier(str, &(data->EA), "C"))
    //     return (1);
    // if (checkIdentifier(str, &(data->EA), "F"))
    //     return (1);
    else
    {
        freeData(data);
        return(0);
    }
        

    freeData(data);
    printf("Error: Unrecognized input: [%s]\n", str);
    return (0);
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
    char    *line;
    
    fd = errOpen(file);
    if (fd == -1)
    {
       return (1); 
    }
    
    line = get_next_line(fd); //if result is empty line skip to next
    //printf("Result is %s\n", result);
    while (line)	
    {
        if (is_empty_or_whitespace(line)) // Skip to the next line if parseInput returns 0
        {
            free(line);
            line = get_next_line(fd);
            continue;
        }
        if (!parseInput(line, &data))
        {
            free(line);
            return(1);
        }
        free(line);
        line = get_next_line(fd);
    }
    printf("AFTER--------------->\n");
    printInput(data);
    freeData(&data);
    
    close(fd);
    return (0);
}