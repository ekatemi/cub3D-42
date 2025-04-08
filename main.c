/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:39:45 by emikhayl          #+#    #+#             */
/*   Updated: 2025/04/02 19:39:48 by emikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "mlx_linux/mlx.h"
#include "libft/libft.h"
#include "cub_3d.h"
#include <string.h> ///DELETE!!!!!!



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

char *trim_trailing_spaces(const char *str)
{
    int len = ft_strlen(str);
    while (len > 0 && ft_isspace(str[len - 1])) // Move backward to remove spaces
        len--;
    return (ft_substr(str, 0, len)); // Extract trimmed substring
}

//helper
void printInput(t_data data)
{
    // printf("PRINT DATA IN FILLED STRUCT\n");
    // printf("NO '%s'\n", data.NO);
    // printf("SO '%s'\n", data.SO);
    // printf("WE '%s'\n", data.WE);
    // printf("EA '%s'\n", data.EA);
    // printf("Filled %d \n", data.filled);
    // printf("Floor %d, %d, %d \n", data.F.r,data.F.g, data.F.b);
    // printf("Ceiling %d, %d, %d \n", data.C.r,data.C.g, data.C.b);
    
    printf("MAP---------->\n");
    for (size_t i = 0; i < data.rows; i++)
    {
        printf("%s\n", data.map[i]);
    }
    printf("rows is %zu, cols is %zu, pos is [%d][%d] \n", data.rows, data.cols, data.me.pos.x, data.me.pos.y);
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
            *path_target = trim_trailing_spaces(str);
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
            printf("Successfully assigned string %s color: \n", str);
        }

        return (1);  // Return success
    }
    return (0);  // Return 0 if the identifier doesn't match
}

int storeRawMap(t_data *data, char *line)
{
    size_t len;
    char *trimmed_line;

    if (!data || !line || !data->inside)
        return (0);

    trimmed_line = trim_trailing_spaces(line);
    if (!trimmed_line)
        return (0); // Memory allocation failed

    len = strlen(trimmed_line);
    data->map[data->rows] = (char *)malloc(len + 1);
    if (!data->map[data->rows])
    {
        free(trimmed_line);
        return (0); // Allocation error
    }

    ft_strlcpy(data->map[data->rows], trimmed_line, len + 1);
    free(trimmed_line); // Free temporary trimmed string

    data->rows++;

    if (!data->inside)
        data->inside = 1;
    return (1);
}

int parseInput(char *str, t_data *data)
{
    if (!str || !data)
        return (0);
    
    char *start = str; //for map

    while (ft_isspace(*str))
        str++;

    // If it is a beginning of a map put flag
    if ((!ft_isspace(*str) && data->filled == 6) )
    {
        data->inside = 1;
    }

    if(storeRawMap(data, start))
    {
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
        free_data(data);
        return(0);
    }
    free_data(data);
    printf("Error: Unrecognized input: [%s]\n", str);
    return (0);
}

int main(int argc, char **argv)
{
    t_data data;

    inputDataInit(&data);
    //printInput(data); //just to check

    char *file = getFilename(argc, argv);
    if (!file)
    {
        free_data(&data);
        return (1);
    }
        
        
    int     fd;
    char    *line;
    
    fd = errOpen(file);
    if (fd == -1)
    {
       free_data(&data);
       return (1); 
    }
    
    line = get_next_line(fd); //if result is empty line skip to next
    //printf("Result is %s\n", result);
    while (line)	
    {
        if (is_empty_or_whitespace(line) && data.inside == 0) // Skip to the next line if parseInput returns 0
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
    //printInput(data);
    
    if(!normalize_map(&data))
    {
        printf("Map is not valid\n");
        free_data(&data);
        return 1;
    }
    
    //trimEmptyLines(&data);
    printf("Map after modification------->\n");
    printInput(data);
    
    if (is_map_closed(&data)) //area size begin
        printf("\nThe map is closed\n");
    else
    {
        printf("\nThe map is open\n");
        free_data(&data);
        return 1;
    }
        
    
    ///here check map is valid
    //start mlx
    free_data(&data);
    
    close(fd);
    return (0);
}

