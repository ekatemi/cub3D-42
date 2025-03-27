#include "libft/libft.h"
#include "cub_3d.h"


int validChar(char *line, int *pos)
{
    if(!line)
        return 0;
    while(*line)
    {
        if (*line != '1' && *line != '0' && *line != 'N' && *line != 'S'
            && *line != 'W' && *line != 'E' && *line != ' ')
            return (0);
        if(*line == 'N' || *line == 'S' || *line == 'W' || *line == 'E')
            (*pos)++;
        line++;
    }
    return (1);
}

int mapIsValid(const t_data data)
{
    int i;

    i = 0;
    int pos = 0;
    if (data.idx < 3)
        return 0;
    while(i < data.idx)
    {
        if(is_empty_or_whitespace(data.map[i]))
            return 0;
        if(!validChar(data.map[i], &pos))
            return 0;
        i++;
    }
    return (pos == 1);
}
