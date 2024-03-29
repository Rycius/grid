#include "builder.h"

#define BUILD_ASSETS_PATH "../resources/"

build_item buildItems[2][4]; // BUG: bug - not all atlasses will have same amount of items
tex_atlas atlasArr[2];

void LoadBuildAssets()
{
    atlasArr[BUILD_ITEM_ROAD].texture = LoadTexture(TextFormat("%s%s", BUILD_ASSETS_PATH, "master.png"));
    atlasArr[BUILD_ITEM_ROAD].itemCount = 1;
    buildItems[BUILD_ITEM_ROAD][ROAD_2x2_STRAIGHT] = { .atlas = &atlasArr[BUILD_ITEM_ROAD], .src = Rec(0, 32, 72, 72), .res = 576.00f };
    buildItems[BUILD_ITEM_ROAD][ROAD_2x2_BEND] = { .atlas = &atlasArr[BUILD_ITEM_ROAD], .src = Rec(72, 32, 72, 72), .res = 576.0f };
    buildItems[BUILD_ITEM_ROAD][ROAD_2x2_CROSS] = { .atlas = &atlasArr[BUILD_ITEM_ROAD], .src = Rec(144, 32, 72, 72), .res = 576.0f };
    buildItems[BUILD_ITEM_ROAD][ROAD_2x2_T] = { .atlas = &atlasArr[BUILD_ITEM_ROAD], .src = Rec(216, 32, 72, 72), .res = 576.0f };
    
    atlasArr[BUILD_ITEM_HUMAN].texture = LoadTexture(TextFormat("%s%s", BUILD_ASSETS_PATH, "master.png"));
    buildItems[BUILD_ITEM_HUMAN][HUMAN_0] = { .atlas = &atlasArr[BUILD_ITEM_HUMAN], .src = Rec(0, 0, 31, 31), .res = 32.0f };

    // atlasArr[BUILD_ITEM_ROAD].texture = LoadTexture(TextFormat("%s%s", BUILD_ASSETS_PATH, "roads.png"));
    // atlasArr[BUILD_ITEM_ROAD].itemCount = 6;

    // buildItems[BUILD_ITEM_ROAD][ROAD_2x2_1X2_SYTAIGHT] = { .atlas = &atlasArr[BUILD_ITEM_ROAD], .src = Rec(32, 32, 32, 32), .res = 384.0f };
    // buildItems[BUILD_ITEM_ROAD][ROAD_2x1_STRAIGHT] = { .atlas = &atlasArr[BUILD_ITEM_ROAD], .src = Rec(64, 32, 32, 32), .res = 384.0f };

    // atlasArr[BUILD_ITEM_HUMAN].texture = LoadTexture(TextFormat("%s%s", BUILD_ASSETS_PATH, "humans.png"));
    // atlasArr[BUILD_ITEM_HUMAN].itemCount = 1;

    // buildItems[BUILD_ITEM_HUMAN][HUMAN_0] = { .atlas = &atlasArr[BUILD_ITEM_HUMAN], .src = Rec(0, 0, 32, 32), .res = 32.0f };
}

build_item GetBuildItem(int32 type, int32 item)
{
    return buildItems[type][item];
}

int32 BuildItemCount(int32 type)
{
    return ArrayCount((buildItems[type]));
}