#include "structures.h"
#include <stdio.h>
#include "ui.h"
#include "saveload.h"

void printMap(city* c, player* p) {
    printf("\n\033[36m%s City Map\033[0m\n", c->name); // Cyan city name
    printf("╔");
    for(int i = 0; i < c->width; i++) {
        printf("═══");
        if (i < c->width - 1) {
            printf("╦");
        }
    }
    printf("╗\n");
    for (int i = 0; i < c->height; i++) {
        for (int j = 0; j < c->width; j++) {
            printf("║ "); // Vertical separator
            if (p->x == i && p->y == j) {
                printf("\033[1;31m☺\033[0m"); // Bold red player
            } else if (c->cityMap[i][j]) {
                switch (c->cityMap[i][j]->building_type) {
                    case RESIDENTIAL: 
                        printf("\033[32m⌂\033[0m"); // Green house
                        break;
                    case OFFICE: 
                        printf("\033[34mF\033[0m"); // Blue office
                        break;
                    default: 
                        printf("?");
                        break;
                }
            } else {
                printf("·"); // Middle dot for empty
            }
            printf(" ");
        }
        printf("║\n");
        if (i < c->height - 1) {
            printf("╠");
            for (int j = 0; j < c->width; j++) {
                printf("═══");
                if (j < c->width - 1) {
                    printf("╬");
                }
            }
            printf("╣\n");
        }
    }
    printf("╚");
    for (int i = 0; i < c->width; i++) {
        printf("═══");
        if (i < c->width - 1) {
            printf("╩");
        }
    }
    printf("╝\n");
    printf("\n\033[33mLegend:\033[0m ☺=You | ⌂=Home | F=Office | ·=Empty\n\n");
}

