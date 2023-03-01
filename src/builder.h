#ifndef BUILDER_H
#define BUILDER_H

#include "game.h"

enum 
{
    BUILD_ITEM_ROAD,
    BUILD_ITEM_HUMAN,

    BUILD_ITEM_TYPE_COUNT
};

enum  // nxm   n - road directions (one way/two way)   m - laine per direction
{
    ROAD_2x2_STRAIGHT,
    ROAD_2x2_BEND,
    ROAD_2x2_CROSS,
    ROAD_2x2_T,
    ROAD_2x2_1X2_SYTAIGHT,
    ROAD_2x1_STRAIGHT,
};

enum 
{
    HUMAN_0,

};

void LoadBuildAssets(void);
build_item GetBuildItem(int32 type, int32 item);
int32 BuildItemCount(int32 type);

#endif