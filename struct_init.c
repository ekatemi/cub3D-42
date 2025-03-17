#include "cub_3d.h"


void inputDataInit(t_data *data)
{
    if (!data)
        return;
    data->NO = NULL;// Path to the texture file
    data->SO = NULL;
    data->WE = NULL;
    data->EA = NULL;

    data->floor.r = -1; //0 to 255
    data->floor.g = -1;
    data->floor.b = -1;

    data->ceiling.r = -1;
    data->ceiling.g = -1;
    data->ceiling.b = -1;

    data->map = (char**)malloc(sizeof(char*) * (50 + 1));
    if (!data->map)
        return;
    data->map[0] = 0; //init space for 50 lines
}