#ifndef UI_H
#define UI_H

#include <stdio.h>
#include <stdlib.h>

#include "structures.h"
#include "ui.h"
#include "saveload.h"
#include "city.h"

unsigned safeInput_u(unsigned min, unsigned max);
void handle_dialogue(t_player *p, t_npc *n);
void playerControl(t_player* p);

#endif
