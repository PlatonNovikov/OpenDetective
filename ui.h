#ifndef UI_H
#define UI_H
#include "structures.h"

void printMap(city* c, player* p);

void printSeparator();

void clearInputBuffer();

int safeInput(int min, int max);

void handleDialogue(player* p, npc* n);

void handleResidentialRoom(player* p);

void handleEmptyRoom(player* p);

void handleResidentialFloor(player* p);

void handleOfficeFloor(player* p);

void handleBuildingInteraction(city* c, player* p);

void handleMapMovement(city* c, player* p);

void handleOutsideInteraction(city* c, player* p);

void playerControl(city* c, player* p);
#endif