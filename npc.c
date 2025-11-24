#include "npc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "city.h"

void generate_npc(npc* new_npc, city* c) {
	snprintf(new_npc->firstName, sizeof(new_npc->firstName), "%s", first_names[rand() % ARRAY_SIZE]);
	snprintf(new_npc->lastName, sizeof(new_npc->lastName), "%s", last_names[rand() % ARRAY_SIZE]);
	new_npc->relationships = (relationship*)calloc(MAX_RELATIONSHIPS, sizeof(relationship));
	if (!new_npc->relationships) {
		printf("Error allocating memory for relationships.\n");
		free(new_npc);
		exit(1);
	}
	new_npc->relationshipCount = 0;
	new_npc->dailySchedule = (schedule*)calloc(1, sizeof(schedule));
	if (!new_npc->dailySchedule)
	{
		printf("Error allocating memory for daily schedule.\n");
		free(new_npc->relationships);
		free(new_npc);
		exit(1);
	}
	new_npc->tick = npc_tick;
	c->npcList[c->npcListCount] = new_npc;
	c->npcListCount += 1;
}

void generate_family(int count, npc** family, city* c) {
	if (!family) {
		printf("Error allocating memory for family.\n");
		exit(1);
	}
	for (int i = 0; i < count; i++){
		family[i] = (npc*)calloc(1, sizeof(npc));
		if (!family[i]) {
			printf("Error allocating memory for NPC.\n");
			exit(1);
		}
		generate_npc(family[i], c);
		strcpy(family[i]->lastName, family[0]->lastName);
	}

	for (int i = 0; i < count; i++){
		npc* n = family[i];
		for (int j = 0; j < count; j++){
			if (i == j){
				continue;
			}
			relationship* r = &n->relationships[n->relationshipCount];
			r->count = n->relationshipCount + 1;
			r->strength = 50;
			r->target = family[j];
			r->type = FAMILY;
			n->relationshipCount += 1;
		}
	}
}

void gotoWork(npc* n){
	if(!n->placeOfWork || n->currentOffice == n->placeOfWork){
		return;
	}

	if (n->currentRoom)
	{
		add_npc(n, n->currentRoom->parentFloor->current_npcs);
		remove_npc(n, n->currentRoom->current_npcs);
		n->currentRoom = NULL;
		return ;
	}
	if (n->currentFloor && (n->currentBuilding != n->placeOfWork->parentFloor->parentBuilding))
	{
		add_npc(n, n->currentFloor->parentBuilding->current_npcs);
		remove_npc(n, n->currentFloor->current_npcs);
		n->currentFloor = NULL;
		return ;
	}
	int work_x, work_y;
	work_x = n->placeOfWork->parentFloor->parentBuilding->x;
	work_y = n->placeOfWork->parentFloor->parentBuilding->y;
	if (n->currentBuilding->x != work_x || n->currentBuilding->y != work_y)
	{
		if (n->x < work_x)
			n->x++;
		else if (n->x > work_x)
			n->x--;
		else if (n->y < work_y)
			n->y++;
		else if (n->y > work_y)
			n->y--;
		remove_npc(n, n->currentBuilding->current_npcs);
		n->currentBuilding = n->currentBuilding->parentCity->cityMap[n->x][n->y];
		add_npc(n, n->currentBuilding->current_npcs);
		return ;
	}
	if (n->currentBuilding->x == work_x && n->currentBuilding->y == work_y)
	{
		n->currentFloor = n->placeOfWork->parentFloor;
		add_npc(n, n->currentFloor->current_npcs);
		remove_npc(n, n->currentBuilding->current_npcs);
		return ;
	}
	if (n->currentFloor == n->placeOfWork->parentFloor)
	{
		n->currentOffice = n->placeOfWork;
		add_npc(n, n->currentOffice->current_npcs);
		remove_npc(n, n->currentFloor->current_npcs);
		return ;
	}
}

void gotoHone(npc *n)
{
	if(!n->placeOfResidence || (n->placeOfResidence == n->currentRoom)){
		return;
	}

	if (n->currentOffice)
	{
		add_npc(n, n->currentOffice->parentFloor->current_npcs);
		remove_npc(n, n->currentOffice->current_npcs);
		n->currentOffice = NULL;
		return ;
	}
	if (n->currentFloor && (n->currentBuilding != n->placeOfResidence->parentFloor->parentBuilding))
	{
		add_npc(n, n->currentBuilding->current_npcs);
		remove_npc(n, n->currentFloor->current_npcs);
		n->currentFloor = NULL;
		return ;
	}
	int home_x, home_y;
	home_x = n->placeOfResidence->parentFloor->parentBuilding->x;
	home_y = n->placeOfResidence->parentFloor->parentBuilding->y;
	if (n->currentBuilding->x != home_x || n->currentBuilding->y != home_y)
	{
		if (n->x < home_x)
			n->x++;
		else if (n->x > home_x)
			n->x--;
		else if (n->y < home_y)
			n->y++;
		else if (n->y > home_y)
			n->y--;
		remove_npc(n, n->currentBuilding->current_npcs);
		n->currentBuilding = n->currentBuilding->parentCity->cityMap[n->x][n->y];
		add_npc(n, n->currentBuilding->current_npcs);
		return ;
	}
	if (n->currentBuilding->x == home_x && n->currentBuilding->y == home_y)
	{
		n->currentFloor = n->placeOfResidence->parentFloor;
		add_npc(n, n->currentFloor->current_npcs);
		remove_npc(n, n->currentBuilding->current_npcs);
		return ;
	}
	if (n->currentFloor == n->placeOfResidence->parentFloor)
	{
		n->currentRoom = n->placeOfResidence;
		add_npc(n, n->currentRoom->current_npcs);
		remove_npc(n, n->currentFloor->current_npcs);
		return ;
	}
}

void npc_tick(npc* n, city* c)
{
	if (!n->dailySchedule)
		return; // No schedule defined

	if (c->time >= n->dailySchedule->work_start && c->time < n->dailySchedule->work_end)
	{
		gotoWork(n);
	}
	else
	{
		gotoHone(n);
	}
}

void add_npc(npc *n, npc **npc_list)
{
	for (int i = 0; i < MAX_NPC_PRESENT; i++)
	{
		if (npc_list[i] == NULL)
		{
			npc_list[i] = n;
			return;
		}
	}
}

void remove_npc(npc *n, npc **npc_list)
{
	for (int i = 0; i < MAX_NPC_PRESENT; i++)
	{
		if (npc_list[i] == n)
		{
			npc_list[i] = NULL;
			break ;
		}
	}
	for (int i = 0; i < MAX_NPC_PRESENT - 1; i++)
	{
		if (npc_list[i] == NULL && npc_list[i + 1] != NULL)
		{
			npc_list[i] = npc_list[i + 1];
			npc_list[i + 1] = NULL;
		}
	}
}