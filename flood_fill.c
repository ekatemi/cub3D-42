/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emikhayl <emikhayl@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 19:29:42 by emikhayl          #+#    #+#             */
/*   Updated: 2025/04/02 19:38:19 by emikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <string.h>

void	free_area(char **area, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(area[i]);
		i++;
	}
	free(area);
}

char	**make_area(t_data *data)
{
	int		i;
	char	**area;

	i = 0;
	area = (char **)malloc(data->rows * sizeof(char *));
	if (!area)
		return (NULL);
	while (i < (int)data->rows)
	{
		area[i] = strdup(data->map[i]);
		if (!area[i])
		{
			while (--i >= 0)
				free(area[i]);
			free(area);
			return (NULL);
		}
		i++;
	}
	return (area);
}

int	fill(t_data *data, int y, int x, char **map)
{
	int	open;

	if (y < 0 || x < 0 || y >= (int)data->rows || x >= (int)data->cols)
		return (1);
	if (map[y][x] == 'F' || map[y][x] == '1')
		return (0);
	map[y][x] = 'F';
	open = 0;
	open |= fill(data, y - 1, x, map);
	open |= fill(data, y + 1, x, map);
	open |= fill(data, y, x - 1, map);
	open |= fill(data, y, x + 1, map);
	return (open);
}

int	is_map_closed(t_data *data)
{
	int		is_open;
	char	**copy;
	int		y;
	int		x;

	copy = make_area(data);
	if (!copy)
		return (0);
	y = data->me.pos.y;
	x = data->me.pos.x;
	is_open = fill(data, y, x, copy);
	free_area(copy, data->rows);
	return (!is_open);
}
