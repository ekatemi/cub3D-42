#include "libft/libft.h"
#include "cub_3d.h"

int validChar(char *line, int *pos)
{
    if (!line)
        return 0;
    while (*line)
    {
        if (*line != '1' && *line != '0' && *line != 'N' && *line != 'S' && *line != 'W' && *line != 'E' && !ft_isspace(*line))
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

// trim empty lines at the end
int trimEmptyLines(t_data *data)
{
    if (!data || !data->map || data->rows <= 0)
        return 0;

    while (data->rows > 0 && is_empty_or_whitespace(data->map[data->rows - 1]))
    {
        free(data->map[data->rows - 1]);
        data->map[data->rows - 1] = NULL;
        data->rows--;
    }
    return 1;
}

// check trimmed map
int mapIsValid(const t_data data)
{
    int i;

    i = 0;
    int pos = 0;
    if (data.rows < 3)
        return 0;
    while (i < data.rows)
    {
        if (is_empty_or_whitespace(data.map[i]))
        {
            printf("Error empty line inside a map\n");
            return 0;
        }
            
        if (!validChar(data.map[i], &pos))
        {
            printf("Error not allowed characters\n");
            return 0;
        }
        i++;
    }
    if(pos > 1 || pos < 1)
        printf("Error position is not correct\n");
    return (pos == 1);
}

// I assume that srs is equal or shorter than dest because dest is
int copyStr(char *dst, char *src)
{
    int i = 0;

    while(src[i] && dst[i])
    {   
        if(!ft_isspace(src[i]))
            dst[i] = src[i];
        i++;
    }
    // while(dst[i])
    // {
    //     dst[i] = '0';
    //     i++;
    // }
    return 1;
}




void findPos(t_data *data)
{
    int i;
    int j;
    if (!data || !data->map || data->rows <= 0)
        return ;
    
    i = 0;
    while (i < data->rows)
    {
        j = 0;
        while(data->map[i][j])
        {
            if(data->map[i][j] == 'S' || data->map[i][j] == 'N' 
                || data->map[i][j] == 'W' || data->map[i][j] == 'E')
            {
                data->d = data->map[i][j];
                data->pos.x = j;
                data->pos.y = i;
            }
           j++;    
        }
        i++;
    }
}

// should make all rows equal max len + \0 and replace all space characters with '0'
int normalizeMap(t_data *data)
{
    if (!data || !data->map || data->rows <= 0)
        return 0;
    // trim empty lines at the end
    if (!trimEmptyLines(data))
        return 0;
    if (!mapIsValid(*data))
        return 0; 
    int i = 0;
    // find max len of row
    size_t max_len = 0;
    while (i < data->rows)
    {
        size_t row_len = ft_strlen(data->map[i]);
        if (row_len > max_len)
            max_len = ft_strlen(data->map[i]);
        i++;
    }
    printf("The max len raw is %zu\n", max_len);

    i = 0;
    while (i < data->rows)
    {
        char *tmp = (char *)malloc(max_len + 1);
        ft_memset(tmp, '0', max_len); // init with '0'
        printf("Tmp is %s\n", tmp);
        if (!copyStr(tmp, data->map[i]))
            return 0;
        free(data->map[i]);
        data->map[i] = tmp;
        i++;
    }
    findPos(data);
    return 1;
}