#include "libft/libft.h"
#include <stdio.h>
#include "cub_3d.h"
#include <string.h>

void free_arr(char **arr)
{
    int i = 0;
    if (!arr)
        return;
    while (arr[i])
    {
        free(arr[i]); // Free each word
        i++;
    }
    free(arr); // Free the array itself
}

//int check_extention 1 ok, 0 not ok
int checkExtention(char *str)
{
    if (str == NULL)
        return (1);

    char *ptr = ft_strrchr(str, '.'); //last occurance
    if (!ptr || ptr == str) //no . found or . at the beginning
        return 0;
    ptr++;
    return (!ft_strcmp("cub", ptr));
}

char* getFilename(int arg, char **argv)
{
    if (arg != 2)
    {
        printf("Error\ninput should be <./cub3D> <file.cub>\n");
        return NULL;
    }
    char *str=argv[1];
    if (!checkExtention(str))
    {
        perror("Error\nonly .cub extention allowed and filename required\n");
        return NULL;
    }
    return (str);
}

//check if path is valid and return valid fd or -1
int checkPath(char *str)
{
    int fd;

    fd = -1;
    if (*str == '.' && *(str + 1) == '/' )
    {
        fd = errOpen(str);
    }
    return fd;
}

int	ft_isspace(char c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r' || c == ' ');
}

int is_empty_or_whitespace(char *str)
{
    if (str == NULL)
        return (1);
    
    while (*str)
    {
        if (!ft_isspace(*str)) // Check for non-whitespace characters
            return (0);
        str++;
    }
    return (1); //all whitespace
}

char	**ft_split_global(const char *s, char c)
{
	char			**arr_of_words;
	const char		*separator;
	size_t			size_word;
	size_t			len;
    
	if (!s)
        return (NULL);

	arr_of_words = malloc(3 * sizeof(char *));
	if (!arr_of_words)
		return (NULL);

	separator = ft_strchr(s, c);
	if (!separator)
		return (free(arr_of_words), NULL);

	size_word = separator - s;
	strncpy(arr_of_words[0], s, size_word);
	if (!arr_of_words[0])
	{
		free(arr_of_words);
		return (NULL);
	}

	separator++; // Move past delimiter

	// Skip leading spaces
	while (*separator == ' ')
		separator++;

    // Find length excluding trailing spaces
    len = ft_strlen(separator);
	while (len > 0 && separator[len -1] == ' ')
		len--;

    strncpy(arr_of_words[1],separator, len);
	if (!arr_of_words[1])
	{
		free(arr_of_words[0]);
		free(arr_of_words);
		return (NULL);
	}

	arr_of_words[2] = NULL;
	return (arr_of_words);
}