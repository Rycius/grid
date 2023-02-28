//TODO: store filled cellls in dictionary using cell x:y number as a key?

#define MY_DEBUG 1


#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

#include "ray_types.h"
#include "grid.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    __declspec(dllexport) unsigned long NvOptimusEnablement = 1;
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
    
#ifdef __cplusplus
}
#endif

#define CAMERA_MOVE_SPEED 400.0f
#define CAMERA_ZOOM_SPEED 5.0f

#define TEXTURE_SIZE 32

v2 ScreenToGridPos(v2 screenPos, float gridRes, Camera2D camera);

struct tex_atlas
{
    Texture2D texture;
    int32 itemCount;
};

struct build_item
{
    tex_atlas *atlas;
    Rectangle src;
    float rotation;
};

struct grid_tile
{
    Rectangle rec;
    build_item item;
};

int main() 
{
    // Initialization
    //--------------------------------------------------------------------------------------
    Rectangle screen = Rec(0.0f, 0.0f, 800.0f, 450.0f);
    
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screen.width, screen.height, "raylib");
    
    Camera2D camera = { 0 };
    camera.offset = Vec2(screen.width/2.0f, screen.height/2.0f);
    camera.target = Vec2(0.0f, 0.0f);
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    
    SetTargetFPS(120);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    
    float dt = 0.0f;
    
    
    //--------------------------------------------------------------------------------------
    
    float gridRes = 50.0f; 
    
    
    Image cellImg = GenImageColor(gridRes, gridRes, {136, 164, 124, 255});
    Texture2D cellTex = LoadTextureFromImage(cellImg);
    
    Image gridImg = GenImageColor(screen.width, screen.height, WHITE);
    Texture2D gridTex = LoadTextureFromImage(gridImg);
    
    
    //-------------------------------- SHADER SETUP --------------------------------
    
    Shader gridShader = LoadShader(0, "../resources/grid.fs");
    v2 gridValOffset = GetWorldToScreen2D(ScreenToGridPos(Vec2(0.0f, 0.0f), gridRes, camera), camera);
    v3 gridValColor = Vec3(0.11f, 0.19f, 0.37f);
    float gridValFallOff = 20.0f;
    GridShaderInit(gridShader, Vec2(screen.width, screen.height), gridRes, gridValOffset, GetMousePosition(), camera.zoom, gridValColor, gridValFallOff);
    //--------------------------------------------------------------------------------------
    
    
    grid_tile tiles[100] = {};
    int32 tilesIndex = 0;

    tex_atlas roadAtlas = {.texture = LoadTexture("../resources/roads.png"), .itemCount = 3};

    build_item buildItems[3] = {
        {.atlas = &roadAtlas, .src = Rec(0, 0, 32, 32)},
        {.atlas = &roadAtlas, .src = Rec(32, 0, 32, 32)},
        {.atlas = &roadAtlas, .src = Rec(64, 0, 32, 32)}
    };

    int32 buildItemsCount = 3;
    int32 buildItemID = 0;
    float buildItemRotation = 0.0f;
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        dt = GetFrameTime();
        
        gridValOffset = GetWorldToScreen2D(ScreenToGridPos(Vec2(0.0f, 0.0f), gridRes, camera), camera);
        
        GridShaderUpdate(gridShader, gridValOffset, GetMousePosition(), camera.zoom);
        
        //------------------------------- CAMERA ---------------------------------------------------
        v2 cameraVelocity = {};
        v2 cameraDir = {};
        
        if(IsKeyDown(KEY_W))
        {
            cameraDir.y -= 1;
        }
        if(IsKeyDown(KEY_S))
        {
            cameraDir.y += 1;
        }
        if(IsKeyDown(KEY_A))
        {
            cameraDir.x -= 1;
        }
        if(IsKeyDown(KEY_D))
        {
            cameraDir.x += 1;
        }
        
        if(GetMouseWheelMove() > 0.0f && IsKeyDown(KEY_LEFT_CONTROL))
        {
            camera.zoom = Clamp(camera.zoom+CAMERA_ZOOM_SPEED*dt, camera.zoom, 2.0f);
        }
        else if(GetMouseWheelMove() < 0.0f && IsKeyDown(KEY_LEFT_CONTROL))
        {
            camera.zoom = Clamp(camera.zoom-CAMERA_ZOOM_SPEED*dt, 0.5f, camera.zoom);
        }
        
        cameraVelocity = Vector2Scale(Vector2Normalize(cameraDir), CAMERA_MOVE_SPEED*dt);
        camera.target = Vector2Add(camera.target, cameraVelocity);
        
        //----------------------------------- BUILDING ----------------------------------------
                
        float mw = GetMouseWheelMove();
        if(!IsKeyDown(KEY_LEFT_CONTROL))
        {
            if(mw > 0.0f) ++buildItemID;
            else if(mw < 0.0f) --buildItemID;
        }

 
        if(IsMouseButtonPressed(2))
        {
            buildItemRotation += 90.0f;
            //buildItemRotation = ((int32)buildItemRotation)%360;
        }

        if(IsMouseButtonPressed(0))
        {
            tiles[tilesIndex].rec = Rec(ScreenToGridPos(GetMousePosition(), gridRes, camera), gridRes, gridRes);
            tiles[tilesIndex].rec.x += gridRes/2.0f;
            tiles[tilesIndex].rec.y += gridRes/2.0f;
            tiles[tilesIndex].item = buildItems[abs((buildItemID)%buildItemsCount)];
            tiles[tilesIndex].item.rotation = buildItemRotation;
            tilesIndex++;
        }


        
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        
        ClearBackground(RAYWHITE);
        
        BeginMode2D(camera);

        Rectangle destRec = Rec(ScreenToGridPos(GetMousePosition(), gridRes, camera), gridRes, gridRes);
        destRec.x += gridRes/2.0f;
        destRec.y += gridRes/2.0f;

        DrawTexturePro(buildItems[abs((buildItemID)%buildItemsCount)].atlas->texture, 
                        buildItems[abs((buildItemID)%buildItemsCount)].src,
                        destRec,
                        Vec2(gridRes/2.0f, gridRes/2.0f),
                        buildItemRotation,
                        WHITE);
        
        for(int32 i = 0; i < tilesIndex; ++i)
        {
            //DrawTextureEx(roadTex, tiles[i], 0.0f, 1.0f, WHITE);
            DrawTexturePro(tiles[i].item.atlas->texture, 
                            tiles[i].item.src, 
                            tiles[i].rec, 
                            Vec2(gridRes/2.0f, gridRes/2.0f), 
                            tiles[i].item.rotation, 
                            WHITE);
        }
        
        EndMode2D();
        
        BeginShaderMode(gridShader);
        DrawTextureEx(gridTex, Vec2(0.0f, 0.0f), 0.0f, 1.0f, WHITE);
        EndShaderMode();
        
        DrawFPS(10, 10);
        
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    
    return 0;
}

v2 ScreenToGridPos(v2 screenPos, float gridRes, Camera2D camera)
{
    v2 mw = GetScreenToWorld2D(screenPos, camera); // mouse world pos
    
    float x = floorf(mw.x / gridRes)*gridRes;
    float y = floorf(mw.y / gridRes)*gridRes;
    
    return Vec2(x, y);
}
