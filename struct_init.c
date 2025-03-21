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

    data->map = NULL;

    // data->map = (char**)malloc(sizeof(char*) * (50 + 1));
    // if (!data->map)
    //     return;
    // int i = 0;
    // while (i < 51)
    // {
    //     data->map[i] = NULL;
    // }
}

void freeData(t_data *data)
{
    //int i;

    if (!data)
        return;

    // Free texture paths
    free(data->NO);
    free(data->SO);
    free(data->WE);
    free(data->EA);

    // // Free the map
    // if (data->map)
    // {
    //     i = 0;
    //     while (i < 50)
    //     {
    //         if (data->map)
    //         free(data->map[i]);
    //         data->map[i] = NULL;
    //         i++;
    //     }
    //     free(data->map);
    //     data->map = NULL;
    // }
}