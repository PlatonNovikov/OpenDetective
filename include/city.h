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
	void			(*addTime)(unsigned hours);
} t_city;

void allocateFloors(t_building *b);

t_room* getFreeResidence();

t_office* getFreeWorkplace();

void populateCity();

void addTime(unsigned minutes);

size_t currentDay(void); //returns current day number
size_t currentTimeHour(void); //returns current hour
size_t currentTimeMinute(void); //returns current minute
size_t currentDayMinute(void); //returns current minute

void set_coworkers();

extern t_city *g_city;

#endif
