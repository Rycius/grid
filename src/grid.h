/* date = February 27th 2023 10:45 pm */

#ifndef GRID_H
#define GRID_H

enum
{
    GRID_SHADER_LOCATION_SCREEN,
    GRID_SHADER_LOCATION_SIZE,
    GRID_SHADER_LOCATION_OFFSET,
    GRID_SHADER_LOCATION_MOUSE,
    GRID_SHADER_LOCATION_ZOOM,
    GRID_SHADER_LOCATION_COLOR,
    GRID_SHADER_LOCATION_FALLOFF
};

void GridShaderInit(Shader shader, v2 screen, float size, v2 offset, v2 mouse, float zoom, v3 color, float fallOff);
void GridShaderUpdate(Shader shader, v2 offset, v2 mousePos, float zoom);

#endif //GRID_H
