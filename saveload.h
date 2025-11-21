#ifndef SAVELOAD_H
#define SAVELOAD_H

#include "structures.h"
#include "city.h"
#include "npc.h"

void makeSavefile(city* c, player* p);
void loadSavefile(city* c, player* p);

#endif