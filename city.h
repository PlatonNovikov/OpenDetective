#ifndef CITY_C
#define CITY_C

#include "structures.h"

#define MAX_NPC 10000

typedef struct city {
    char name[100];
    int width, height;

    building*** cityMap;
    building** residentialBuildingsList;
    building** officeBuildingsList;

    int residentialBuildings;
    int officeBuildings;

    npc** npcList;
    int npcListCount;

    int time;  // 0-23 (часы)
    int day;   // Дни с начала игры
    void (*addTime)(city* c, int hours);
} city;

void allocateFloors(building* b);

room* getFreeResidence(city* c);

office* getFreeWorkplace(city* c);

void populateCity(city* c);

void timeManager(city* c);
#endif