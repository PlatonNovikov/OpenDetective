#ifndef NPC_H
#define NPC_H

#include "structures.h"
#include "city.h"

#define MAX_RELATIONSHIPS 100

typedef enum relationship_type {
	FAMILY,
	FRIEND,
	COWORKER,
} relationship_type;

typedef struct relationship {
	npc					*target;	// Pointer to the related NPC
	relationship_type	type;		// Type of relationship
	int					strength;	// 0-100 (e.g., closeness, trust)
	int					count;		// Number of interactions
} relationship;

typedef struct schedule {
	int	work_start;
	int	work_end;
} schedule;

typedef struct npc {
	char			firstName[100];
	char			lastName[100];
	room			*placeOfResidence;
	office			*placeOfWork;
	int 			x,y;
	building		*currentBuilding;
	floor			*currentFloor;
	room			*currentRoom;
	office			*currentOffice;

	relationship	*relationships; // Dynamic array of relationships
	int				relationshipCount;

	schedule		*dailySchedule;

	void			(*tick)(struct npc* n, city* c);
} npc;

void generate_npc(npc* new_npc, city* c);

void generate_family(int count, npc** family, city* c);

void gotoWork(npc* n);

void npc_tick(npc* n, city* c);

void add_npc(npc *n, npc **npc_list);

void remove_npc(npc *n, npc **npc_list);

#endif