#include "city.h"
#include "rand/rand.h"
//boykisser
//writing it a year later. I have no idea why i wrote "boykisser", but im leaving it here lol

// static void residential_gen(t_floor *parent_f)
// {

// }

static void floor_gen(t_building *parent_b, unsigned f_number)
{
	t_floor* f = (t_floor*)calloc(1, sizeof(t_floor));
	if (!f) {
		printf("Error allocating memory for floor.\n");
		exit(1);
	}

	f->floorNumber = f_number;
	f->parentBuilding = parent_b;

	f->current_npcs = (t_npc**)calloc(MAX_NPC_PRESENT, sizeof(t_npc*));
	if (!f->current_npcs) {
		printf("Error allocating memory for current NPCs on floor.\n");
		free(f);
		exit(1);
	}

	switch (parent_b->building_type) {
		case RESIDENTIAL:
			f->floorType = RESIDENTIAL;
			f->floorTypeData.residentialFloorData = (t_residentialFloor*)calloc(1, sizeof(t_residentialFloor));
			//printf("Allocating memory for residential floor data...\n");
			if (!f->floorTypeData.residentialFloorData) {
				printf("Error allocating memory for residential floor data.\n");
				free(f);
				exit(1);
			}
			f->floorTypeData.residentialFloorData->room_count = 4;
			f->floorTypeData.residentialFloorData->rooms = (t_room**)calloc(4, sizeof(t_room*));
			//printf("Allocating memory for rooms...\n");
			if (!f->floorTypeData.residentialFloorData->rooms) {
				printf("Error allocating memory for rooms.\n");
				free(f->floorTypeData.residentialFloorData);
				free(f);
				exit(1);
			}
			for (unsigned j = 0; j < 4; j++) {
				t_room* r = (t_room*)calloc(1, sizeof(t_room));
				if (!r) {
					printf("Error allocating memory for room.\n");
					for (unsigned k = 0; k < j; k++) {
						free(f->floorTypeData.residentialFloorData->rooms[k]);
					}
					free(f->floorTypeData.residentialFloorData->rooms);
					free(f->floorTypeData.residentialFloorData);
					free(f);
					exit(1);
				}
				r->npcs = (t_npc**)calloc(4, sizeof(t_npc*));
				if (!r->npcs) {
					printf("Error allocating memory for NPCs.\n");
					free(r);
					for (unsigned k = 0; k < j; k++) {
						free(f->floorTypeData.residentialFloorData->rooms[k]);
					}
					free(f->floorTypeData.residentialFloorData->rooms);
					free(f->floorTypeData.residentialFloorData);
					free(f);
					exit(1);
				}
				r->current_npcs = (t_npc**)calloc(MAX_NPC_PRESENT, sizeof(t_npc*));
				if (!r->current_npcs) {
					printf("Error allocating memory for current NPCs.\n");
					free(r->npcs);
					free(r);
					for (unsigned k = 0; k < j; k++) {
						free(f->floorTypeData.residentialFloorData->rooms[k]);
					}
					free(f->floorTypeData.residentialFloorData->rooms);
					free(f->floorTypeData.residentialFloorData);
					free(f);
					exit(1);
				}
				r->npc_count = 0;
				for(unsigned k = 0; k < 4; k++){
					r->npcs[k] = NULL;
				}
				r->parentFloor = f;
				r->room_number = j;
				f->floorTypeData.residentialFloorData->rooms[j] = r;
			}
			break;

		case OFFICE:
			f->floorType = OFFICE;
			//printf("Allocating memory for office floor data...\n");
			f->floorTypeData.officeFloorData = calloc(1, sizeof(t_officeFloor));
			if (!f->floorTypeData.officeFloorData) {
				printf("Error allocating memory for office floor data.\n");
				free(f);
				exit(1);
			}
			t_officeFloor* of = f->floorTypeData.officeFloorData;
			of->office_count = 3;
			of->parentFloor = f;
			of->offices = calloc(of->office_count, sizeof(t_office*));
			if (!of->offices) {
				printf("Error allocating memory for offices.\n");
				free(of);
				exit(1);
			}

			for (unsigned j = 0; j < of->office_count; j++) {
				//printf("Allocating memory for office...\n");
				of->offices[j] = calloc(1, sizeof(t_office));
				of->offices[j]->parentFloor = f;
				if (!of->offices[j]) {
					printf("Error allocating memory for office.\n");
					exit(1);
				}
				of->offices[j]->employee_count = 0;
				of->offices[j]->employees = (t_npc**)calloc(5, sizeof(t_npc*));
				if (!of->offices[j]->employees) {
					printf("Error allocating memory for employees.\n");
					free(of->offices[j]);
					exit(1);
				}
				of->offices[j]->current_npcs = (t_npc**)calloc(MAX_NPC_PRESENT, sizeof(t_npc*));
				if (!of->offices[j]->current_npcs)
				{
					printf("Error allocating memory for current NPCs in office.\n");
					free(of->offices[j]->employees);
					free(of->offices[j]);
					exit(1);
				}
				of->offices[j]->office_number = j;
			}
			break;
		default:
			printf("Unknown building type.\n");
			free(f);
			exit(1);
		}
	parent_b->floors[f_number] = f;
}

