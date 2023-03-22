//TODO: store filled cellls in dictionary using cell x:y number as a key?
#ifdef __cplusplus
extern "C" {
#endif
    
    __declspec(dllexport) unsigned long NvOptimusEnablement = 1;
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
    
#ifdef __cplusplus
}
#endif

#define MY_DEBUG 1


#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

#include "game.h"
#include "grid.h"
#include "builder.h"

#define CAMERA_MOVE_SPEED 400.0f
#define CAMERA_ZOOM_SPEED 10.0f


Camera2D camera;
Rectangle screen;

Shader gridShader;
float gridRes = 64.00f;
v2 gridOffset = Vec2(0.0f, 0.0f);
v3 gridColor;
float gridFallOff;


void UpdateGrid()
{
    gridOffset = GetWorldToScreen2D(ScreenToGridPos(Vec2(0.0f, 0.0f), gridRes, camera), camera);
        
    GridShaderUpdate(gridShader, Vec2(screen.width, screen.height), gridRes, gridOffset, GetMousePosition(), camera.zoom, gridColor, gridFallOff);
}

int main() 
{
    // Initialization
    //--------------------------------------------------------------------------------------
    screen = Rec(0.0f, 0.0f, 800.0f, 450.0f);
    
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screen.width, screen.height, "raylib");
    
    camera = { 0 };
    camera.offset = Vec2(screen.width/2.0f, screen.height/2.0f);
    camera.target = Vec2(0.0f, 0.0f);
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    
    SetTargetFPS(120);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    
    float dt = 0.0f;
    
    
    //--------------------------------------------------------------------------------------    
        
    Image gridImg = GenImageColor(screen.width, screen.height, WHITE);
    Texture2D gridTex = LoadTextureFromImage(gridImg);
    UnloadImage(gridImg);
    
    
    //-------------------------------- GRID SHADER SETUP --------------------------------
    
    gridShader = LoadShader(0, "../resources/grid.fs");
    gridOffset = GetWorldToScreen2D(ScreenToGridPos(Vec2(0.0f, 0.0f), gridRes, camera), camera);
    gridColor = Vec3(0.11f, 0.19f, 0.37f);
    gridFallOff = 20.0f;
    GridShaderInit(gridShader, Vec2(screen.width, screen.height), gridRes, gridOffset, GetMousePosition(), camera.zoom, gridColor, gridFallOff);
    //--------------------------------------------------------------------------------------
    
    LoadBuildAssets();

    grid_tile tiles[100] = {};
    int32 tilesIndex = 0;

    build_item activeItem = GetBuildItem(0, 0);
    int32 buildItemTypeID = 0;
    int32 buildItemID = 0;
    float buildItemRotation = 0.0f;
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        dt = GetFrameTime();

        if(IsWindowResized())
        {
            screen = Rec(0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight());
            gridImg = GenImageColor(screen.width, screen.height, WHITE);
            gridTex = LoadTextureFromImage(gridImg);
        }
                
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
            camera.zoom = Clamp(camera.zoom-CAMERA_ZOOM_SPEED*dt, 0.2f, camera.zoom);
        }
        
        cameraVelocity = Vector2Scale(Vector2Normalize(cameraDir), CAMERA_MOVE_SPEED*dt);
        camera.target = Vector2Add(camera.target, cameraVelocity);
        
        //----------------------------------- BUILDING ----------------------------------------
        
        if(IsKeyPressed(KEY_ONE)) 
        { 
            buildItemTypeID = 0;
            buildItemID = 0;
        }
        else if(IsKeyPressed(KEY_TWO))
        {
            buildItemTypeID = 1;
            buildItemID = 0;
        } 

        float mw = GetMouseWheelMove();
        if(!IsKeyDown(KEY_LEFT_CONTROL))
        {
            if(mw > 0.0f) ++buildItemID;
            else if(mw < 0.0f) --buildItemID;

            if(buildItemID >= BuildItemCount(buildItemTypeID)) buildItemID = 0;
            else if(buildItemID < 0) buildItemID = BuildItemCount(buildItemTypeID) -1;
        }

        activeItem = GetBuildItem(buildItemTypeID, buildItemID);
        gridRes = activeItem.res;


        if(IsMouseButtonPressed(2))
        {
            buildItemRotation += 90.0f;
            //buildItemRotation = ((int32)buildItemRotation)%360;
        }

        if(IsMouseButtonPressed(0))
        {
            build_item item = GetBuildItem(buildItemTypeID, buildItemID);
            item.rotation = buildItemRotation;
            

            tiles[tilesIndex].rec = Rec(ScreenToGridPos(GetMousePosition(), gridRes, camera), gridRes, gridRes);
            tiles[tilesIndex].rec.x += item.res/2.0f;
            tiles[tilesIndex].rec.y += item.res/2.0f;
            tiles[tilesIndex].item = item;
            tilesIndex++;
        }

        UpdateGrid();


        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        
        ClearBackground(RAYWHITE);
        
        BeginMode2D(camera);
        
        for(int32 i = 0; i < tilesIndex; ++i)
        {
            DrawTexturePro(tiles[i].item.atlas->texture, 
                            tiles[i].item.src, 
                            tiles[i].rec, 
                            Vec2(tiles[i].item.res/2.0f, tiles[i].item.res/2.0f), 
                            tiles[i].item.rotation, 
                            WHITE);
        }

        Rectangle destRec = Rec(ScreenToGridPos(GetMousePosition(), gridRes, camera), gridRes, gridRes);
        destRec.x += gridRes/2.0f;
        destRec.y += gridRes/2.0f;
        
        
        DrawTexturePro(activeItem.atlas->texture, 
                        activeItem.src,
                        destRec,
                        Vec2(activeItem.res/2.0f, activeItem.res/2.0f),
                        buildItemRotation,
                        WHITE);
        
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
