#include "cub_3d.h"


void inputDataInit(t_data *data)
{
    int i;

    i = 0;
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
    data->idx = 0;
    data->inside = 0;


    data->map = (char**)malloc(sizeof(char*) * (MAP_SIZE));
    if (!data->map)
    {
        data->map = NULL;
        return;
    }
        
    // Initialize all rows to NULL
    while(i < MAP_SIZE)
    {
        data->map[i] = NULL;
        i++;
    }

    data->d = 'A';
    data->pos.x = 0;
    data->pos.y = 0;
}

void freeData(t_data *data)
{
    int i;

    i = 0;
    if (!data)
        return;

    // Free texture paths
    free(data->NO);
    free(data->SO);
    free(data->WE);
    free(data->EA);

    // Free the map
    while (i < MAP_SIZE)
    {
        free(data->map[i]);
        data->map[i] = NULL;
        i++;
    }
    free(data->map);
    data->map = NULL;
        
}