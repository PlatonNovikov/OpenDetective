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
    if(!n->placeOfWork){
        return;
    }

    if(!((n->x == n->placeOfWork->parentFloor->parentBuilding->x) && (n->y == n->placeOfWork->parentFloor->parentBuilding->y))){
        if(!n->current.currentRoom){
            if(n->currentFloor->floorNumber == 0){
                if(!n->currentBuilding){
                    if (n->x > n->placeOfWork->parentFloor->parentBuilding->x){
                        n->x -= 1;
                    } else if (n->x < n->placeOfWork->parentFloor->parentBuilding->x){
                        n->x += 1;
                    } else if (n->y > n->placeOfWork->parentFloor->parentBuilding->y){
                        n->x -= 1;
                    } else if (n->y > n->placeOfWork->parentFloor->parentBuilding->y){
                        n->x += 1;
                    }
                } else {
                    n->currentBuilding = NULL;
                }

            } else {
                n->currentFloor = n->currentBuilding->floors[n->currentFloor->floorNumber-1];
            }
        } else {
            n->current.currentRoom = NULL;
        }
    } else {
        if (!n->currentBuilding){
            n->currentBuilding = n->currentBuilding->parentCity->cityMap[n->x][n->y];
            n->currentFloor = n->currentBuilding->parentCity->cityMap[n->x][n->y]->floors[0];
            return;
        }

        if (!(n->currentFloor->floorNumber == n->placeOfWork->parentFloor->floorNumber)){
            n->currentFloor = n->currentBuilding->floors[n->currentFloor->floorNumber+1];
        }

        if (!(n->current.currentOffice)){
            n->current.currentOffice = n->placeOfWork;
        }
    }
}