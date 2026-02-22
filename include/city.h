#ifndef CITY_C
#define CITY_C

#include <stdio.h>
#include <stdlib.h>

#include "structures.h"
#include "npc.h"
#include "vector.h"

#define MAX_NPC 10000
typedef struct t_city {
	char		name[100];
	unsigned	width, height;

	t_building		***cityMap;
	t_vec			*residentialBuildings; // (t_building *) list of pointers to all residential buildings
	t_vec			*officeBuildings;	// (t_building *) list of pointers to all office buildings

	t_vec			*npcList;
	t_relationship	*rel;

	size_t			time;  // minutes since start
	void			(*addTime)(t_city* self, unsigned hours);
} t_city;

void allocateFloors(t_building *b);

t_room* getFreeResidence(t_city* c);

t_office* getFreeWorkplace(t_city* c);

void populateCity(t_city* c);

void addTime(t_city* c, unsigned minutes);

size_t currentDay(t_city *c); //returns current day number
size_t currentTimeHour(t_city *c); //returns current hour
size_t currentTimeMinute(t_city *c); //returns current minute
size_t currentDayMinute(t_city *c); //returns current minute
#endif
