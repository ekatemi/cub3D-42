#include "cub_3d.h"
#include "./libft/libft.h"

char	*extract_line(char *buffer)
{
	int		line_size;
	char	*temp;
	char	*line;

	if (buffer[0] == '\0')
		return (NULL);
	line_size = 0;
	while (buffer[line_size] && buffer[line_size] != '\n')
		line_size++;
	if (buffer[line_size] == '\n')
		line_size++;
	line = malloc(sizeof(char) * (line_size + 1));
	if (!line)
		return (NULL);
	temp = line;
	while (0 < line_size--)
		*temp++ = *buffer++;
	*temp = '\0';
	return (line);
}

char	*update_storage(char *buffer)
{
	char	*ptr_newline;
	char	*rest_line;
	int		line_size;
	char	*temp;

	ptr_newline = ft_strchr(buffer, '\n');
	if (!ptr_newline)
	{
		return (get_free(&buffer));
	}
	line_size = ft_strlen(ptr_newline) - 1;
	rest_line = ft_calloc((line_size + 1), sizeof(char));
	if (!rest_line)
		return (get_free(&buffer));
	temp = rest_line;
	while (0 < line_size--)
		*temp++ = *++ptr_newline;
	free (buffer);
	buffer = rest_line;
	return (buffer);
}

char	*read_from_file(int fd, char *buffer)
{
	char	*r_buffer;
	int		bytes_nbr;

	r_buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!r_buffer)
		return (get_free(&buffer));
	bytes_nbr = 1;
	while (bytes_nbr > 0 && !ft_strchr(buffer, '\n'))
	{
		bytes_nbr = read(fd, r_buffer, BUFFER_SIZE);
		if (bytes_nbr == -1)
		{
			free(buffer);
			free(r_buffer);
			return (NULL);
		}
		r_buffer[bytes_nbr] = '\0';
		buffer = ft_strjoin(buffer, r_buffer);
		if (!buffer)
			break ;
	}
	free(r_buffer);
	return (buffer);
}

char	*get_free(char **str1)
{
	if (str1 && *str1)
	{
		free(*str1);
		*str1 = NULL;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char		*persistent_buffer;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!persistent_buffer)
		persistent_buffer = ft_calloc(1, sizeof(char));
	if (!persistent_buffer)
		return (NULL);
	if (persistent_buffer == NULL || !ft_strchr(persistent_buffer, '\n'))
		persistent_buffer = read_from_file(fd, persistent_buffer);
	if (!persistent_buffer)
		return (NULL);
	line = extract_line(persistent_buffer);
	if (!line)
		return (get_free(&persistent_buffer));
	persistent_buffer = update_storage(persistent_buffer);
	return (line);
}
