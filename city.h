#ifndef CITY_C
#define CITY_C

#include "structures.h"

#define MAX_NPC 10000

typedef struct t_city {
	char		name[100];
	int			width, height;

	t_building	***cityMap;
	t_building	**residentialBuildingsList;
	t_building	**officeBuildingsList;

	int			residentialBuildings;
	int			officeBuildings;

	t_npc		**npcList;
	int			npcListCount;

	int			time;  // 0-23 (часы)
	int			day;   // Дни с начала игры
	void		(*addTime)(t_city* c, int hours);
} t_city;

void allocateFloors(t_building* b);

t_room* getFreeResidence(t_city* c);

t_office* getFreeWorkplace(t_city* c);

void populateCity(t_city* c);

void addTime(t_city* c, int hours);

#endif