void allocateFloors(t_building* b) {
	//printf("Allocating memory for floors...\n");
	b->floors = (t_floor**)calloc(b->height, sizeof(t_floor*));
	if (!b->floors) {
		printf("Error allocating memory for floors.\n");
		exit(1);
	}

	for (unsigned i = 0; i < b->height; i++) {
		floor_gen(b, i);
	}
	//printf("Done!\n");
}

t_room* getFreeResidence(t_city* c){
	unsigned countC = (unsigned)zurand() % c->residentialBuildings;
	unsigned countB = countC;
	unsigned floorC = (unsigned)zurand() % c->residentialBuildingsList[countC]->height;
	unsigned floorB = floorC;
	unsigned roomC = (unsigned)zurand() % 4;
	unsigned roomB = roomC;
	while (c->residentialBuildingsList[countC]->floors[floorC]->floorTypeData.residentialFloorData->rooms[roomC]->npcs[0]){
		if (roomC < 3){
			roomC++;
		} else {
			roomC = 0;
			if (floorC < c->residentialBuildingsList[countC]->height - 1){
				floorC++;
			} else {
				floorC = 0;
				if (countC < c->residentialBuildings - 1){
					countC++;
				} else {
					countC = 0;
				}
			}
		}
		if (countC == countB && floorC == floorB && roomC == roomB){
			return NULL;
		}
	}
	return c->residentialBuildingsList[countC]->floors[floorC]->floorTypeData.residentialFloorData->rooms[roomC];
}

t_office* getFreeWorkplace(t_city* c){
	unsigned countC = (unsigned)zurand() % c->officeBuildings;
	unsigned countB = countC;
	unsigned floorC = (unsigned)zurand() % c->officeBuildingsList[countC]->height;
	unsigned floorB = floorC;
	unsigned officeC = (unsigned)zurand() % c->officeBuildingsList[countC]->floors[floorC]->floorTypeData.officeFloorData->office_count;
	unsigned officeB = officeC;
	while (c->officeBuildingsList[countC]->floors[floorC]->floorTypeData.officeFloorData->offices[officeC]->employee_count == 5){
		if (officeC < c->officeBuildingsList[countC]->floors[floorC]->floorTypeData.officeFloorData->office_count - 1){
			officeC++;
		} else {
			officeC = 0;
			if (floorC < c->officeBuildingsList[countC]->height - 1){
				floorC++;
			} else {
				floorC = 0;
				if (countC < c->officeBuildings - 1){
					countC++;
				} else {
					countC = 0;
				}
			}
		}
		if (countC == countB && floorC == floorB && officeC == officeB){
			return NULL;
		}
	}
	return c->officeBuildingsList[countC]->floors[floorC]->floorTypeData.officeFloorData->offices[officeC];
}

