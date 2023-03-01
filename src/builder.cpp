#include "builder.h"

#define BUILD_ASSETS_PATH "../resources/"

build_item buildItems[1][6];
tex_atlas atlasArr[1];

void LoadBuildAssets()
{
    atlasArr[BUILD_ITEM_ROAD].texture = LoadTexture(TextFormat("%s%s", BUILD_ASSETS_PATH, "roads.png"));
    atlasArr[BUILD_ITEM_ROAD].itemCount = 6;

    buildItems[BUILD_ITEM_ROAD][ROAD_2x2_STRAIGHT] = { .atlas = &atlasArr[BUILD_ITEM_ROAD], .src = Rec(0, 0, 32, 32), .res = 100.0f };
    buildItems[BUILD_ITEM_ROAD][ROAD_2x2_BEND] = { .atlas = &atlasArr[BUILD_ITEM_ROAD], .src = Rec(32, 0, 32, 32), .res = 100.0f };
    buildItems[BUILD_ITEM_ROAD][ROAD_2x2_CROSS] = { .atlas = &atlasArr[BUILD_ITEM_ROAD], .src = Rec(64, 0, 32, 32), .res = 100.0f };
    buildItems[BUILD_ITEM_ROAD][ROAD_2x2_T] = { .atlas = &atlasArr[BUILD_ITEM_ROAD], .src = Rec(0, 32, 32, 32), .res = 100.0f };
    buildItems[BUILD_ITEM_ROAD][ROAD_2x2_1X2_SYTAIGHT] = { .atlas = &atlasArr[BUILD_ITEM_ROAD], .src = Rec(32, 32, 32, 32), .res = 100.0f };
    buildItems[BUILD_ITEM_ROAD][ROAD_2x1_STRAIGHT] = { .atlas = &atlasArr[BUILD_ITEM_ROAD], .src = Rec(64, 32, 32, 32), .res = 100.0f };
}

build_item GetBuildItem(int32 type, int32 item)
{
    return buildItems[type][item];
}

int32 BuildItemCount(int32 type)
{
    return ArrayCount((buildItems[type]));
}