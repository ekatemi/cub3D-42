#include "libft/libft.h"
#include "cub_3d.h"

int validChar(char *line, int *pos)
{
    if (!line)
        return 0;
    while (*line)
    {
        if (*line != '1' && *line != '0' && *line != 'N' && *line != 'S' && *line != 'W' && *line != 'E' && *line != ' ')
            return (0);
        if (*line == 'N' || *line == 'S' || *line == 'W' || *line == 'E')
            (*pos)++;
        line++;
    }
    return (1);
}

// trim empty lines at the end
int trimEmptyLines(t_data *data)
{
    if (!data || !data->map || data->idx <= 0)
        return 0;

    while (data->idx > 0 && is_empty_or_whitespace(data->map[data->idx - 1]))
    {
        free(data->map[data->idx - 1]);
        data->map[data->idx - 1] = NULL;
        data->idx--;
    }
    return 1;
}

// check trimmed map
int mapIsValid(const t_data data)
{
    int i;

    i = 0;
    int pos = 0;
    if (data.idx < 3)
        return 0;
    while (i < data.idx)
    {
        if (is_empty_or_whitespace(data.map[i]))
            return 0;
        if (!validChar(data.map[i], &pos))
            return 0;
        i++;
    }
    return (pos == 1);
}

// I assume that srs is equal or shorter than dest because dest is
int copyStr(char *dst, char *src)
{
    int i = 0;
    while (src[i])
    {
        if (!ft_isspace(src[i]))
        {
            dst[i] = src[i];
            i++;
        }
        else
        {
            i++;
        }
    }
    dst[i] = '\0';
    return 1;
}

// should make all rows equal max len + \0 and replace all space characters with '0'
int normalizeMap(t_data *data)
{
    if (!data || !data->map || data->idx <= 0)
        return 0;
    // trim empty lines at the end
    if (!trimEmptyLines(data))
        return 0;
    // check if the chars are valid
    if (!mapIsValid(*data))
        return 0;
    int i = 0;
    // find max len of row
    int max_len = 0;
    while (i < data->idx)
    {
        if (ft_strlen(data->map[i]) > max_len)
            max_len = ft_strlen(data->map[i]);
        i++;
    }

    i = 0;
    while (i < data->idx)
    {
        char *tmp = (char *)malloc(max_len + 1);
        ft_memset(tmp, '0', max_len); // init with '0'
        if (!copyStr(tmp, data->map[i]))
            return 0;
        free(data->map[i]);
        data->map[i] = tmp;
        i++;
    }
    return 1;
}