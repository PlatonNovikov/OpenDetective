#ifndef SAVELOAD_H
#define SAVELOAD_H

#include "structures.h"
#include "city.h"
#include "npc.h"

void makeSavefile(t_city* c, t_player* p);
void loadSavefile(t_city* c, t_player* p);

#endif