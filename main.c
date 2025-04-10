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
		len--;
	return (ft_substr(str, 0, len));
}

//helper
void	print_input(t_data data)
{
	size_t	i;

	printf("PRINT DATA IN FILLED STRUCT\n");
	printf("NO '%s'\n", data.NO);
	printf("SO '%s'\n", data.SO);
	printf("WE '%s'\n", data.WE);
	printf("EA '%s'\n", data.EA);
	printf("Filled %d \n", data.filled);
	printf("Floor %d\n", data.floor);
	printf("Ceiling %d\n", data.ceiling);
	printf("MAP---------->\n");
	i = 0;
	while (i < data.rows)
	{
		printf("%s\n", data.map[i]);
		i++;
	}
	printf("rows is %zu, cols is %zu, pos is [%d][%d], direction is %c \n",
		data.rows, data.cols, data.me.pos.x, data.me.pos.y, data.me.dir);
}

//returns int color or -1 in case of error
int	set_color(char *str)
{
	char	**arr;
	int		colors[3];
	int		i;

	i = 0;
	arr = ft_split(str, ',');
	if (!arr)
		return (-1);
	while (arr[i])
	{
		colors[i] = ft_atoi(arr[i]);
		if (colors[i] == -1)
			return (free_matrix(arr, 3), -1);
		i++;
	}
	if (i != 3)
	{
		printf("Error:\n 3 parameters [R,G,B]\n");
		return (free_matrix(arr, 3), -1);
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
		return (0);
	len = ft_strlen(trimmed_line);
	data->map[data->rows] = (char *)malloc(len + 1);
	if (!data->map[data->rows])
	{
		free(trimmed_line);
		return (0);
	}
	ft_strlcpy(data->map[data->rows], trimmed_line, len + 1);
	free(trimmed_line);
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

int	handle_map(t_data *data, char *str)
{
	char *start;

    start = str;
    if (data->filled < 6)
	{
		printf("Error: Map should go last\n");
		free_data(data);
		return (0);
	}
	data->inside = 1;
	if (store_raw_map(data, start))
		return (1);
	return (0);
}

int	parse_line(char *str, t_data *data)
{
	int		result;
	int		i;
	void	*targets[6];
	char	*ids[6];

	if (!str || !data)
		return (0);
	while (ft_isspace(*str))
		str++;
	targets[0] = &(data->NO);
	targets[1] = &(data->SO);
	targets[2] = &(data->WE);
	targets[3] = &(data->EA);
	targets[4] = &(data->floor);
	targets[5] = &(data->ceiling);
	ids[0] = "NO";
	ids[1] = "SO";
	ids[2] = "WE";
	ids[3] = "EA";
	ids[4] = "F";
	ids[5] = "C";
	i = 0;
	while (i < 6)
	{
		result = check_identifier(str, targets[i], ids[i]);
		if (result == 1)
			return (data->filled++, 1);
		if (result == -1)
			return (0);
		i++;
	}
	if (map_begin(str))
		return (handle_map(data, str));
	else
	{
		printf("Error: Unrecognized input: %s\n", str);
		return (free_data(data), 0);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		fd;
	char	*file;
	char	*line;

	input_data_init(&data);
	file = get_filename(argc, argv);
	if (!file)
	{
		free_data(&data);
		return (1);
	}
	fd = err_open(file);
	if (fd == -1)
	{
		free_data(&data);
		return (1);
	}
	line = get_next_line(fd);
	while (line)
	{
		if (is_empty_or_whitespace(line) && data.inside == 0)
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (!parse_line(line, &data))
		{
			free(line);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	if (!map_ok(&data))
	{
		free_data(&data);
		return (1);
	}
	print_input(data);
	free_data(&data);
	close(fd);
	return (0);
}