void populateCity(t_city* c){
	for (unsigned i = 0; i < c->residentialBuildings; i++){
		for (unsigned j = 0; j < c->residentialBuildingsList[i]->height; j++){
			for (unsigned k = 0; k < c->residentialBuildingsList[i]->floors[j]->floorTypeData.residentialFloorData->room_count; k++){
				t_room* r = c->residentialBuildingsList[i]->floors[j]->floorTypeData.residentialFloorData->rooms[k];
				if(rand()%4){
					t_npc* new_npc = (t_npc*)calloc(1, sizeof(t_npc));
					if (!new_npc) {
						printf("Error allocating memory for NPC.\n");
						exit(1);
					}
					generate_npc(new_npc, c);
					new_npc->placeOfResidence = getFreeResidence(c);
					new_npc->placeOfResidence->npcs[0] = new_npc;
					new_npc->placeOfResidence->npc_count = 1;
					new_npc->x = new_npc->placeOfResidence->parentFloor->parentBuilding->x;
					new_npc->y = new_npc->placeOfResidence->parentFloor->parentBuilding->y;
					new_npc->placeOfWork = getFreeWorkplace(c);
					new_npc->currentRoom = new_npc->placeOfResidence;
					new_npc->currentFloor = new_npc->placeOfResidence->parentFloor;
					new_npc->currentBuilding = new_npc->placeOfResidence->parentFloor->parentBuilding;
					add_npc(new_npc, r->current_npcs);
					if (new_npc->placeOfWork)
					{
						new_npc->placeOfWork->employees[new_npc->placeOfWork->employee_count] = new_npc;
						new_npc->dailySchedule->work_start = 9 * 60;	//9:00
						new_npc->dailySchedule->work_end = 17 * 60;		//17:00
						new_npc->placeOfWork->employee_count++;
					}
				}
				else{
					t_npc** family = (t_npc**)calloc(4, sizeof(t_npc*));
					unsigned count = (unsigned)zurand() % 3 + 2;
					if (!family) {
						printf("Error allocating memory for family.\n");
						exit(1);
					}
					generate_family(count, family, c);
					family[0]->placeOfResidence = getFreeResidence(c);
					family[0]->placeOfResidence->npcs = family;
					family[0]->placeOfResidence->npc_count = count;
					for (unsigned l = 0; l < count; l++)
					{
						add_npc(family[l], r->current_npcs);
						family[l]->x = family[0]->placeOfResidence->parentFloor->parentBuilding->x;
						family[l]->y = family[0]->placeOfResidence->parentFloor->parentBuilding->y;
						family[l]->placeOfResidence = family[0]->placeOfResidence;
						family[l]->placeOfWork = getFreeWorkplace(c);
						family[l]->currentRoom = r;
						family[l]->currentFloor = family[l]->placeOfResidence->parentFloor;
						family[l]->currentBuilding = family[l]->placeOfResidence->parentFloor->parentBuilding;
						if (family[l]->placeOfWork)
						{
							family[l]->placeOfWork->employees[family[l]->placeOfWork->employee_count] = family[l];
							family[l]->placeOfWork->employee_count++;
							family[l]->dailySchedule->work_start = 9 * 60;	//9:00
							family[l]->dailySchedule->work_end = 17 * 60;	//17:00
						}
					}

				}
			}
		}
	}
}

void timeManager(t_city* c)
{
	t_npc *n = NULL;

	for (unsigned i = 0; i < c->npcListCount; i++)
	{
		n = c->npcList[i];
		n->tick(n, c);
	}
}

void addTime(t_city* c, unsigned minutes)
{
	for (unsigned i = 0; i < minutes; i++){
		c->time += 1;
		timeManager(c);
	}
}

size_t currentDay(t_city *c) //returns current day number
{
	return (c->time / (60 * 24));
}

size_t currentTimeHour(t_city *c) //returns current hour
{
	return ((c->time / 60) % 24);
}


size_t currentTimeMinute(t_city *c) //returns current minute
{
	return (c->time % 60);
}

size_t currentDayMinute(t_city *c) //returns current minute
{
	return (c->time % (60 * 24));
}