void printSeparator() {
    printf("\n\033[35m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m\n");
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int safeInput(int min, int max) {
    int choice;
    while(1) {
        if(scanf("%d", &choice) == 1) {
            if(choice >= min && choice <= max) {
                clearInputBuffer();
                return choice;
            }
        }
        clearInputBuffer();
        printf("Invalid input. Please enter a number between %d-%d: ", min, max);
    }
}

void handleDialogue(player* p, npc* n) {
    printf("\n🗨️ \033[1m%s %s\033[0m\n", n->firstName, n->lastName);
    printf("1. Ask about work\n");
    printf("2. Ask about family\n");
    printf("3. Ask about hobbies\n");
    printf("4. Say goodbye\n» Choice: ");
    int choice = safeInput(1, 4);
    clear();
    switch(choice) {
        case 1:
            printf("%s %s says: 'I work at %s.'\n", n->firstName, n->lastName, n->placeOfWork->name);
            break;
        case 2:
            printf("%s %s says: 'I live at %s.'\n", n->firstName, n->lastName, n->placeOfResidence->parentFloor->parentBuilding->name);
            break;
        case 3:
            printf("%s %s says: 'I like to read books.'\n", n->firstName, n->lastName);
            break;
        case 4:
            printf("%s %s says: 'Goodbye!'\n", n->firstName, n->lastName);
            break;
    }
}

// Подфункции для разных состояний игры
void handleResidentialRoom(player* p) {
    room* r = p->currentRoom;

    if(r->npc_count > 1){
        printf("\n👥 \033[1m%s's Room\033[0m\n", r->npcs[0]->lastName);
        printf("1. Talk to %s's\n", r->npcs[0]->lastName);
    } else {
        printf("\n👤 \033[1m%s %s's Room\033[0m\n", r->npcs[0]->firstName, r->npcs[0]->lastName);
        printf("1. Talk to %s\n", r->npcs[0]->firstName);
    }

    printf("2. Search the room\n");
    printf("3. Leave\n» Choice: ");
    
    int choice = safeInput(1, 3);
    clear();
    
    switch(choice) {
        case 1:
            if (r->npc_count == 1) {
                handleDialogue(p, r->npcs[0]);
            } else {
                for (int i = 0; i < r->npc_count; i++) {
                    printf("%d. Talk to %s %s\n", i + 1, r->npcs[i]->firstName, r->npcs[i]->lastName);
                }
                printf("%d. Leave\n» Choice: ", r->npc_count + 1);
                int npcChoice = safeInput(1, r->npc_count + 1);
                clear();
                if (npcChoice == r->npc_count + 1) {
                    break;
                }
                handleDialogue(p, r->npcs[npcChoice - 1]);
            }
            break;
        case 2:
            printf("\n🔍 You find dusty code snippets and a half-eaten pizza.\n");
            break;
        case 3:
            p->currentRoom = NULL;
            break;
    }
} 

void handleEmptyRoom(player* p){
    printf("\n🚪 Empty Room\n");
    printf("1. Search the room\n");
    printf("2. Leave\n» Choice: ");
    int choice = safeInput(1, 2);
    clear();

    switch(choice) {
        case 1:
            printf("\n🔍 You find nothing but dust and a flickering light.\n");
            break;
        case 2:
            p->currentRoom = NULL;
            break;
    }
}

void handleResidentialFloor(player* p) {
    printf("\n🏠 Floor Menu:\n");
    printf("1. Enter a room (1-4)\n");
    printf("2. Exit building\n");
    printf("3. Switch floor\n» Choice: ");
    
    int choice = safeInput(1, 3);
    clear();
    
    switch(choice) {
        case 1: {
            printf("Enter room number: ");
            int roomChoice = safeInput(1, 4);
            residentialFloor* resFloor = (residentialFloor*)p->currentFloor->floor_type_data;
            
            if(resFloor) {
                p->currentRoom = resFloor->rooms[roomChoice - 1];
            } else {
                printf("Invalid floor data.\n");
            }
            break;
        }
        case 2:
            p->currentFloor = NULL;
            p->currentBuilding = NULL;
            break;
        case 3: {
            printf("Choose a floor (1-%d):\n", p->currentBuilding->height);
            for(int i = 0; i < p->currentBuilding->height; i++) {
                printf("%d. Floor %d\n", i + 1, i + 1);
            }
            int floorChoice = safeInput(1, p->currentBuilding->height);
            p->currentFloor = p->currentBuilding->floors[floorChoice - 1];
            break;
        }
    }
}

void handleOfficeFloor(player* p) {
    printf("\n🏢 Office Floor\n");
    printf("1. Exit building\n");
    printf("2. List companies\n");
    printf("3. Switch floor\n» Choice: ");
    
    int choice = safeInput(1, 3);
    clear();
    
    switch(choice) {
        case 1:
            p->currentFloor = NULL;
            p->currentBuilding = NULL;
            break;
        case 2: {
            officeFloor* officeFlr = (officeFloor*)p->currentFloor->floor_type_data;
            if(!officeFlr) break;

            printf("Choose an office:\n");
            for(int i = 0; i < officeFlr->office_count; i++) {
                printf("%d. %s\n", i + 1, officeFlr->offices[i]->name);
            }
            int officeChoice = safeInput(1, officeFlr->office_count);
            office* o = officeFlr->offices[officeChoice - 1];

            printf("Employees of %s:\n", o->name);
            for(int i = 0; i < o->employee_count; i++) {
                printf("%d. %s %s\n", i + 1, o->employees[i]->firstName, o->employees[i]->lastName);
            }
            int empChoice = safeInput(1, o->employee_count);
            npc* n = o->employees[empChoice - 1];

            printf("1. Talk to %s %s\n", n->firstName, n->lastName);
            printf("2. Leave\n» Choice: ");
            int action = safeInput(1, 2);
            
            if(action == 1) {
                printf("%s %s says: 'Hello! Welcome to my office.'\n", 
                      n->firstName, n->lastName);
            }
            break;
        }
        case 3: {
            printf("Choose a floor (1-%d):\n", p->currentBuilding->height);
            for(int i = 0; i < p->currentBuilding->height; i++) {
                printf("%d. Floor %d\n", i + 1, i + 1);
            }
            int floorChoice = safeInput(1, p->currentBuilding->height);
            p->currentFloor = p->currentBuilding->floors[floorChoice - 1];
            break;
        }
    }
}

void handleBuildingInteraction(city* c, player* p) {
    printSeparator();
    printf("📍 \033[1m%s\033[0m | Floor: %d\n", 
          p->currentBuilding->name, 
          p->currentFloor->floorNumber + 1);
    printSeparator();

    if(p->currentRoom) {
        printf("%d", p->currentRoom->npc_count);
        if (p->currentRoom->npc_count > 0) {
            handleResidentialRoom(p);
        } else {
            handleEmptyRoom(p);
        }
    } else {
        switch(p->currentFloor->floor_type) {
            case RESIDENTIAL:
                handleResidentialFloor(p);
                break;
            case OFFICE:
                handleOfficeFloor(p);
                break;
        }
    }
}

void handleMapMovement(city* c, player* p) {
    printf("1. North 🡹\n2. South 🡻\n3. West 🡸\n4. East 🡺\n» ");
    int dir = safeInput(1, 4);
    
    switch(dir) {
        case 1:
            if(p->x > 0) p->x--;
            else printf("You're at the city's northern edge!\n");
            break;
        case 2:
            if(p->x < c->height - 1) p->x++;
            else printf("You're at the city's southern edge!\n");
            break;
        case 3: 
            if(p->y > 0) p->y--;
            else printf("You're at the city's western edge!\n");
            break;
        case 4:
            if(p->y < c->width - 1) p->y++;
            else printf("You're at the city's eastern edge!\n");
            break;
    }
}

void handleOutsideInteraction(city* c, player* p) {
    printSeparator();
    printf("🌆 You're at \033[1m%s\033[0m\n", c->cityMap[p->x][p->y]->name);
    printSeparator();
    
    printf("1. Enter building\n");
    printf("2. Move\n");
    printf("3. View map\n»");
    printf("4. Save\n» Choice: ");
    
    int choice = safeInput(1, 4);
    clear();
    
    switch(choice) {
        case 1:
            if(c->cityMap[p->x][p->y]) {
                p->currentBuilding = c->cityMap[p->x][p->y];
                p->currentFloor = p->currentBuilding->floors[0]; // Start at ground floor
            } else {
                printf("There is no building here.\n");
            }
            break;
        case 2:
            handleMapMovement(c, p);
            break;
        case 3:
            printMap(c, p);
            break;
        case 4:
            makeSavefile(c, p);
            break;
    }
}

// Основная функция
void playerControl(city* c, player* p) {
    if(p->currentBuilding) {
        handleBuildingInteraction(c, p);
    } else {
        handleOutsideInteraction(c, p);
    }
}