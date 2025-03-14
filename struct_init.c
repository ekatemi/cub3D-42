#include "cub_3d.h"

void texturesInit(t_textures *t)
{
    if (!t)
        return;
    t->EA = NULL;
    t->NO = NULL;
    t->SO = NULL;
    t->WE = NULL;
}

void colorInit(t_color *c)
{
    if (!c)
        return;
    c->location = NULL;
    c->r = 0;
    c->g = 0;
    c->b = 0;
}