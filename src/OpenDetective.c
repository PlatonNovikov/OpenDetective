#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/structures.h"
#include "../include/generators.h"
#include "../include/ui.h"
#include "../include/saveload.h"
#include "../include/npc.h"
#include "../include/city.h"
#include "../include/rand.h"

t_city *g_city;

void player_building_spawn(t_inner_npc *n){
	n->x = urand() % g_city->height;
	n->y = urand() % g_city->width;
	for (unsigned x = n->x; x < g_city->height; ++x) {
		for (unsigned y = (x == n->x ? n->y : 0); y < g_city->width; ++y) {
			if (g_city->cityMap[x][y]->building_type == RESIDENTIAL) {
				n->x = x;
				n->y = y;
				n->currentBuilding = g_city->cityMap[x][y];
				return; // Остановка поиска
			}
		}
	}

	// Если не нашли здание, начинаем заново с (0, 0)
	for (unsigned x = 0; x < g_city->height; ++x) {
		for (unsigned y = 0; y < g_city->width; ++y) {
			if (g_city->cityMap[x][y]->building_type == RESIDENTIAL) {
				n->x = x;
				n->y = y;
				n->currentBuilding = g_city->cityMap[x][y];
				return;
			}
		}
	}
}

void make_player(t_player *p)
{
	p->npc = calloc(1, sizeof(t_inner_npc));
	t_inner_npc *n = p->npc;
	if(!n)
		exit(EXIT_FAILURE);

	player_building_spawn(n);
	n->currentFloor = n->currentBuilding->floors[urand() % n->currentBuilding->height];
	n->currentRoom = n->currentFloor->floorTypeData.residentialFloorData->rooms[rand() % 4];
	n->currentOffice = NULL;
	p->known_npcs = init_vec();
}

void start(t_player* p) {
	g_city = calloc(1, sizeof(t_city));
	if (!g_city)
		exit(EXIT_FAILURE);

	printf("Enter city name: ");
	scanf("%99s", g_city->name);
	clear();
	printf("Enter city width: ");
	scanf("%u", &g_city->width);
	clear();
	printf("Enter city height: ");
	scanf("%u", &g_city->height);
	clear();
	printf("Generating...\n");

	g_city->addTime = addTime;
	g_city->rel = NULL;

	g_city->cityMap = calloc(g_city->height, sizeof(t_building**));
	if (!g_city->cityMap) {
		printf("Error allocating memory for city map.\n");
		exit(1);
	}

	for (unsigned i = 0; i < g_city->height; i++) {
		g_city->cityMap[i] = calloc(g_city->width, sizeof(t_building*));
		if (!g_city->cityMap[i]) {
			printf("Error allocating memory for city map row.\n");
			exit(1);
		}

		for (unsigned j = 0; j < g_city->width; j++) {
			t_building* b = calloc(1, sizeof(t_building));
			if (!b) {
				printf("Error allocating memory for building.\n");
				exit(1);
			}

			snprintf(b->name, sizeof(b->name), "%s", generate_street_name());
			b->x = i;
			b->y = j;
			b->height = (unsigned)rand() % 7 + 3; // Высота от 3 до 10 этажей
			b->parentCity = g_city;
			b->current_npcs = calloc(MAX_NPC_PRESENT, sizeof(t_npc*));
			if (!b->current_npcs)
			{
				printf("Error allocating memory for current NPCs in building.\n");
				free(b);
				exit(1);
			}
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
			g_city->cityMap[i][j] = b;
		}
	}
	g_city->residentialBuildings = 0;
	g_city->officeBuildings = 0;
	for (unsigned i = 0; i < g_city->height; i++) {
		for (unsigned j = 0; j < g_city->width; j++) {
			if (g_city->cityMap[i][j]->building_type == RESIDENTIAL) {
				g_city->residentialBuildings++;
			} else {
				g_city->officeBuildings++;
			}
		}
	}
	g_city->residentialBuildings = init_vec();
	g_city->officeBuildings = init_vec();

	for (unsigned i = 0; i < g_city->height; i++) {
		for (unsigned j = 0; j < g_city->width; j++) {
			if (g_city->cityMap[i][j]->building_type == RESIDENTIAL) {
				vec_append(g_city->residentialBuildings, g_city->cityMap[i][j]);
			} else {
				vec_append(g_city->officeBuildings, g_city->cityMap[i][j]);
			}
		}
	}
	for (unsigned i = 0; i < g_city->height; i++) {
		for (unsigned j = 0; j < g_city->width; j++) {
			t_building* b = g_city->cityMap[i][j];
			for (unsigned k = 0; k < b->height; k++) {
				if (b->floors[k]->floorType == OFFICE) {
					for (unsigned l = 0; l < b->floors[k]->floorTypeData.officeFloorData->office_count; l++){
						t_office* o = b->floors[k]->floorTypeData.officeFloorData->offices[l];
						snprintf(o->name, sizeof(o->name), "%s", generateCompanyName());
					}
				}
			}
		}
	}
	g_city->npcList = init_vec();
	populateCity(g_city);
    g_city->time = 0;
	g_city->addTime(36 * 60); //start at 12:00 next day
	make_player(p);

	//printf("City generated successfully!\n\n");
}

