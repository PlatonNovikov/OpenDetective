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
    npc* target;                // Pointer to the related NPC
    relationship_type type;     // Type of relationship
    int strength;               // 0-100 (e.g., closeness, trust)
    int count;                  // Number of interactions
} relationship;

typedef struct schedule {

} schedule;

typedef struct npc {
    char firstName[100];
    char lastName[100];
    room* placeOfResidence;
    office* placeOfWork;
    int x,y;
    building* currentBuilding;
    floor* currentFloor;
    union {
        room* currentRoom;
        office* currentOffice;
    }current;

    relationship* relationships; // Dynamic array of relationships
    int relationshipCount;
} npc;

void generate_npc(npc* new_npc, city* c);

void generate_family(int count, npc** family, city* c);

void gotoWork(npc* n);

#endif