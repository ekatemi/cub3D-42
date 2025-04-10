/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:39:45 by emikhayl          #+#    #+#             */
/*   Updated: 2025/04/02 19:39:48 by emikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "parser.h"
#include <string.h>

// int check_extention 1 ok, 0 not ok
int	check_extention(char *str)
{
	char	*ptr;

	if (str == NULL)
		return (1);
	ptr = ft_strrchr(str, '.');
	if (!ptr || ptr == str)
		return (0);
	ptr++;
	return (!ft_strcmp("cub", ptr));
}

char	*get_filename(int arg, char **argv)
{
	char	*str;

	if (arg != 2)
	{
		printf("Error\ninput should be <./cub3D> <file.cub>\n");
		return (NULL);
	}
	str = argv[1];
	if (!check_extention(str))
	{
		perror("Error\nonly .cub extention allowed and filename required\n");
		return (NULL);
	}
	return (str);
}

int	check_path(char *str)
{
	int	fd;

	fd = -1;
	if (*str == '.' && *(str + 1) == '/')
		fd = err_open(str);
	return (fd);
}

int	ft_isspace(char c)
{
	return (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ');
}

int	is_empty_or_whitespace(char *str)
{
	if (str == NULL)
		return (1);
	while (*str)
	{
		if (!ft_isspace(*str))
			return (0);
		str++;
	}
	return (1);
}