void freeCity() {
	// if (!g_city) return;

	// for (unsigned i = 0; i < g_city->height; i++) {
	// 	for (unsigned j = 0; j < g_city->width; j++) {
	// 		t_building* b = g_city->cityMap[i][j];
	// 		if (!b) continue;

	// 		// Освобождаем этажи
	// 		for (unsigned k = 0; k < b->height; k++) {
	// 			t_floor* f = b->floors[k];
	// 			if (!f) continue;

	// 			// Освобождаем данные этажа в зависимости от типа
	// 			switch (f->floorType) {
	// 				case RESIDENTIAL: {
	// 					t_residentialFloor* resFloor = f->floorTypeData.residentialFloorData;
	// 					if (resFloor) {
	// 						for (unsigned l = 0; l < resFloor->room_count; l++) {
	// 							t_room* r = resFloor->rooms[l];
	// 							if (r) {
	// 								// Освобождаем NPC в комнате
	// 								if (r->assigned_npcs[0]) {
	// 									free(r->assigned_npcs[0]);
	// 								}
	// 								free(r->assigned_npcs); // Освобождаем массив NPC
	// 								free(r);       // Освобождаем саму комнату
	// 							}
	// 						}
	// 						free(resFloor->rooms); // Освобождаем массив комнат
	// 						free(resFloor);        // Освобождаем данные жилого этажа
	// 					}
	// 					break;
	// 				}

	// 				case OFFICE: {
	// 					t_officeFloor* of = f->floorTypeData.officeFloorData;
	// 					if (of) {
	// 						for (unsigned l = 0; l < of->office_count; l++) {
	// 							t_office* o = of->offices[l];
	// 							if (o) {
	// 								// Освобождаем сотрудников офиса
	// 								for (unsigned m = 0; m < o->employee_count; m++) {
	// 									if (o->employees[m]) {
	// 										free(o->employees[m]);
	// 									}
	// 								}
	// 								free(o->employees); // Освобождаем массив сотрудников
	// 								free(o);            // Освобождаем сам офис
	// 							}
	// 						}
	// 						free(of->offices); // Освобождаем массив офисов
	// 						free(of);         // Освобождаем данные офисного этажа
	// 					}
	// 					break;
	// 				}

	// 				default:
	// 					// Неизвестный тип этажа
	// 					break;
	// 			}

	// 			free(f); // Освобождаем сам этаж
	// 		}

	// 		free(b->floors); // Освобождаем массив этажей
	// 		free(b);         // Освобождаем само здание
	// 	}

	// 	free(g_city->cityMap[i]); // Освобождаем строку карты
	// }

	// // Освобождаем списки зданий
	// if (g_city->residentialBuildingsList) {
	// 	free(g_city->residentialBuildingsList);
	// }
	// if (g_city->officeBuildingsList) {
	// 	free(g_city->officeBuildingsList);
	// }

	// free(g_city->cityMap); // Освобождаем карту города
}

void openCMD(){
	#if defined(_WIN32) || defined(_WIN64)
		system("start cmd.exe /K OpenDetective.exe --child");
	#elif defined(__linux__) || defined(__unix__)
		if (system("which gnome-terminal > /dev/null 2>&1") == 0) {
			system("gnome-terminal -- bash -g_city './OpenDetective --child; exec bash'");
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

int main(int argc, char *argv[])
{
	if (argc < 2 || strcmp(argv[1], "--child") != 0) {
		// openCMD();  // Открываем новый терминал
		// return 0;   // Завершаем текущий процесс, чтобы избежать дублирования
	}
	clear();
	srand((unsigned)time(NULL));
	// srand(THE_ANSWER_TO_LIFE_THE_UNIVERSE_AND_EVERYTHING); //debug

	t_player p;

	clear();
	printf("1: New city\n");
	printf("2: Load save");
	int choice;
	printf("\nChoose an option: ");
	scanf("%d", &choice);
	clear();
	if (choice == 2)
	{
		printf("Not implemented yet");
		// loadSavefile(&p);
	}
	else
	{
		start(&p);
	}

	while (1) {
		playerControl(&p);
	}
	freeCity();
	return 0;
}
