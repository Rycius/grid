#include "ray_types.h"

#include "grid.h"

uint32 _gridShaderLocations[7];

void GridShaderInit(Shader shader, v2 screen, float size, v2 offset, v2 mouse, float zoom, v3 color, float fallOff)
{
    _gridShaderLocations[GRID_SHADER_LOCATION_SCREEN] = GetShaderLocation(shader, "screen");
    SetShaderValue(shader, _gridShaderLocations[GRID_SHADER_LOCATION_SCREEN], &screen, SHADER_UNIFORM_VEC2);
    
    _gridShaderLocations[GRID_SHADER_LOCATION_SIZE] = GetShaderLocation(shader, "size");
    SetShaderValue(shader, _gridShaderLocations[GRID_SHADER_LOCATION_SIZE], &size, SHADER_UNIFORM_FLOAT);
    
    _gridShaderLocations[GRID_SHADER_LOCATION_OFFSET] = GetShaderLocation(shader, "offset");
    SetShaderValue(shader, _gridShaderLocations[GRID_SHADER_LOCATION_OFFSET], &offset, SHADER_UNIFORM_VEC2);
    
    _gridShaderLocations[GRID_SHADER_LOCATION_MOUSE] = GetShaderLocation(shader, "mousePos");
    SetShaderValue(shader, _gridShaderLocations[GRID_SHADER_LOCATION_MOUSE], &mouse, SHADER_UNIFORM_VEC2);
    
    _gridShaderLocations[GRID_SHADER_LOCATION_ZOOM] = GetShaderLocation(shader, "zoom");
    SetShaderValue(shader, _gridShaderLocations[GRID_SHADER_LOCATION_ZOOM], &zoom, SHADER_UNIFORM_FLOAT);
    
    _gridShaderLocations[GRID_SHADER_LOCATION_COLOR] = GetShaderLocation(shader, "color");
    SetShaderValue(shader, _gridShaderLocations[GRID_SHADER_LOCATION_COLOR], &color, SHADER_UNIFORM_VEC3);
    
    _gridShaderLocations[GRID_SHADER_LOCATION_FALLOFF] = GetShaderLocation(shader, "fallOff");
    SetShaderValue(shader, _gridShaderLocations[GRID_SHADER_LOCATION_FALLOFF], &fallOff, SHADER_UNIFORM_FLOAT);
}

void GridShaderUpdate(Shader shader, float size, v2 offset, v2 mousePos, float zoom, v3 color, float fallOff)
{
    SetShaderValue(shader, _gridShaderLocations[GRID_SHADER_LOCATION_SIZE], &size, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, _gridShaderLocations[GRID_SHADER_LOCATION_OFFSET], &offset, SHADER_UNIFORM_VEC2);
    SetShaderValue(shader, _gridShaderLocations[GRID_SHADER_LOCATION_MOUSE], &mousePos, SHADER_UNIFORM_VEC2);
    SetShaderValue(shader, _gridShaderLocations[GRID_SHADER_LOCATION_ZOOM], &zoom, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, _gridShaderLocations[GRID_SHADER_LOCATION_COLOR], &color, SHADER_UNIFORM_VEC3);
    SetShaderValue(shader, _gridShaderLocations[GRID_SHADER_LOCATION_FALLOFF], &fallOff, SHADER_UNIFORM_FLOAT);
}

void GridShaderUpdateSize(Shader shader, float size)
{
    _gridShaderLocations[GRID_SHADER_LOCATION_SIZE] = GetShaderLocation(shader, "size");
    SetShaderValue(shader, _gridShaderLocations[GRID_SHADER_LOCATION_SIZE], &size, SHADER_UNIFORM_FLOAT);
}