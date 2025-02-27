#include "saveload.h"
#include "stdio.h"
#include <stdlib.h>
#include <string.h>

void makeSavefile(city* c, player* p) {
    FILE* savefile = fopen("savefile.txt", "w");
    if (!savefile) {
        printf("Error opening savefile.\n");
        exit(1);
    }

    // Сохраняем данные города
    fprintf(savefile, "CITYDATA\n%s\n%d %d\n%d %d\n%d %d\n",
        c->name, c->width, c->height, c->residentialBuildings, c->officeBuildings, c->time, c->day);

    // Сохраняем данные игрока
    fprintf(savefile, "PLAYERDATA\n%d %d\n%d %d\n%d\n%d\n",
        p->x, p->y, 
        p->currentBuilding ? p->currentBuilding->x : -1, p->currentBuilding ? p->currentBuilding->y : -1,
        p->currentFloor ? p->currentFloor->floorNumber : -1,
        p->currentRoom ? p->currentRoom->room_number : -1);

    // Проходим по всем зданиям, этажам и комнатам за один проход
    fprintf(savefile, "BUILDINGDATA\n");
    for (int i = 0; i < c->height; i++) {
        for (int j = 0; j < c->width; j++) {
            building* b = c->cityMap[i][j];
            fprintf(savefile, "%s\n%d %d %d %d\n", b->name, b->x, b->y, b->height, b->building_type);

            // Сохранение этажей
            for (int k = 0; k < b->height; k++) {
                floor* f = b->floors[k];
                fprintf(savefile, "FLOOR %d %d %d %d\n", b->x, b->y, f->floorNumber, f->floor_type);

                if (f->floor_type == RESIDENTIAL) {
                    residentialFloor* rf = (residentialFloor*)f->floor_type_data;
                    fprintf(savefile, "ROOMS %d\n", rf->room_count);
                    
                    for (int l = 0; l < rf->room_count; l++) {
                        room* r = rf->rooms[l];
                        fprintf(savefile, "ROOM %d %d %d %d\n", b->x, b->y, f->floorNumber, r->room_number);
                        fprintf(savefile, "NPCS %d\n", r->npc_count);

                        // Сохранение NPC
                        for (int m = 0; m < r->npc_count; m++) {
                            npc* n = r->npcs[m];
                            fprintf(savefile, "NPC %s %s\n", n->firstName, n->lastName);
                            fprintf(savefile, "RESIDENCE %d %d %d %d\n",
                                n->placeOfResidence->parentFloor->parentBuilding->x,
                                n->placeOfResidence->parentFloor->parentBuilding->y,
                                n->placeOfResidence->parentFloor->floorNumber,
                                n->placeOfResidence->room_number);

                            if (n->placeOfWork) {
                                fprintf(savefile, "WORK %d %d %d %d\n",
                                    n->placeOfWork->parentFloor->parentBuilding->x,
                                    n->placeOfWork->parentFloor->parentBuilding->y,
                                    n->placeOfWork->parentFloor->floorNumber,
                                    n->placeOfWork->office_number);
                            }
                        }
                    }
                } else if (f->floor_type == OFFICE) {
                    officeFloor* of = (officeFloor*)f->floor_type_data;
                    fprintf(savefile, "OFFICES %d\n", of->office_count);

                    for (int l = 0; l < of->office_count; l++) {
                        office* o = of->offices[l];
                        fprintf(savefile, "OFFICE %d %d %d %s %d\n",
                            b->x, b->y, f->floorNumber, o->name, o->employee_count);
                    }
                }
            }
        }
    }

    fprintf(savefile, "END\n"); // Маркер конца файла
    fclose(savefile);
}

