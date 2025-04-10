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
#include "parser.h"

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

char	*trim_trailing_spaces(const char *str)
{
	int	len;

	len = ft_strlen(str);
	while (len > 0 && ft_isspace(str[len - 1]))
		len--; // Move backward to remove spaces
	return (ft_substr(str, 0, len)); // Extract trimmed substring
}

//helper
void print_input(t_data data)
{
    printf("PRINT DATA IN FILLED STRUCT\n");
    printf("NO '%s'\n", data.NO);
    printf("SO '%s'\n", data.SO);
    printf("WE '%s'\n", data.WE);
    printf("EA '%s'\n", data.EA);
    printf("Filled %d \n", data.filled);
    printf("Floor %d\n", data.floor);
    printf("Ceiling %d\n", data.ceiling);
    
    printf("MAP---------->\n");
    for (size_t i = 0; i < data.rows; i++)
    {
        printf("%s\n", data.map[i]);
    }
    printf("rows is %zu, cols is %zu, pos is [%d][%d], direction is %c \n", data.rows, data.cols, data.me.pos.x, data.me.pos.y, data.me.dir);
}

//retuns int color or -1 in case of error
int	set_color(char *str)
{
	char	**arr;
	int		colors[3];
	int		i;

	i = 0;
	arr = ft_split(str, ',');
	if (!arr)
		return (-1); // Allocation error

	while (arr[i])
	{
		colors[i] = ft_atoi(arr[i]);
		if (colors[i] == -1)
		{
			free_matrix(arr, 3);
			return (-1); // Invalid input
		}
		i++;
	}
	if (i != 3)
	{
		printf("Error:\n 3 parameters [R,G,B]\n");
		free_matrix(arr, 3);
		return (-1);
	}
	free_matrix(arr, 3);
	return ((colors[0] << 16) | (colors[1] << 8) | colors[2]);
}

//if (check_identifier(str, &(data->NO), "NO"))
int	check_identifier(char *str, void *target, char *id)
{
	size_t	id_len;
	int		*color_target;
	char	**path_target;

	id_len = ft_strlen(id);
	if (ft_strncmp(str, id, id_len) != 0 || !ft_isspace(str[id_len]))
		return (0);
	str += id_len;
	while (ft_isspace(*str))
		str++;

	if (id[0] == 'F' || id[0] == 'C')
	{
		color_target = (int *)target;
		if (*color_target != -2)
		{
			printf("Error: Duplicated identifier %s\n", id);
			return (-1);
		}
		*color_target = set_color(str);
		if (*color_target == -1)
		{
			printf("ERROR Color\n");
			return (-1);
		}
		printf("Assigned %d color target\n", *color_target);
	}
	else
	{
		path_target = (char **)target;
		if (*path_target != NULL)
		{
			printf("Error: Duplicated identifier %s\n", id);
			return (-1);
		}
		*path_target = trim_trailing_spaces(str);
		if (!*path_target)
			return (-1);
		printf("Successfully assigned %s: [%s]\n", id, *path_target);
	}
	return (1);
}

int	store_raw_map(t_data *data, char *line)
{
	size_t	len;
	char	*trimmed_line;

	if (!data || !line || !data->inside)
		return (0);
	trimmed_line = trim_trailing_spaces(line);
	if (!trimmed_line)
		return (0); // Memory allocation failed
	len = ft_strlen(trimmed_line);
	data->map[data->rows] = (char *)malloc(len + 1);
	if (!data->map[data->rows])
	{
		free(trimmed_line);
		return (0); // Allocation error
	}
	ft_strlcpy(data->map[data->rows], trimmed_line, len + 1);
    free(trimmed_line); // Free temporary trimmed string
	data->rows++;
	return (1);
}

int	map_begin(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str != '1' && *str != '0' && *str != 'N' && *str != 'S'
			&& *str != 'E' && *str != 'W' && !ft_isspace(*str))
			return (0);
		str++;
	}
	return (1);
}

int	parse_line(char *str, t_data *data)
{
	char *start;
	int result;

	if (!str || !data)
		return (0);
	start = str;
	while (ft_isspace(*str))
		str++;

	result = check_identifier(str, &(data->NO), "NO");
	if (result == 1)
        return (data->filled++, 1);
	if (result == -1)
        return (0);
	result = check_identifier(str, &(data->SO), "SO");
	if (result == 1)
        return (data->filled++, 1);
	if (result == -1)
        return (0);
	result = check_identifier(str, &(data->WE), "WE");
	if (result == 1)
        return (data->filled++, 1);
	if (result == -1)
        return (0);
	result = check_identifier(str, &(data->EA), "EA");
	if (result == 1)
        return (data->filled++, 1);
	if (result == -1)
        return (0);
	result = check_identifier(str, &(data->floor), "F");
	if (result == 1)
        return (data->filled++, 1);
	if (result == -1)
        return (0);
	result = check_identifier(str, &(data->ceiling), "C");
	if (result == 1)
        return (data->filled++, 1);
	if (result == -1)
        return (0);

	if (map_begin(str))
	{
		if (data->filled < 6)
		{
			printf("Error: Map should go last\n");
			free_data(data);
			return (0);
		}
		data->inside = 1;
		if (store_raw_map(data, start))
			return (1);
	}
	else
	{
		printf("Error: Unrecognized input: %s\n", str);
		free_data(data);
		return (0);
	}
	return (0);
}



int main(int argc, char **argv)
{
    t_data data;
    input_data_init(&data);
    
	
	
	char *file = get_filename(argc, argv);
    if (!file)
    {
        free_data(&data);
        return (1);
    }  
    int     fd;
    char    *line;
    
    fd = err_open(file);
    if (fd == -1)
    {
       free_data(&data);
       return (1); 
    }
    line = get_next_line(fd);
    while (line)	
    {
        //skip empty lines if we are not in the map
        if (is_empty_or_whitespace(line) && data.inside == 0)
        {
            free(line);
            line = get_next_line(fd);
            continue;
        }
        if (!parse_line(line, &data))
        {
            free(line);
            return(1);
        }
        free(line);
        line = get_next_line(fd);
    }  

    //handling filled struct
    //map operations
    if(!normalize_map(&data))
    {
        printf("Map is not valid\n");
        free_data(&data);
        return 1;
    } 
    if (!is_map_closed(&data)) //area size begin
	{
        printf("\nThe map is open\n");
        free_data(&data);
        return 1;
    }
    print_input(data);
    free_data(&data);
    close(fd);
    return (0);
}

