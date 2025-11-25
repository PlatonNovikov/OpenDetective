#include "structures.h"
#include <stdio.h>
#include "ui.h"
#include "saveload.h"
#include <stdlib.h>

void printMap(t_city* c, t_player* p)
{
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

void printSeparator()
{
	printf("\n\033[35m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m\n");
}

void clearInputBuffer()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

int safeInput(int min, int max)
{
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

//returns the number of NPCs in the npcList
int getNpcs(t_npc** npcList)
{
	int count = 0;
	while ((npcList[count] != NULL) && (count < MAX_NPC)) {
		count++;
	}
	return count;
}

//prints the list of NPCs in the npcList
void listNpcs(t_npc** npcList, int startIndex)
{
	int count = getNpcs(npcList);
	for (int i = 0; i < count; i++) {
		printf("%d: %s %s\n", i + 1 + startIndex, npcList[i]->firstName, npcList[i]->lastName);
	}
}

void printTime(t_city* c) {
	printf("\033[33mDay %d, Time: %02d:00\033[0m\n", c->day, c->time);
}

void handleMapMovement(t_city* c, t_player* p)
{
	int choice;

	printSeparator();
	printMap(c, p);

	printf("1: Move north\n");
	printf("2: Move south\n");
	printf("3: Move east\n");
	printf("4: Move west\n");
	printf("0: Do nothing\n");
	choice = safeInput(0, 4);
	switch (choice)
	{
	case 1:
		if (p->x > 0)
			p->x -= 1;
		else
			printf("You can't move further north.\n");
		break;

	case 2:
		if (p->x < c->height - 1)
			p->x += 1;
		else
			printf("You can't move further south.\n");
		break;

	case 3:
		if (p->y < c->width - 1)
			p->y += 1;
		else
			printf("You can't move further east.\n");
		break;

	case 4:
		if (p->y > 0)
			p->y -= 1;
		else
			printf("You can't move further west.\n");
		break;
	}
	p->currentBuilding = c->cityMap[p->x][p->y];
	c->addTime(c, 1);
}

void handleDialogue(t_player* p, t_npc* n)
{
	int choice;

	printTime(p->currentBuilding->parentCity);
	printSeparator();
	printf("You are talking to %s %s\n", n->firstName, n->lastName);
	printf("1: Ask about their day\n");
	printf("2: Say goodbye\n");
	choice = safeInput(1, 2);
	switch (choice)
	{
	case 1:
		printf("%s says: 'It's been a busy day at work!'\n", n->firstName);
		break;
	case 2:
		printf("You say goodbye to %s.\n", n->firstName);
		break;

	default:
		break;
	}
}

void handleResidentialRoom(t_city *c, t_player* p)
{
	int 		choice;
	const int	npcCount = getNpcs(p->currentRoom->current_npcs);

	printTime(c);
	printSeparator();
	printf("You are in room number %d\n", p->currentRoom->room_number);
	if (npcCount > 0)
	{
		if (npcCount == 1)
			printf("There is 1 person here\n");
		else
			printf("There are %d people here\n", npcCount);
	}
	else
		printf("The room is empty.\n");

	printf("1: Talk to someone\n");
	printf("0: Exit room\n");
	choice = safeInput(0, 1);
	switch (choice)
	{
	case 1:
		if (npcCount == 0)
		{
			printf("There is no one to talk to.\n");
			break;
		}
		listNpcs(p->currentRoom->current_npcs, 0);
		printf("Choose a person to talk to (0 to cancel): ");
		choice = safeInput(0, npcCount);
		if (choice == 0)
			break ;
		handleDialogue(p, p->currentRoom->current_npcs[choice - 1]);
		break;

	case 0:
		printf("You exit the room.\n");
		p->currentRoom = NULL;
		break;

	default:
		break;
	}
}

void handleOffice(t_city* c, t_player* p)
{
	int 		choice;
	const int	npcCount = getNpcs(p->currentOffice->current_npcs);

	printTime(c);
	printSeparator();
	printf("You are in office number %d of %s\n", p->currentOffice->office_number, p->currentOffice->name);
	if (npcCount > 0)
	{
		if (npcCount == 1)
			printf("There is 1 person here\n");
		else
			printf("There are %d people here\n", npcCount);
	}
	else
		printf("The office is empty.\n");

	printf("1: Talk to someone\n");
	printf("0: Exit office\n");
	choice = safeInput(0, 1);
	switch (choice)
	{
	case 1:
		if (npcCount == 0)
		{
			printf("There is no one to talk to.\n");
			break;
		}
		listNpcs(p->currentOffice->current_npcs, 0);
		printf("Choose a person to talk to (0 to cancel): ");
		choice = safeInput(0, npcCount);
		if (choice == 0)
			break ;
		handleDialogue(p, p->currentOffice->current_npcs[choice - 1]);
		break;

	case 0:
		printf("You exit the office.\n");
		p->currentOffice = NULL;
		break;

	default:
		break;
	}
}

void handleResidentialFloor(t_player* p)
{
	int choice;

	const int	npcCount = getNpcs(p->currentFloor->current_npcs);
	printTime(p->currentBuilding->parentCity);
	printSeparator();
	printf("You are on floor %d of %s\n", p->currentFloor->floorNumber, p->currentBuilding->name);
	if (npcCount > 0)
	{
		if (npcCount == 1)
			printf("There is 1 person here\n");
		else
			printf("There are %d people here\n", npcCount);
	}
	else
		printf("The floor is empty.\n");
	printf("1: Enter a room\n");
	printf("2: Talk to someone\n");
	printf("3: Go to another floor\n");
	if (p->currentFloor->floorNumber == 0)
		printf("0: Exit building\n");
	choice = safeInput(p->currentFloor->floorNumber > 0, 3);
	switch (choice)
	{
	case 1:
		printf("Choose a room to enter:\n");
		for (int i = 0; i < p->currentFloor->floorTypeData.residentialFloorData->room_count; i++)
		{
			printf("%d: Room %d\n", i + 1, p->currentFloor->floorTypeData.residentialFloorData->rooms[i]->room_number);
		}
		choice = safeInput(1, p->currentFloor->floorTypeData.residentialFloorData->room_count);
		p->currentRoom = p->currentFloor->floorTypeData.residentialFloorData->rooms[choice - 1];
		break;

	case 2:
		if (npcCount == 0)
		{
			printf("There is no one to talk to.\n");
			break;
		}
		listNpcs(p->currentFloor->current_npcs, 0);
		printf("Choose a person to talk to (0 to cancel): ");
		choice = safeInput(0, npcCount);
		if (choice == 0)
			break ;
		handleDialogue(p, p->currentFloor->current_npcs[choice - 1]);
		break;

	case 3:
		printf("Choose a floor to go to (0 to cancel):\n");
		for (int i = 0; i < p->currentBuilding->height; i++)
		{
			printf("%d: Floor %d\n", i + 1, i);
		}
		choice = safeInput(0, p->currentBuilding->height);
		if (choice == 0)
			break ;
		p->currentFloor = p->currentBuilding->floors[choice - 1];
		break;

	case 0:
		printf("You exit the building.\n");
		p->currentFloor = NULL;
		break;

	default:
		break;
	}
}

void handleOfficeFloor(t_player* p)
{
	int choice;

	const int	npcCount = getNpcs(p->currentFloor->current_npcs);
	printTime(p->currentBuilding->parentCity);
	printSeparator();
	printf("You are on floor %d of %s\n", p->currentFloor->floorNumber, p->currentBuilding->name);
	if (npcCount > 0)
	{
		if (npcCount == 1)
			printf("There is 1 person here\n");
		else
			printf("There are %d people here\n", npcCount);
	}
	else
		printf("The floor is empty.\n");
	printf("1: Enter an office\n");
	printf("2: Talk to someone\n");
	printf("3: Go to another floor\n");
	if (p->currentFloor->floorNumber == 0)
		printf("0: Exit building\n");
	choice = safeInput(p->currentFloor->floorNumber > 0, 3);
	switch (choice)
	{
	case 1:
		printf("Choose an office to enter:\n");
		for (int i = 0; i < p->currentFloor->floorTypeData.officeFloorData->office_count; i++)
		{
			printf("%d: Office %d\n", i + 1, p->currentFloor->floorTypeData.officeFloorData->offices[i]->office_number);
		}
		choice = safeInput(1, p->currentFloor->floorTypeData.officeFloorData->office_count);
		p->currentOffice = p->currentFloor->floorTypeData.officeFloorData->offices[choice - 1];
		break;

	case 2:
		if (npcCount == 0)
		{
			printf("There is no one to talk to.\n");
			break;
		}
		listNpcs(p->currentFloor->current_npcs, 0);
		printf("Choose a person to talk to (0 to cancel): ");
		choice = safeInput(0, npcCount);
		if (choice == 0)
			break ;
		handleDialogue(p, p->currentFloor->current_npcs[choice - 1]);
		break;

	case 3:
		printf("Choose a floor to go to (0 to cancel):\n");
		for (int i = 0; i < p->currentBuilding->height; i++)
		{
			printf("%d: Floor %d\n", i + 1, i);
		}
		choice = safeInput(0, p->currentBuilding->height);
		if (choice == 0)
			break ;
		p->currentFloor = p->currentBuilding->floors[choice - 1];
		break;

	case 0:
		printf("You exit the building.\n");
		p->currentFloor = NULL;
		break;

	default:
		break;
	}
}

void handleOutsideInteraction(t_city* c, t_player* p)
{
	int choice;
	const int	npcCount = getNpcs(p->currentBuilding->current_npcs);

	printTime(c);
	printSeparator();
	printf("You are outside at (%d, %d) in front of %s\n", p->x, p->y, p->currentBuilding->name);
	printf("1: Enter building\n");
	printf("2: Move on the map\n");
	if (npcCount > 0)
	{
		if (npcCount == 1)
			printf("There is 1 person here\n");
		else
			printf("There are %d people here\n", npcCount);
	}
	else
		printf("The street is empty.\n");
	printf("3: Talk to someone\n");
	printf("4: Sleep on the bench\n");
	printf("0: Exit Game\n");
	choice = safeInput(0, 4);
	switch (choice)
	{
	case 1:
		p->currentFloor = p->currentBuilding->floors[0];
		break;

	case 2:
		handleMapMovement(c, p);
		break;

	case 3:
		if (npcCount == 0)
		{
			printf("There is no one to talk to.\n");
			break;
		}
		listNpcs(p->currentBuilding->current_npcs, 0);
		printf("Choose a person to talk to (0 to cancel): ");
		choice = safeInput(0, npcCount);
		if (choice == 0)
			break ;
		handleDialogue(p, p->currentBuilding->current_npcs[choice - 1]);
		break;

	case 4:
		printf("How many hours do you want to sleep? (from 1 to 12): ");
		choice = safeInput(1, 12);
		c->addTime(c, choice);
		printf("You slept for %d hours.\n", choice);
		break;
	case 0:
		// saveGame(c, p);
		printf("Exiting...\n");
		exit(0);
		break;

	default:
		break;
	}
}

// Основная функция
void playerControl(t_city* c, t_player* p) {
	if (p->currentRoom)
	{
		handleResidentialRoom(c, p);
	}
	else if (p->currentOffice)
	{
		handleOffice(c, p);
	}
	else if (p->currentFloor)
	{
		if (p->currentBuilding->building_type == RESIDENTIAL)
		{
			handleResidentialFloor(p);
		}
		else if (p->currentBuilding->building_type == OFFICE)
		{
			handleOfficeFloor(p);
		}
	}
	else
	{
		handleOutsideInteraction(c, p);
	}
}