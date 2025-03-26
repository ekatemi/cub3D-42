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
    
    printf("MAP---------->\n");
    //printf("%s\n", data.map[0]);
    //printf("%s\n", data.map[1]);
    for (int i = 0; i < data.idx; i++)
    {
        printf("%s", data.map[i]);
    }
    printf("\nIDX is %d \n", data.idx);
}


//parse string like this "255,0,4" andd assign to F or C
int fillColor(t_location *l, char *str, char id)
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

    if(id == 'C')
    {
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
    else if(id == 'F')
    {
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
    return 0;
}

int checkIdentifier(char *str, void *target, char *id) //id "NO", "SO", "WE", "EA", "C", "F"
{
    size_t id_len = ft_strlen(id); // Length of the identifier

    // while (ft_isspace(*str)) 
    //     str++;

    // Print for debugging
    //printf("str[0] is %c %c \n", str[0], str[1]);

    // Check if the identifier matches
    if (ft_strncmp(str, id, id_len) == 0 && ft_isspace(*(str + id_len)))
    {
        str += id_len;  // Move pointer past the identifier

        // Skip spaces after the identifier
        while (ft_isspace(*str))
            str++;

        // Check for duplication if it's a texture identifier (NO, SO, WE, EA)
        if (id[0] != 'C' && id[0] != 'F' && *(char **)target != NULL) {
            printf("Error: Duplicated identifier %s\n", id);
            return (0);  // Return error if already assigned
        }


        // Handle texture identifiers (NO, SO, WE, EA)
        if (id[0] != 'C' && id[0] != 'F') {
            char **path_target = (char **)target;
            *path_target = ft_strdup(str);  // Assign the path to the target
            if (!*path_target) 
                return (0);  // Allocation error
            printf("Successfully assigned %s: [%s]\n", id, *path_target);
        }
        // Handle color identifiers (C, F)
        else {
            t_location *color_target = (t_location *)target; // Cast the target to t_location pointer

            // Now you can access the fields of the t_location structure    
            if (!fillColor(color_target, str, *id))
            {
                
                return 0;
            }

            //printf("Color Target: R=%d, G=%d, B=%d\n", color_target->r, color_target->g, color_target->b);
            // Print assigned color
            printf("Successfully assigned string %s color: \n", str);
        }

        return (1);  // Return success
    }

    // No match found
    printf("failed to match (check)\n");
    return (0);  // Return 0 if the identifier doesn't match
}

int storeMap(t_data *data, char *line)
{
    size_t len;

    if(!data || !line)
        return(0);
    if(is_empty_or_whitespace(line))
    {
       printf("Error: empty line in map\n");
       return 0; 
    }
        
    len = ft_strlen(line);
    data->map[data->idx] = (char *)malloc(len + 1);
    if(!data->map[data->idx])
        return 0; //err
    ft_strlcpy(data->map[data->idx], line, len + 1);
    printf("Stored line: %s\n", data->map[data->idx]);
    data->idx +=1;

    return (1);
}

int parseInput(char *str, t_data *data)
{
    if (!str || !data)
        return (0);
    
    char *start = str; //for map

    while (ft_isspace(*str))
        str++;

    // If it's a map line, return success
    if ((*str == '1' && data->filled == 6) || data->inside)//maybe 1 || 0 if map can start from 0
    {
        //printf("Map reached %s\n", start); //TODO check empty lines in map
        if(!storeMap(data, start))
        {
            freeData(data);
            return 0;//err  
        }
        if(data->idx == MAP_SIZE)
        {
            printf("Need resize");
            return 0;//err
        }
        if (!data->inside)
            data->inside = 1; 
        //handle map storeMap(str, data);
        return (1);//all good
    }
       

    if (checkIdentifier(str, &(data->NO), "NO"))
    {
      data->filled += 1;
      return (1);  
    }    
    if (checkIdentifier(str, &(data->SO), "SO"))
    {
      data->filled += 1;
      return (1);  
    }
    if (checkIdentifier(str, &(data->WE), "WE"))
    {
      data->filled += 1;
      return (1);  
    }
    if (checkIdentifier(str, &(data->EA), "EA"))
    {
      data->filled += 1;
      return (1);  
    }
    if (checkIdentifier(str, &(data->F), "F"))
    {
      data->filled += 1;
      return (1);  
    }
    if (checkIdentifier(str, &(data->C), "C"))
    {
      data->filled += 1;
      return (1);  
    }  
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
        if (is_empty_or_whitespace(line) && !data.inside) // Skip to the next line if parseInput returns 0
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