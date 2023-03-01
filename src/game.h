#ifndef GAME_H
#define GAME_H


#include "ray_types.h"

#define TEXTURE_SIZE 32

struct tex_atlas
{
    Texture2D texture;
    int32 itemCount;
};

struct build_item
{
    tex_atlas *atlas;
    Rectangle src;
    float res; // resolution
    float rotation;
};

struct grid_tile
{
    Rectangle rec;
    build_item item;
};

v2 ScreenToGridPos(v2 screenPos, float gridRes, Camera2D camera);

#endif // GAME_H