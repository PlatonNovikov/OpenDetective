#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "structures.h"
#include "generators.h"
#include "ui.h"
#include "saveload.h"

void allocateFloors(building* b) {
    printf("Allocating memory for floors...\n");
    b->floors = (floor**)malloc(b->height * sizeof(floor*));
    if (!b->floors) {
        printf("Error allocating memory for floors.\n");
        exit(1);
    }

    for (int i = 0; i < b->height; i++) {
        floor* f = (floor*)malloc(sizeof(floor));
        if (!f) {
            printf("Error allocating memory for floor.\n");
            exit(1);
        }
        f->floorNumber = i;
        f->parentBuilding = b;

        printf("Allocating memory for floor type data...\n");
        
        switch (b->building_type) {
        case RESIDENTIAL:
            f->floor_type = RESIDENTIAL;
            f->floor_type_data = (residentialFloor*)malloc(sizeof(residentialFloor));
            printf("Allocating memory for residential floor data...\n");
            if (!f->floor_type_data) {
                printf("Error allocating memory for residential floor data.\n");
                free(f);
                exit(1);
            }
            ((residentialFloor*)f->floor_type_data)->room_count = 4;
            ((residentialFloor*)f->floor_type_data)->rooms = (room**)malloc(4 * sizeof(room*));
            printf("Allocating memory for rooms...\n");
            if (!((residentialFloor*)f->floor_type_data)->rooms) {
                printf("Error allocating memory for rooms.\n");
                free(f->floor_type_data);
                free(f);
                exit(1);
            }
            for (int j = 0; j < 4; j++) {
                room* r = (room*)malloc(sizeof(room));
                if (!r) {
                    printf("Error allocating memory for room.\n");
                    for (int k = 0; k < j; k++) {
                        free(((residentialFloor*)f->floor_type_data)->rooms[k]);
                    }
                    free(((residentialFloor*)f->floor_type_data)->rooms);
                    free(f->floor_type_data);
                    free(f);
                    exit(1);
                }
                r->npcs = (npc**)malloc(4 * sizeof(npc*));
                if (!r->npcs) {
                    printf("Error allocating memory for NPCs.\n");
                    free(r);
                    for (int k = 0; k < j; k++) {
                        free(((residentialFloor*)f->floor_type_data)->rooms[k]);
                    }
                    free(((residentialFloor*)f->floor_type_data)->rooms);
                    free(f->floor_type_data);
                    free(f);
                    exit(1);
                }
                r->npc_count = 0;
                for(int k = 0; k < 4; k++){
                    r->npcs[k] = NULL;
                }
                r->parentFloor = f;
                r->room_number = j;
                ((residentialFloor*)f->floor_type_data)->rooms[j] = r;
            }
            break;

        case OFFICE:
            printf("Allocating memory for office floor data...\n");
            f->floor_type = OFFICE;
            f->floor_type_data = (officeFloor*)malloc(sizeof(officeFloor));
            if (!f->floor_type_data) {
                printf("Error allocating memory for office floor data.\n");
                free(f);
                exit(1);
            }
            officeFloor* of = (officeFloor*)f->floor_type_data;
            of->office_count = 3;
            of->parentFloor = f;
            of->offices = (office**)malloc(of->office_count * sizeof(office*));
            if (!of->offices) {
                printf("Error allocating memory for offices.\n");
                free(of);
                exit(1);
            }

            for (int j = 0; j < of->office_count; j++) {
                printf("Allocating memory for office...\n");
                of->offices[j] = (office*)malloc(sizeof(office));
                of->offices[j]->parentFloor = f;
                if (!of->offices[j]) {
                    printf("Error allocating memory for office.\n");
                    exit(1);
                }
                of->offices[j]->employee_count = 0;
                of->offices[j]->employees = (npc**)malloc(5 * sizeof(npc*));
                if (!of->offices[j]->employees) {
                    printf("Error allocating memory for employees.\n");
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
}

void generate_npc(npc* new_npc) {
    snprintf(new_npc->firstName, sizeof(new_npc->firstName), "%s", first_names[rand() % ARRAY_SIZE]);
    snprintf(new_npc->lastName, sizeof(new_npc->lastName), "%s", last_names[rand() % ARRAY_SIZE]);
    new_npc->relationships = (relationship*)malloc(MAX_RELATIONSHIPS * sizeof(relationship));
    if (!new_npc->relationships) {
        printf("Error allocating memory for relationships.\n");
        free(new_npc);
        exit(1);
    }
    new_npc->relationshipCount = 0;
}

void generate_family(int count, npc** family) {
    if (!family) {
        printf("Error allocating memory for family.\n");
        exit(1);
    }
    for (int i = 0; i < count; i++){
        family[i] = (npc*)malloc(sizeof(npc));
        if (!family[i]) {
            printf("Error allocating memory for NPC.\n");
            exit(1);
        }
        generate_npc(family[i]);
        strcpy(family[i]->lastName, family[0]->lastName);
    }
}

room* getFreeResidence(city* c){
    int countC = rand() % c->residentialBuildings;
    int countB = countC;
    int floorC = rand() % c->residentialBuildingsList[countC]->height;
    int floorB = floorC;
    int roomC = rand() % 4;
    int roomB = roomC;
    while (((residentialFloor*)c->residentialBuildingsList[countC]->floors[floorC]->floor_type_data)->rooms[roomC]->npcs[0]){
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
    return ((residentialFloor*)c->residentialBuildingsList[countC]->floors[floorC]->floor_type_data)->rooms[roomC];
}

office* getFreeWorkplace(city* c){
    int countC = rand() % c->officeBuildings;
    int countB = countC;
    int floorC = rand() % c->officeBuildingsList[countC]->height;
    int floorB = floorC;
    int officeC = rand() % ((officeFloor*)c->officeBuildingsList[countC]->floors[floorC]->floor_type_data)->office_count;
    int officeB = officeC;
    while (((officeFloor*)c->officeBuildingsList[countC]->floors[floorC]->floor_type_data)->offices[officeC]->employee_count == 5){
        if (officeC < ((officeFloor*)c->officeBuildingsList[countC]->floors[floorC]->floor_type_data)->office_count - 1){
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
    return ((officeFloor*)c->officeBuildingsList[countC]->floors[floorC]->floor_type_data)->offices[officeC];
}

void populateCity(city* c){
    for (int i = 0; i < c->residentialBuildings; i++){
        for (int j = 0; j < c->residentialBuildingsList[i]->height; j++){
            for (int k = 0; k < ((residentialFloor*)c->residentialBuildingsList[i]->floors[j]->floor_type_data)->room_count; k++){
                room* r = ((residentialFloor*)c->residentialBuildingsList[i]->floors[j]->floor_type_data)->rooms[k];
                if(rand()%4){
                    npc* new_npc = (npc*)malloc(sizeof(npc));
                    if (!new_npc) {
                        printf("Error allocating memory for NPC.\n");
                        exit(1);
                    }
                    generate_npc(new_npc);
                    new_npc->placeOfResidence = getFreeResidence(c);
                    new_npc->placeOfResidence->npcs[0] = new_npc;
                    new_npc->placeOfResidence->npc_count = 1;
                    new_npc->currentPlace = new_npc->placeOfResidence;
                    new_npc->placeOfWork = getFreeWorkplace(c);
                    if (new_npc->placeOfWork){
                        new_npc->placeOfWork->employees[new_npc->placeOfWork->employee_count] = new_npc;
                        new_npc->placeOfWork->employee_count++;
                    }
                }
                else{
                    npc** family = (npc**)malloc(4 * sizeof(npc*));
                    int count = rand() % 3 + 2;
                    if (!family) {
                        printf("Error allocating memory for family.\n");
                        exit(1);
                    }
                    generate_family(count, family);
                    
                    family[0]->placeOfResidence = getFreeResidence(c);
                    family[0]->placeOfResidence->npcs = family;
                    family[0]->placeOfResidence->npc_count = count;
                    for (int l = 0; l < count; l++){
                        family[l]->currentPlace = family[0]->placeOfResidence;
                        family[l]->placeOfResidence = family[0]->placeOfResidence;
                        family[l]->placeOfWork = getFreeWorkplace(c);
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

void player_building_spawn(city* c, player* p){
    for (int x = p->x; x < c->height; ++x) {
        for (int y = (x == p->x ? p->y : 0); y < c->width; ++y) {
            if (c->cityMap[x][y]->building_type == RESIDENTIAL) {
                p->x = x;
                p->y = y;
                p->currentBuilding = c->cityMap[x][y];
                return; // Остановка поиска
            }
        }
    }

    // Если не нашли здание, начинаем заново с (0, 0)
    for (int x = 0; x < c->height; ++x) {
        for (int y = 0; y < c->width; ++y) {
            if (c->cityMap[x][y]->building_type == RESIDENTIAL) {
                p->x = x;
                p->y = y;
                p->currentBuilding = c->cityMap[x][y];
                return;
            }
        }
    }
}

void start(city* c, player* p) {
    printf("Enter city name: ");
    scanf("%99s", c->name);
    clear();
    printf("Enter city width: ");
    scanf("%d", &c->width);
    clear();
    printf("Enter city height: ");
    scanf("%d", &c->height);
    clear();
    printf("Generating...\n");

    c->cityMap = (building***)malloc(c->height * sizeof(building**));
    if (!c->cityMap) {
        printf("Error allocating memory for city map.\n");
        exit(1);
    }

    for (int i = 0; i < c->height; i++) {
        c->cityMap[i] = (building**)malloc(c->width * sizeof(building*));
        if (!c->cityMap[i]) {
            printf("Error allocating memory for city map row.\n");
            exit(1);
        }

        for (int j = 0; j < c->width; j++) {
            building* b = (building*)malloc(sizeof(building));
            if (!b) {
                printf("Error allocating memory for building.\n");
                exit(1);
            }

            snprintf(b->name, sizeof(b->name), "%s", generate_street_name());
            b->x = i;
            b->y = j;
            b->height = rand() % 7 + 3; // Высота от 3 до 10 этажей
            b->parentCity = c;
            switch (rand()%10)
            {
            case 0:
                b->building_type = OFFICE;
                break;

            default:
                b->building_type = RESIDENTIAL;
                break;
            }

            allocateFloors(b);
            c->cityMap[i][j] = b;
        }
    }

    c->residentialBuildings = 0;
    c->officeBuildings = 0;
    for (int i = 0; i < c->height; i++) {
        for (int j = 0; j < c->width; j++) {
            if (c->cityMap[i][j]->building_type == RESIDENTIAL) {
                c->residentialBuildings++;
            } else {
                c->officeBuildings++;
            }
        }
    }

    c->residentialBuildingsList = (building**)malloc(c->residentialBuildings * sizeof(building*));
    if (!c->residentialBuildingsList) {
        printf("Error allocating memory for residential buildings.\n");
        exit(1);
    }
    c->officeBuildingsList = (building**)malloc(c->officeBuildings * sizeof(building*));
    if (!c->officeBuildingsList) {
        printf("Error allocating memory for office buildings.\n");
        exit(1);
    }

    int countR = 0;
    int countO = 0;
    for (int i = 0; i < c->height; i++) {
        for (int j = 0; j < c->width; j++) {
            if (c->cityMap[i][j]->building_type == RESIDENTIAL) {
                c->residentialBuildingsList[countR] = c->cityMap[i][j];
                countR++;
            } else {
                c->officeBuildingsList[countO] = c->cityMap[i][j];
                countO++;
            }
        }
    }

    for (int i = 0; i < c->height; i++) {
        for (int j = 0; j < c->width; j++) {
            building* b = c->cityMap[i][j];
            for (int k = 0; k < b->height; k++) {
                if (b->floors[k]->floor_type == OFFICE){
                    for (int l = 0; l < ((officeFloor*)b->floors[k]->floor_type_data)->office_count; l++){
                        office* o = ((officeFloor*)b->floors[k]->floor_type_data)->offices[l];
                        snprintf(o->name, sizeof(o->name), "%s", generateCompanyName());
                    } 
                }
            }
        }
    }
    
    populateCity(c);

    p->x = rand() % c->height;
    p->y = rand() % c->width;
    player_building_spawn(c, p);
    p->currentBuilding = c->cityMap[p->x][p->y];
    p->currentFloor = p->currentBuilding->floors[rand() % p->currentBuilding->height];
    p->currentRoom = ((residentialFloor*)p->currentFloor->floor_type_data)->rooms[rand() % 4];

    printf("City generated successfully!\n\n");

}

void freeCity(city* c) {
    if (!c) return;

    for (int i = 0; i < c->height; i++) {
        for (int j = 0; j < c->width; j++) {
            building* b = c->cityMap[i][j];
            if (!b) continue;

            // Освобождаем этажи
            for (int k = 0; k < b->height; k++) {
                floor* f = b->floors[k];
                if (!f) continue;

                // Освобождаем данные этажа в зависимости от типа
                switch (f->floor_type) {
                    case RESIDENTIAL: {
                        residentialFloor* resFloor = (residentialFloor*)f->floor_type_data;
                        if (resFloor) {
                            for (int l = 0; l < resFloor->room_count; l++) {
                                room* r = resFloor->rooms[l];
                                if (r) {
                                    // Освобождаем NPC в комнате
                                    if (r->npcs[0]) {
                                        free(r->npcs[0]);
                                    }
                                    free(r->npcs); // Освобождаем массив NPC
                                    free(r);       // Освобождаем саму комнату
                                }
                            }
                            free(resFloor->rooms); // Освобождаем массив комнат
                            free(resFloor);        // Освобождаем данные жилого этажа
                        }
                        break;
                    }

                    case OFFICE: {
                        officeFloor* of = (officeFloor*)f->floor_type_data;
                        if (of) {
                            for (int l = 0; l < of->office_count; l++) {
                                office* o = of->offices[l];
                                if (o) {
                                    // Освобождаем сотрудников офиса
                                    for (int m = 0; m < o->employee_count; m++) {
                                        if (o->employees[m]) {
                                            free(o->employees[m]);
                                        }
                                    }
                                    free(o->employees); // Освобождаем массив сотрудников
                                    free(o);            // Освобождаем сам офис
                                }
                            }
                            free(of->offices); // Освобождаем массив офисов
                            free(of);         // Освобождаем данные офисного этажа
                        }
                        break;
                    }

                    default:
                        // Неизвестный тип этажа
                        break;
                }

                free(f); // Освобождаем сам этаж
            }

            free(b->floors); // Освобождаем массив этажей
            free(b);         // Освобождаем само здание
        }

        free(c->cityMap[i]); // Освобождаем строку карты
    }

    // Освобождаем списки зданий
    if (c->residentialBuildingsList) {
        free(c->residentialBuildingsList);
    }
    if (c->officeBuildingsList) {
        free(c->officeBuildingsList);
    }

    free(c->cityMap); // Освобождаем карту города
}

void openCMD(){
    #if defined(_WIN32) || defined(_WIN64)
        system("start cmd.exe /K OpenDetective.exe --child");
    #elif defined(__linux__) || defined(__unix__)
        if (system("which gnome-terminal > /dev/null 2>&1") == 0) {
            system("gnome-terminal -- bash -c './OpenDetective --child; exec bash'");
        } else if (system("which xterm > /dev/null 2>&1") == 0) {
            system("xterm -hold -e './OpenDetective --child' &");
        } else if (system("which konsole > /dev/null 2>&1") == 0) {
            system("konsole --hold -e './OpenDetective --child' &");
        } else if (system("which terminator > /dev/null 2>&1") == 0) {
            system("terminator -e './OpenDetective --child' &");
        } else {
            printf("error.\n");
        }
    #else
        printf("go fuck yourself\n");
    #endif
}

int main(int argc, char *argv[]){
    /*if (argc < 2 || strcmp(argv[1], "--child") != 0) {
        openCMD();  // Открываем новый терминал
        return 0;   // Завершаем текущий процесс, чтобы избежать дублирования
    }*/
    clear();
    srand(time(NULL));
    srand(THE_ANSWER_TO_LIFE_THE_UNIVERSE_AND_EVERYTHING);
    city c;
    player p;

    printf("1: New city");
    printf("2: Load save");
    int choice;
    printf("\nChoose an option: ");
    scanf("%d", &choice);
    clear();
    if (choice == 2) {
        loadSavefile(&c, &p);
    } else {
        start(&c, &p);
    }

    while (1) {
        playerControl(&c, &p);
    }
    freeCity(&c);
    return 0;
}