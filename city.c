#include "city.h"
#include "structures.h"
#include "npc.h"
#include <stdio.h>
#include <stdlib.h>
//boykisser
//writing it a year later. I have no idea why i wrote "boykisser", but im leaving it here lol

void allocateFloors(building* b) {
	//printf("Allocating memory for floors...\n");
	b->floors = (floor**)calloc(b->height, sizeof(floor*));
	if (!b->floors) {
		printf("Error allocating memory for floors.\n");
		exit(1);
	}

	for (int i = 0; i < b->height; i++) {
		floor* f = (floor*)calloc(1, sizeof(floor));
		if (!f) {
			printf("Error allocating memory for floor.\n");
			exit(1);
		}
		f->floorNumber = i;
		f->parentBuilding = b;
		f->current_npcs = (npc**)calloc(MAX_NPC_PRESENT, sizeof(npc*));
		if (!f->current_npcs) {
			printf("Error allocating memory for current NPCs on floor.\n");
			free(f);
			exit(1);
		}

		//printf("Allocating memory for floor type data...\n");

		switch (b->building_type) {
		case RESIDENTIAL:
			f->floorType = RESIDENTIAL;
			f->floorTypeData.residentialFloorData = (residentialFloor*)calloc(1, sizeof(residentialFloor));
			//printf("Allocating memory for residential floor data...\n");
			if (!f->floorTypeData.residentialFloorData) {
				printf("Error allocating memory for residential floor data.\n");
				free(f);
				exit(1);
			}
			f->floorTypeData.residentialFloorData->room_count = 4;
			f->floorTypeData.residentialFloorData->rooms = (room**)calloc(4, sizeof(room*));
			//printf("Allocating memory for rooms...\n");
			if (!f->floorTypeData.residentialFloorData->rooms) {
				printf("Error allocating memory for rooms.\n");
				free(f->floorTypeData.residentialFloorData);
				free(f);
				exit(1);
			}
			for (int j = 0; j < 4; j++) {
				room* r = (room*)calloc(1, sizeof(room));
				if (!r) {
					printf("Error allocating memory for room.\n");
					for (int k = 0; k < j; k++) {
						free(f->floorTypeData.residentialFloorData->rooms[k]);
					}
					free(f->floorTypeData.residentialFloorData->rooms);
					free(f->floorTypeData.residentialFloorData);
					free(f);
					exit(1);
				}
				r->npcs = (npc**)calloc(4, sizeof(npc*));
				if (!r->npcs) {
					printf("Error allocating memory for NPCs.\n");
					free(r);
					for (int k = 0; k < j; k++) {
						free(f->floorTypeData.residentialFloorData->rooms[k]);
					}
					free(f->floorTypeData.residentialFloorData->rooms);
					free(f->floorTypeData.residentialFloorData);
					free(f);
					exit(1);
				}
				r->current_npcs = (npc**)calloc(MAX_NPC_PRESENT, sizeof(npc*));
				if (!r->current_npcs) {
					printf("Error allocating memory for current NPCs.\n");
					free(r->npcs);
					free(r);
					for (int k = 0; k < j; k++) {
						free(f->floorTypeData.residentialFloorData->rooms[k]);
					}
					free(f->floorTypeData.residentialFloorData->rooms);
					free(f->floorTypeData.residentialFloorData);
					free(f);
					exit(1);
				}
				r->npc_count = 0;
				for(int k = 0; k < 4; k++){
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
			f->floorTypeData.officeFloorData = (officeFloor*)calloc(1, sizeof(officeFloor));
			if (!f->floorTypeData.officeFloorData) {
				printf("Error allocating memory for office floor data.\n");
				free(f);
				exit(1);
			}
			officeFloor* of = f->floorTypeData.officeFloorData;
			of->office_count = 3;
			of->parentFloor = f;
			of->offices = (office**)calloc(of->office_count, sizeof(office*));
			if (!of->offices) {
				printf("Error allocating memory for offices.\n");
				free(of);
				exit(1);
			}

			for (int j = 0; j < of->office_count; j++) {
				//printf("Allocating memory for office...\n");
				of->offices[j] = (office*)calloc(1, sizeof(office));
				of->offices[j]->parentFloor = f;
				if (!of->offices[j]) {
					printf("Error allocating memory for office.\n");
					exit(1);
				}
				of->offices[j]->employee_count = 0;
				of->offices[j]->employees = (npc**)calloc(5, sizeof(npc*));
				if (!of->offices[j]->employees) {
					printf("Error allocating memory for employees.\n");
					free(of->offices[j]);
					exit(1);
				}
				of->offices[j]->current_npcs = (npc**)calloc(MAX_NPC_PRESENT, sizeof(npc*));
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
		b->floors[i] = f;
	}
	//printf("Done!\n");
}

room* getFreeResidence(city* c){
	int countC = rand() % c->residentialBuildings;
	int countB = countC;
	int floorC = rand() % c->residentialBuildingsList[countC]->height;
	int floorB = floorC;
	int roomC = rand() % 4;
	int roomB = roomC;
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

office* getFreeWorkplace(city* c){
	int countC = rand() % c->officeBuildings;
	int countB = countC;
	int floorC = rand() % c->officeBuildingsList[countC]->height;
	int floorB = floorC;
	int officeC = rand() % c->officeBuildingsList[countC]->floors[floorC]->floorTypeData.officeFloorData->office_count;
	int officeB = officeC;
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

void populateCity(city* c){
	for (int i = 0; i < c->residentialBuildings; i++){
		for (int j = 0; j < c->residentialBuildingsList[i]->height; j++){
			for (int k = 0; k < c->residentialBuildingsList[i]->floors[j]->floorTypeData.residentialFloorData->room_count; k++){
				room* r = c->residentialBuildingsList[i]->floors[j]->floorTypeData.residentialFloorData->rooms[k];
				if(rand()%4){
					npc* new_npc = (npc*)calloc(1, sizeof(npc));
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
					new_npc->currentRoom = r;
					new_npc->currentFloor = r->parentFloor;
					new_npc->currentBuilding = r->parentFloor->parentBuilding;
					add_npc(new_npc, r->current_npcs);
					if (new_npc->placeOfWork){
						new_npc->placeOfWork->employees[new_npc->placeOfWork->employee_count] = new_npc;
						new_npc->dailySchedule->work_start = 9;
						new_npc->dailySchedule->work_end = 17;
						new_npc->placeOfWork->employee_count++;
					}
				}
				else{
					npc** family = (npc**)calloc(4, sizeof(npc*));
					int count = rand() % 3 + 2;
					if (!family) {
						printf("Error allocating memory for family.\n");
						exit(1);
					}
					generate_family(count, family, c);
					family[0]->placeOfResidence = getFreeResidence(c);
					family[0]->placeOfResidence->npcs = family;
					family[0]->placeOfResidence->npc_count = count;
					for (int l = 0; l < count; l++)
					{
						add_npc(family[l], r->current_npcs);
						family[l]->x = family[0]->placeOfResidence->parentFloor->parentBuilding->x;
						family[l]->y = family[0]->placeOfResidence->parentFloor->parentBuilding->y;
						family[l]->placeOfResidence = family[0]->placeOfResidence;
						family[l]->placeOfWork = getFreeWorkplace(c);
						family[l]->currentRoom = r;
						if (family[l]->placeOfWork){
							family[l]->placeOfWork->employees[family[l]->placeOfWork->employee_count] = family[l];
							family[l]->placeOfWork->employee_count++;
						}
					}

				}
			}
		}
	}
}

void timeManager(city* c)
{
	for (int i = 0; i  < c->npcListCount; i++)
	{
		npc* n = c->npcList[i];
		n->tick(n, c);
	}
}

void addTime(city* c, int hours)
{
	for (int i = 0; i < hours; i++){
		c->time += 1;
		if (c->time >= 24){
			c->time = 0;
			c->day += 1;
		}
		timeManager(c);
	}
}