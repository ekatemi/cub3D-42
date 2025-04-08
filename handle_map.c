/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:38:38 by emikhayl          #+#    #+#             */
/*   Updated: 2025/04/02 20:02:01 by emikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "parser.h"

static int	valid_char(char *line, int *pos)
{
	if (!line)
		return (0);
	while (*line)
	{
		if (*line != '1' && *line != '0' && *line != 'N'
			&& *line != 'S' && *line != 'W' && *line != 'E'
			&& !ft_isspace(*line))
		{
			printf("Wrong char %c\n", *line);
			return (0);
		}
		if (*line == 'N' || *line == 'S' || *line == 'W' || *line == 'E')
			(*pos)++;
		line++;
	}
	return (1);
}

int	trim_empty_lines(t_data *data)
{
	if (!data || !data->map || data->rows <= 0)
		return (0);
	while (data->rows > 0
		&& is_empty_or_whitespace(data->map[data->rows - 1]))
	{
		free(data->map[data->rows - 1]);
		data->map[data->rows - 1] = NULL;
		data->rows--;
	}
	return (1);
}

int	map_is_valid(const t_data data)
{
	size_t	i;
	int		pos;

	i = 0;
	pos = 0;
	if (data.rows < 3)
		return (0);
	while (i < data.rows)
	{
		if (is_empty_or_whitespace(data.map[i]))
		{
			printf("Error empty line inside a map\n");
			return (0);
		}
		if (!valid_char(data.map[i], &pos))
		{
			printf("Error not allowed characters\n");
			return (0);
		}
		i++;
	}
	if (pos > 1 || pos < 1)
		printf("Error position is not correct\n");
	return (pos == 1);
}

static int	copy_str(char *dst, char *src)
{
	int	i;

	i = 0;
	while (src[i] && dst[i])
	{
		if (!ft_isspace(src[i]))
			dst[i] = src[i];
		i++;
	}
	return (1);
}


static void	find_pos(t_data *data)
{
	size_t	i;
	size_t	j;

	if (!data || !data->map || data->rows <= 0)
		return ;
	i = 0;
	while (i < data->rows)
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'S' || data->map[i][j] == 'N'
				|| data->map[i][j] == 'W' || data->map[i][j] == 'E')
			{
				data->me.dir = data->map[i][j];
				data->me.pos.x = j;
				data->me.pos.y = i;
				data->map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
}

int	set_cols_len(t_data *data)
{
	size_t	i;
	size_t	len;
	size_t	max_len;

	i = 0;
	len = 0;
	max_len = 0;
	if (!data || !data->map)
		return (0);
	while (i < data->rows)
	{
		len = ft_strlen(data->map[i]);
		if (len > max_len)
			max_len = len;
		i++;
	}
	data->cols = max_len;
	return (1);
}

int	normalize_map(t_data *data)
{
	size_t	i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	if (!data || !data->map)
		return (0);
	if (!trim_empty_lines(data))
		return (0);
	if (!map_is_valid(*data))
		return (0);
	set_cols_len(data);
	while (i < data->rows)
	{
		tmp = (char *)malloc(data->cols + 1);
		if (!tmp)
			return (0);
		ft_memset(tmp, '0', data->cols);
		tmp[data->cols] = '\0';
		if (!copy_str(tmp, data->map[i]))
		{
			free(tmp);
			return (0);
		}
		free(data->map[i]);
		data->map[i] = tmp;
		i++;
	}
	find_pos(data);
	return (1);
}
