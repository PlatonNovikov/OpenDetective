#include "../include/ui.h"

static void printMap(t_player* p)
{
	printf("\n\033[36m%s City Map\033[0m\n", g_city->name); // Cyan city name
	printf("╔");
	for(unsigned i = 0; i < g_city->width; i++) {
		printf("═══");
		if (i < g_city->width - 1) {
			printf("╦");
		}
	}
	printf("╗\n");
	for (unsigned i = 0; i < g_city->height; i++) {
		for (unsigned j = 0; j < g_city->width; j++) {
			printf("║ "); // Vertical separator
			if (p->npc->x == i && p->npc->y == j) {
				printf("\033[1;31m☺\033[0m"); // Bold red player
			} else if (g_city->cityMap[i][j]) {
				switch (g_city->cityMap[i][j]->building_type) {
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
		if (i < g_city->height - 1) {
			printf("╠");
			for (unsigned j = 0; j < g_city->width; j++) {
				printf("═══");
				if (j < g_city->width - 1) {
					printf("╬");
				}
			}
			printf("╣\n");
		}
	}
	printf("╚");
	for (unsigned i = 0; i < g_city->width; i++) {
		printf("═══");
		if (i < g_city->width - 1) {
			printf("╩");
		}
	}
	printf("╝\n");
	printf("\n\033[33mLegend:\033[0m ☺=You | ⌂=Home | F=Office | ·=Empty\n\n");
}

static void printSeparator()
{
	printf("\n\033[35m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m\n");
}

static void clearInputBuffer()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

unsigned safeInput_u(unsigned min, unsigned max)
{
	unsigned choice;
	while(1) {
		if(scanf("%u", &choice) == 1) {
			if(choice >= min && choice <= max) {
				clearInputBuffer();
				return choice;
			}
		}
		clearInputBuffer();
		printf("Invalid input. Please enter a number between %u-%u: ", min, max);
	}
}

//prints the list of NPCs in the npcList
static void listNpcs(t_vec *npcList, unsigned startIndex)
{
	size_t count = npcList->size;
	t_npc	*n = NULL;
	for (size_t i = 0; i < count; i++) {
		n = ((t_npc **)npcList->data)[i];
		printf("%lu: %s %s\n", i + 1 + startIndex, n->firstName, n->lastName);
	}
}

static void printTime() {
	printf("\033[33mDay %ld, Time: %02ld:%02ld\033[0m\n", currentDay(), currentTimeHour(), currentTimeMinute());
}

static void handleMapMovement(t_player* p)
{
	unsigned choice;

	printSeparator();
	printMap(p);

	printf("1: Move north\n");
	printf("2: Move south\n");
	printf("3: Move east\n");
	printf("4: Move west\n");
	printf("0: Do nothing\n");
	choice = safeInput_u(0, 4);
	switch (choice)
	{
	case 1:
		if (p->npc->x > 0)
			p->npc->x -= 1;
		else
			printf("You can't move further north.\n");
		break;

	case 2:
		if (p->npc->x < g_city->height - 1)
			p->npc->x += 1;
		else
			printf("You can't move further south.\n");
		break;

	case 3:
		if (p->npc->y < g_city->width - 1)
			p->npc->y += 1;
		else
			printf("You can't move further east.\n");
		break;

	case 4:
		if (p->npc->y > 0)
			p->npc->y -= 1;
		else
			printf("You can't move further west.\n");
		break;
	}
	p->npc->currentBuilding = g_city->cityMap[p->npc->x][p->npc->y];
	g_city->addTime(1);
}

static void handleResidentialRoom(t_player* p)
{
	unsigned		choice;
	const size_t	npcCount = p->npc->currentRoom->current_npcs->size;

	printTime(g_city);
	printSeparator();
	printf("You are in room number %d\n", p->npc->currentRoom->room_number);
	if (npcCount > 0)
	{
		if (npcCount == 1)
			printf("There is 1 person here\n");
		else
			printf("There are %ld people here\n", npcCount);
	}
	else
		printf("The room is empty.\n");

	printf("1: Talk to someone\n");
	printf("0: Exit room\n");
	choice = safeInput_u(0, 1);
	switch (choice)
	{
	case 1:
		if (npcCount == 0)
		{
			printf("There is no one to talk to.\n");
			break;
		}
		listNpcs(p->npc->currentRoom->current_npcs, 0);
		printf("Choose a person to talk to (0 to cancel): ");
		choice = safeInput_u(0, npcCount);
		if (choice == 0)
			break ;
		handle_dialogue(p, p->npc->currentRoom->current_npcs->data[choice - 1]);
		break;

	case 0:
		printf("You exit the room.\n");
		p->npc->currentRoom = NULL;
		addTime(1);
		break;

	default:
		break;
	}
}

static void handleOffice(t_player* p)
{
	unsigned		choice;
	const unsigned	npcCount = p->npc->currentOffice->current_npcs->size;

	printTime(g_city);
	printSeparator();
	printf("You are in office number %d of %s\n", p->npc->currentOffice->office_number, p->npc->currentOffice->name);
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
	choice = safeInput_u(0, 1);
	switch (choice)
	{
	case 1:
		if (npcCount == 0)
		{
			printf("There is no one to talk to.\n");
			break;
		}
		listNpcs(p->npc->currentOffice->current_npcs, 0);
		printf("Choose a person to talk to (0 to cancel): ");
		choice = safeInput_u(0, npcCount);
		if (choice == 0)
			break ;
		handle_dialogue(p, p->npc->currentOffice->current_npcs->data[choice - 1]);
		break;

	case 0:
		printf("You exit the office.\n");
		p->npc->currentOffice = NULL;
		addTime(1);
		break;

	default:
		break;
	}
}

static void handleResidentialFloor(t_player* p)
{
	unsigned		choice;
	const unsigned	npcCount = p->npc->currentFloor->current_npcs->size;

	printTime(p->npc->currentBuilding->parentCity);
	printSeparator();
	printf("You are on floor %d of %s\n", p->npc->currentFloor->floorNumber, p->npc->currentBuilding->name);
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
	if (p->npc->currentFloor->floorNumber == 0)
		printf("0: Exit building\n");
	choice = safeInput_u(p->npc->currentFloor->floorNumber > 0, 3);
	switch (choice)
	{
	case 1:
		printf("Choose a room to enter:\n");
		for (unsigned i = 0; i < p->npc->currentFloor->floorTypeData.residentialFloorData->room_count; i++)
		{
			printf("%d: Room %d\n", i + 1, p->npc->currentFloor->floorTypeData.residentialFloorData->rooms[i]->room_number);
		}
		choice = safeInput_u(1, p->npc->currentFloor->floorTypeData.residentialFloorData->room_count);
		p->npc->currentRoom = p->npc->currentFloor->floorTypeData.residentialFloorData->rooms[choice - 1];
		addTime(1);
		break;

	case 2:
		if (npcCount == 0)
		{
			printf("There is no one to talk to.\n");
			break;
		}
		listNpcs(p->npc->currentFloor->current_npcs, 0);
		printf("Choose a person to talk to (0 to cancel): ");
		choice = safeInput_u(0, npcCount);
		if (choice == 0)
			break ;
		handle_dialogue(p, p->npc->currentFloor->current_npcs->data[choice - 1]);
		break;

	case 3:
		printf("Choose a floor to go to (0 to cancel):\n");
		for (unsigned i = 0; i < p->npc->currentBuilding->height; i++)
		{
			printf("%d: Floor %d\n", i + 1, i);
		}
		choice = safeInput_u(0, p->npc->currentBuilding->height);
		if (choice == 0)
			break ;
		p->npc->currentFloor = p->npc->currentBuilding->floors[choice - 1];
		addTime(1);
		break;

	case 0:
		printf("You exit the building.\n");
		p->npc->currentFloor = NULL;
		addTime(1);
		break;

	default:
		break;
	}
}

static void handleOfficeFloor(t_player* p)
{
	unsigned choice;
	const unsigned	npcCount = p->npc->currentFloor->current_npcs->size;

	printTime(p->npc->currentBuilding->parentCity);
	printSeparator();
	printf("You are on floor %d of %s\n", p->npc->currentFloor->floorNumber, p->npc->currentBuilding->name);
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
	if (p->npc->currentFloor->floorNumber == 0)
		printf("0: Exit building\n");
	choice = safeInput_u(p->npc->currentFloor->floorNumber > 0, 3);
	switch (choice)
	{
	case 1:
		printf("Choose an office to enter:\n");
		for (unsigned i = 0; i < p->npc->currentFloor->floorTypeData.officeFloorData->office_count; i++)
		{
			printf("%d: Office %d\n", i + 1, p->npc->currentFloor->floorTypeData.officeFloorData->offices[i]->office_number);
		}
		choice = safeInput_u(1, p->npc->currentFloor->floorTypeData.officeFloorData->office_count);
		p->npc->currentOffice = p->npc->currentFloor->floorTypeData.officeFloorData->offices[choice - 1];
		addTime(1);
		break;

	case 2:
		if (npcCount == 0)
		{
			printf("There is no one to talk to.\n");
			break;
		}
		listNpcs(p->npc->currentFloor->current_npcs, 0);
		printf("Choose a person to talk to (0 to cancel): ");
		choice = safeInput_u(0, npcCount);
		if (choice == 0)
			break ;
		handle_dialogue(p, p->npc->currentFloor->current_npcs->data[choice - 1]);
		break;

	case 3:
		printf("Choose a floor to go to (0 to cancel):\n");
		for (unsigned i = 0; i < p->npc->currentBuilding->height; i++)
		{
			printf("%d: Floor %d\n", i + 1, i);
		}
		choice = safeInput_u(0, p->npc->currentBuilding->height);
		if (choice == 0)
			break ;
		p->npc->currentFloor = p->npc->currentBuilding->floors[choice - 1];
		addTime(1);
		break;

	case 0:
		printf("You exit the building.\n");
		p->npc->currentFloor = NULL;
		addTime(1);
		break;

	default:
		break;
	}
}

static void handleOutsideInteraction(t_player* p)
{
	unsigned		choice;
	const unsigned	npcCount = p->npc->currentBuilding->current_npcs->size;

	printTime(g_city);
	printSeparator();
	printf("You are outside at (%d, %d) in front of %s\n", p->npc->x, p->npc->y, p->npc->currentBuilding->name);
	if (npcCount > 0)
	{
		if (npcCount == 1)
			printf("There is 1 person here\n");
		else
			printf("There are %d people here\n", npcCount);
	}
	else
		printf("The street is empty.\n");
	printf("1: Enter building\n");
	printf("2: Move on the map\n");
	printf("3: Talk to someone\n");
	printf("4: Sleep on the bench\n");
	printf("0: Exit Game\n");
	choice = safeInput_u(0, 4);
	switch (choice)
	{
	case 1:
		p->npc->currentFloor = p->npc->currentBuilding->floors[0];
		break;

	case 2:
		handleMapMovement(p);
		break;

	case 3:
		if (npcCount == 0)
		{
			printf("There is no one to talk to.\n");
			break;
		}
		listNpcs(p->npc->currentBuilding->current_npcs, 0);
		printf("Choose a person to talk to (0 to cancel): ");
		choice = safeInput_u(0, npcCount);
		if (choice == 0)
			break ;
		handle_dialogue(p, p->npc->currentBuilding->current_npcs->data[choice - 1]);
		break;

	case 4:
		printf("How many hours do you want to sleep? (from 1 to 12): ");
		choice = safeInput_u(1, 12);
		g_city->addTime(choice * 60);
		printf("You slept for %d hours.\n", choice);
		break;
	case 0:
		// saveGame(g_city, p);
		printf("Exiting...\n");
		exit(0);
		break;

	default:
		break;
	}
}

// Основная функция
void playerControl(t_player* p) {
	if (p->npc->currentRoom)
	{
		handleResidentialRoom(p);
	}
	else if (p->npc->currentOffice)
	{
		handleOffice(p);
	}
	else if (p->npc->currentFloor)
	{
		if (p->npc->currentBuilding->building_type == RESIDENTIAL)
		{
			handleResidentialFloor(p);
		}
		else if (p->npc->currentBuilding->building_type == OFFICE)
		{
			handleOfficeFloor(p);
		}
	}
	else
	{
		handleOutsideInteraction(p);
	}
}
