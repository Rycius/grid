#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform vec3 color;     // color of grid
uniform vec2 screen;    // screen size
uniform float size;     // grid cell size
uniform vec2 offset;    // begining of the grid on screen
uniform vec2 mousePos;  // mouse position
uniform float zoom;     // camera zoom
uniform float fallOff;

// Output fragment color
out vec4 finalColor;

// NOTE: Add here your custom variables
vec2 uv = screen*fragTexCoord-offset;
vec2 grid = floor(uv/(size*zoom))*size*zoom;
float dis = distance(screen*fragTexCoord, mousePos);

void main()
{
    // background
    finalColor = vec4(0.0, 0.0, 0.0, 0.0);

    if((uv.x < grid.x + 1.0) || (uv.y < grid.y + 1.0))
        finalColor = vec4(color, fallOff/dis);
}

