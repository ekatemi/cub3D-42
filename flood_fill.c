#include "cub_3d.h"
#include <string.h>

//Free allocated memory for the map
void free_area(char **area, int rows)
{
    for (int i = 0; i < rows; i++)
        free(area[i]);
    free(area);
}

// Function to create a dynamic copy of the map
char **make_area(t_data *data)
{
    char **area = (char **)malloc(data->rows * sizeof(char *));
    if (!area)
        return NULL;

    for (int i = 0; i < (int)data->rows; i++)
    {
        area[i] = strdup(data->map[i]); // Copy the entire row as is
        if (!area[i])
        {
            while (--i >= 0)
                free(area[i]);
            free(area);
            return NULL;
        }
    }
    return area;
}

// Modified flood-fill function to detect open maps
// int fill(char **tab, t_point size, char target, int row, int col)
int fill(t_data *data, int y, int x, char **map)
{
    if (y < 0 || x < 0 || y >= (int)data->rows || x >= (int)data->cols)
        return 1;

    if (map[y][x] == 'F' || map[y][x] == '1')
        return 0;

    map[y][x] = 'F';

    int open = 0;
    open |= fill(data, y - 1, x, map);
    open |= fill(data, y + 1, x, map);
    open |= fill(data, y, x - 1, map);
    open |= fill(data, y, x + 1, map);

    return open;
}

// Function to check if the map is closed  area size begin
int is_map_closed(t_data *data)
{
    char **copy = make_area(data);
    if (!copy)
        return 0;

    int y = data->me.pos.y;
    int x = data->me.pos.x;

    int is_open = fill(data, y, x, copy);

    free_area(copy, data->rows);
    return !is_open;
}

// int main(void)
// {
//     t_point size = {8, 5};
//     t_point begin = {1, 1}; // Start inside the open space

//     char *zone[] = {
//         "11111111",
//         "10001001",
//         "        ",
//         "10010000",
//         "10110001",
//         "11100001",
//     };

//     char **area = make_area(zone, size);
//     if (!area)
//     {
//         printf("Memory allocation failed!\n");
//         return 1;
//     }

//     if (is_map_closed(area, size, begin))
//         printf("\nThe map is closed\n");
//     else
//         printf("\nThe map is open\n");

//     free_area(area, size);

//     return 0;
// }