void loadSavefile(city* c, player* p) {
    FILE* savefile = fopen("savefile.txt", "r");
    if (!savefile) {
        printf("Error opening savefile.\n");
        exit(1);
    }

    char buffer[256];
    int currentBuildingX, currentBuildingY, currentFloorNum, currentRoomNum;

    // Читаем CITYDATA
    fscanf(savefile, "%s", buffer);
    if (strcmp(buffer, "CITYDATA") != 0) {
        printf("Invalid save file format.\n");
        fclose(savefile);
        exit(1);
    }
    fscanf(savefile, "%s", c->name);
    fscanf(savefile, "%d %d", &c->width, &c->height);
    fscanf(savefile, "%d %d", &c->residentialBuildings, &c->officeBuildings);
    fscanf(savefile, "%d %d", &c->time, &c->day);

    // Инициализация cityMap
    c->cityMap = (building***)malloc(c->height * sizeof(building**));
    for (int i = 0; i < c->height; i++) {
        c->cityMap[i] = (building**)malloc(c->width * sizeof(building*));
    }

    // Читаем PLAYERDATA
    fscanf(savefile, "%s", buffer);
    if (strcmp(buffer, "PLAYERDATA") != 0) {
        printf("Invalid save file format.\n");
        fclose(savefile);
        exit(1);
    }
    fscanf(savefile, "%d %d", &p->x, &p->y);
    fscanf(savefile, "%d %d", &currentBuildingX, &currentBuildingY);
    fscanf(savefile, "%d", &currentFloorNum);
    fscanf(savefile, "%d", &currentRoomNum);

    // Пока игнорируем восстановление currentBuilding, currentFloor, currentRoom
    p->currentBuilding = NULL;
    p->currentFloor = NULL;
    p->currentRoom = NULL;

    // Читаем BUILDINGDATA
    fscanf(savefile, "%s", buffer);
    if (strcmp(buffer, "BUILDINGDATA") != 0) {
        printf("Invalid save file format. Expected BUILDINGDATA.\n");
        fclose(savefile);
        exit(1);
    }

    // Загрузка зданий, этажей и комнат
    for (int i = 0; i < c->height; i++) {
        for (int j = 0; j < c->width; j++) {
            building* b = (building*)malloc(sizeof(building));
            fscanf(savefile, "%s", b->name);
            fscanf(savefile, "%d %d %d %d", &b->x, &b->y, &b->height, &b->building_type);
            b->floors = (floor**)malloc(b->height * sizeof(floor*));

            for (int k = 0; k < b->height; k++) {
                fscanf(savefile, "%s", buffer);
                if (strcmp(buffer, "FLOOR") != 0) {
                    printf("Unexpected token: %s, expected FLOOR\n", buffer);
                    fclose(savefile);
                    exit(1);
                }
                floor* f = (floor*)malloc(sizeof(floor));
                fscanf(savefile, "%d %d %d %d", &b->x, &b->y, &f->floorNumber, &f->floor_type);

                if (f->floor_type == RESIDENTIAL) {
                    residentialFloor* rf = (residentialFloor*)malloc(sizeof(residentialFloor));
                    fscanf(savefile, "%s %d", buffer, &rf->room_count);
                    rf->rooms = (room**)malloc(rf->room_count * sizeof(room*));

                    for (int l = 0; l < rf->room_count; l++) {
                        room* r = (room*)malloc(sizeof(room));
                        fscanf(savefile, "%s %d %d %d %d", buffer, &b->x, &b->y, &f->floorNumber, &r->room_number);
                        fscanf(savefile, "%s %d", buffer, &r->npc_count);
                        r->npcs = (npc**)malloc(r->npc_count * sizeof(npc*));

                        for (int m = 0; m < r->npc_count; m++) {
                            npc* n = (npc*)malloc(sizeof(npc));
                            fscanf(savefile, "%s %s", buffer, n->firstName);
                            fscanf(savefile, "%s", buffer);
                            fscanf(savefile, "%s %d %d %d %d", buffer,
                                   &n->placeOfResidence->parentFloor->parentBuilding->x,
                                   &n->placeOfResidence->parentFloor->parentBuilding->y,
                                   &n->placeOfResidence->parentFloor->floorNumber,
                                   &n->placeOfResidence->room_number);

                            if (fscanf(savefile, "%s", buffer) == 1 && strcmp(buffer, "WORK") == 0) {
                                fscanf(savefile, "%d %d %d %d",
                                       &n->placeOfWork->parentFloor->parentBuilding->x,
                                       &n->placeOfWork->parentFloor->parentBuilding->y,
                                       &n->placeOfWork->parentFloor->floorNumber,
                                       &n->placeOfWork->office_number);
                            }
                            r->npcs[m] = n;
                        }
                        rf->rooms[l] = r;
                    }
                    f->floor_type_data = rf;
                } else if (f->floor_type == OFFICE) {
                    officeFloor* of = (officeFloor*)malloc(sizeof(officeFloor));
                    fscanf(savefile, "%s %d", buffer, &of->office_count);
                    of->offices = (office**)malloc(of->office_count * sizeof(office*));

                    for (int l = 0; l < of->office_count; l++) {
                        office* o = (office*)malloc(sizeof(office));
                        fscanf(savefile, "%s %d %d %d %s %d", buffer, &b->x, &b->y, &f->floorNumber, o->name, &o->employee_count);
                        of->offices[l] = o;
                    }
                    f->floor_type_data = of;
                }
                b->floors[k] = f;
            }
            c->cityMap[i][j] = b;
        }
    }

    fscanf(savefile, "%s", buffer);
    if (strcmp(buffer, "END") != 0) {
        printf("Savefile corrupted. Missing END marker.\n");
        fclose(savefile);
        exit(1);
    }

    fclose(savefile);
}
