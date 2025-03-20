#include "cub_3d.h"


void inputDataInit(t_data *data)
{
    if (!data)
        return;
    data->NO = NULL;// Path to the texture file
    data->SO = NULL;
    data->WE = NULL;
    data->EA = NULL;

    data->F.r = -1; //0 to 255
    data->F.g = -1;
    data->F.b = -1;

    data->C.r = -1;
    data->C.g = -1;
    data->C.b = -1;

    data->filled = 0;

    data->map = (char**)malloc(sizeof(char*) * (50 + 1));
    if (!data->map)
        return;
    data->map[0] = 0; //init space for 50 lines
}