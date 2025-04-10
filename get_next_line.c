/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:36:19 by emikhayl          #+#    #+#             */
/*   Updated: 2025/04/02 19:43:38 by emikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "./libft/libft.h"

char	*grow_buffer(char *buffer, size_t new_size, int index)
{
	char	*new_buffer;
	int		i;

	new_buffer = (char *)malloc(new_size + 1);
	if (!new_buffer)
	{
		free(buffer);
		return (NULL);
	}
	i = 0;
	while (i < index)
	{
		new_buffer[i] = buffer[i];
		i++;
	}
	free(buffer);
	return (new_buffer);
}

static char	*read_line(int fd)
{
	char	*buffer;
	char	character;
	int		index;
	int		bytes;
	size_t	buffer_size;

	index = 0;
	buffer_size = 1024;
	buffer = (char *)malloc(sizeof(char) * (buffer_size + 1));
	if (!buffer)
		return (NULL);
	bytes = read(fd, &character, 1);
	while (bytes > 0)
	{
		if (index >= (int)buffer_size)
			buffer = grow_buffer(buffer, buffer_size * 2, index);
		buffer[index++] = character;
		if (character == '\n')
			break ;
		bytes = read(fd, &character, 1);
	}
	if ((bytes <= 0) && (index == 0))
		return (free(buffer), NULL);
	buffer[index] = '\0';
	return (buffer);
}

char	*get_next_line(int fd)
{
	char	*line;

	if (fd < 0)
		return (NULL);
	line = read_line(fd);
	if (!line)
		return (NULL);
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	return (line);
}
