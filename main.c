#include "mlx_linux/mlx.h"
#include "libft/libft.h"
#include "cub_3d.h"


char	*ft_strndup(const char *s1, int n)
{
	int			i;
	char			*copy;

	i = 0;
	copy = (char *)malloc(sizeof(char) * (n + 1)); // Allocate memory for n characters + null-terminator
	if (copy == NULL)
		return (NULL);
	while (i < n && s1[i] != '\0') // Copy up to n characters or stop at the null-terminator
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0'; // Ensure null-termination
	return (copy);
}
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
    printf("NO %s \n", data.NO);
    printf("SO %s \n", data.SO);
    printf("WE %s \n", data.WE);
    printf("EA %s \n", data.EA);
    printf("Filled %d \n", data.filled);
    printf("Floor %d, %d, %d \n", data.F.r,data.F.g, data.F.b);
    printf("Ceiling %d, %d, %d \n", data.C.r,data.C.g, data.C.b);
}


// find identifyer
int extractTexture(char *str, t_data *data)
{
    if (!str || !data)
        return (0);
    int i = 0;
    char **target = NULL;
    char *identifier = "";//just for print error

    while (ft_isspace(str[i])) //skip spaces at the beginning
    {
        i++;
    }

    if (ft_strncmp(&str[i], "NO", 2) == 0)
    {
       if (*target != NULL)
       {
            printf("Error: duplicated identifier %s\n", identifier);
            return (-1);
        }
       target = &data->NO;
       identifier = "NO";
    }   
    else if (ft_strncmp(&str[i], "SO", 2) == 0)
    {
        if (*target != NULL)
        {
            printf("Error: duplicated identifier %s\n", identifier);
            return (-1);
        }
        target = &data->SO;
        identifier = "SO";
    }  
    else if (ft_strncmp(&str[i], "WE", 2) == 0)
    {
        if (*target != NULL)
        {
            printf("Error: duplicated identifier %s\n", identifier);
            return (-1);
        }
        target = &data->WE;
        identifier = "WE";
    }
    else if (ft_strncmp(&str[i], "EA", 2) == 0)
    {
        if (*target != NULL)
        {
            printf("Error: duplicated identifier %s\n", identifier);
            return (-1);
        }
        target = &data->EA;
        identifier = "EA";
    }
    //no valid identifier for path found
    if (!target || ( str[i + 2] != ' ' && str[i + 2] != '\0'))
        return (0);
    i += 2;
    
    while (ft_isspace(str[i]))
        i++;

    // if (*target != NULL)//duplicated
    // {
    //     printf("Error: duplicated identifier %s\n", identifier);
    //     return (-1);
    // }
    //strndup till last not empty space char
    int len = ft_strlen(str);
    while(len > 0 && ft_isspace(str[len-1]))
    {
        len--;
    }

    *target = ft_strndup(&str[i], len);
    return (1);
}

/* PARSE F and C */
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

//check id and if it is 0, then input is not correct


int parseInput(char *str, t_data *data)
{
    
    int i = 0;

    char **arr;

    if (!str || ft_strlen(str) < 2)
        return (0); //err
    
    //skip leading whitespaces
    while(ft_isspace(str[i]))
        i++;
    
    if(str[i] != '1') //not a map
    {
        arr =ft_split_global(&str[i], ' '); //divide on first space found,[0][1][2]
        if (!arr)
        {
            printf("Error: Input too short\n");
            return (0);//err allocation or identifyer
        }
             
        //printf("ID is %s, value is %s", arr[0], arr[1]);
        if (!ft_strcmp(arr[0],"NO"))
        {
            if(data->NO != NULL)
            {
                printf("Error: Duplicated identifyer NO\n");
                free_matrix(arr, 2);
                return (-1); //input err
            }
            else 
            {
                data->NO = ft_strdup(arr[1]);
                if (!data->NO)
                {
                    free_matrix(arr, 2);
                    return (0);//alloc err
                }
                data->filled +=1;
            }
            
                
        }
        else if (!ft_strcmp(arr[0],"SO"))
        {
            if(data->SO != NULL)
            {
                free_matrix(arr, 2);
                printf("Error: Duplicated identifyer SO\n");
                return (-1); //input err
            }
            data->SO = ft_strdup(arr[1]);
            if (!data->SO)
            {
                free_matrix(arr, 2);
                return (0);//alloc err
            }
            data->filled +=1;   
        }
        else if (!ft_strcmp(arr[0],"WE"))
        {
            if(data->WE != NULL)
            {
                return (-1); //input err
                free_matrix(arr, 2);
                printf("Error: Duplicated identifyer WE\n");
            }
            data->WE = ft_strdup(arr[1]);
            if (!data->WE)
            {
                free_matrix(arr, 2);
                return (0);//alloc err
            }
            data->filled +=1;   
        }
        else if (!ft_strcmp(arr[0],"EA"))
        {
            if(data->EA != NULL)
            {
                printf("Error: Duplicated identifyer EA\n");
                free_matrix(arr, 2);
                return (-1); //input err
            }
            data->EA = ft_strdup(arr[1]);
            if (!data->EA)
            {
                free_matrix(arr, 2);
                return (0);//alloc err
            }
            data->filled +=1;  
        }
        else if (!ft_strcmp(arr[0],"F"))
        {
            if(data->F.b != -1)
            {
                free_matrix(arr, 2);
                printf("Error: Duplicated identifyer F\n");
                return (-1); //input err
            }
            if (fillColor(&data->F, arr[1]) == 0)
            {
                free_matrix(arr, 2);
                return -1;
            }
            data->filled +=1;   
        }
        else if (!ft_strcmp(arr[0],"C"))
        {
            if(data->C.b != -1)
            {
                free_matrix(arr, 2);
                printf("Error: Duplicated identifyer C\n");
                return (-1); //input err
            }
            if (fillColor(&data->C, arr[1]) == 0)
            {
                free_matrix(arr, 2);
                return (-1); //input err
            }
            data->filled +=1;   
        }
        else
        {
            printf("Error: wrong identifier %s\n", arr[0]);
            free_matrix(arr, 2);
            return (-1); //input err
        } 
        //printf("Value is '%s'\n", data->NO);

    }
    // else
    //     printf("it is a map %s\n", str); //handle map here

    return 1;

}



int main(int argc, char **argv)
{
    t_data data;

    inputDataInit(&data);
    //printInput(data); //just to check

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
        if (parseInput(result, &data) <= 0) //what returns parse input??
            return (1);
        free(result);
        result = get_next_line(fd);
    }
    printInput(data);
    free(result);
    close(fd);
    return (0);
}