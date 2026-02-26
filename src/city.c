#include "../include/city.h"
#include "../include/rand.h"
#include "../include/vector.h"
//boykisser
//writing it a year later. I have no idea why i wrote "boykisser", but im leaving it here lol

// allocates and generates offices at given floor
static void f_office_gen(t_floor *parent_f)
{
	parent_f->floorTypeData.officeFloorData = calloc(1, sizeof(t_officeFloor));
	t_officeFloor *o_f = parent_f->floorTypeData.officeFloorData;
	if (!o_f) {
		printf("Error allocating memory for office floor data.\n");
		exit(1);
	}
	o_f->office_count = OFFICES_PER_FLOOR;
	o_f->parentFloor = parent_f;
	o_f->offices = calloc(o_f->office_count, sizeof(t_office*));
	if (!o_f->offices) {
		printf("Error allocating memory for offices.\n");
		exit(1);
	}

	for (unsigned i = 0; i < o_f->office_count; i++) {
		//printf("Allocating memory for office...\n");
		t_office *o = calloc(1, sizeof(t_office));
		if (!o) {
			printf("Error allocating memory for office.\n");
			exit(1);
		}
		o->employees = init_vec();
		o->current_npcs = init_vec();
		o->parentFloor = parent_f;
		o->office_number = i;
		o_f->offices[i] = o;
	}
}

// allocates and generates residential floor at given floor
static void f_residential_gen(t_floor *parent_f)
{
	parent_f->floorTypeData.residentialFloorData = calloc(1, sizeof(t_residentialFloor));
	t_residentialFloor *r_f = parent_f->floorTypeData.residentialFloorData;
	//printf("Allocating memory for residential floor data...\n");
	if (!r_f) {
		printf("Error allocating memory for residential floor data.\n");
		exit(1);
	}
	r_f->room_count = ROOMS_PER_FLOOR;
	r_f->rooms = calloc(ROOMS_PER_FLOOR, sizeof(t_room*));
	//printf("Allocating memory for rooms...\n");
	if (!r_f->rooms) {
		printf("Error allocating memory for rooms.\n");
		exit(1);
	}

	for (unsigned i = 0; i < ROOMS_PER_FLOOR; i++) {
		t_room* r = (t_room*)calloc(1, sizeof(t_room));
		if (!r) {
			printf("Error allocating memory for room.\n");
			exit(1);
		}
		r->assigned_npcs = init_vec();
		if (!r->assigned_npcs) {
			printf("Error allocating memory for NPCs.\n");
			exit(1);
		}
		r->current_npcs = init_vec();
		if (!r->current_npcs) {
			printf("Error allocating memory for current NPCs.\n");
			exit(1);
		}
		r->parentFloor = parent_f;
		r->room_number = i;
		r_f->rooms[i] = r;
	}
}

// allocates and generates floor at given stage of a parent building
static void floor_gen(t_building *parent_b, unsigned f_number)
{
	t_floor* f = (t_floor*)calloc(1, sizeof(t_floor));
	if (!f) {
		printf("Error allocating memory for floor.\n");
		exit(1);
	}

	f->floorNumber = f_number;
	f->parentBuilding = parent_b;

	f->current_npcs = init_vec();

	switch (parent_b->building_type) {
		case RESIDENTIAL:
			f->floorType = RESIDENTIAL;
			f_residential_gen(f);
			break;

		case OFFICE:
			f->floorType = OFFICE;
			f_office_gen(f);
			break;
		default:
			printf("Unknown building type.\n");
			exit(1);
		}
	parent_b->floors[f_number] = f;
}

// allocates and generates array of floors at given building
void allocateFloors(t_building* b) {
	//printf("Allocating memory for floors...\n");
	b->floors = (t_floor**)calloc(b->height, sizeof(t_floor*));
	if (!b->floors) {
		printf("Error allocating memory for floors.\n");
		exit(1);
	}

	for (unsigned i = 0; i < b->height; i++) {
		floor_gen(b, i);
	}
	//printf("Done!\n");
}

// returns a pointer to a free room
t_room* getFreeResidence(){
	unsigned countC = (unsigned)zurand() % g_city->residentialBuildings->size;
	unsigned countB = countC;
	unsigned floorC = (unsigned)zurand() % ((t_building *)g_city->residentialBuildings->data[countC])->height;
	unsigned floorB = floorC;
	unsigned roomC = (unsigned)zurand() % 4;
	unsigned roomB = roomC;
	while (vec_get(((t_building *)g_city->residentialBuildings->data[countC])->floors[floorC]->floorTypeData.residentialFloorData->rooms[roomC]->assigned_npcs, 0)){
		if (roomC < 3){
			roomC++;
		} else {
			roomC = 0;
			if (floorC < ((t_building *)g_city->residentialBuildings->data[countC])->height - 1){
				floorC++;
			} else {
				floorC = 0;
				if (countC < g_city->residentialBuildings->size - 1){
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
	return ((t_building *)g_city->residentialBuildings->data[countC])->floors[floorC]->floorTypeData.residentialFloorData->rooms[roomC];
}

// returns a pointer to a free office
t_office* getFreeWorkplace(){
	unsigned countC = (unsigned)zurand() % g_city->officeBuildings->size;
	unsigned countB = countC;
	unsigned floorC = (unsigned)zurand() % ((t_building *)g_city->officeBuildings->data[countC])->height;
	unsigned floorB = floorC;
	unsigned officeC = (unsigned)zurand() % ((t_building *)g_city->officeBuildings->data[countC])->floors[floorC]->floorTypeData.officeFloorData->office_count;
	unsigned officeB = officeC;
	while (((t_building *)g_city->officeBuildings->data[countC])->floors[floorC]->floorTypeData.officeFloorData->offices[officeC]->employees->size == 5){
		if (officeC < ((t_building *)g_city->officeBuildings->data[countC])->floors[floorC]->floorTypeData.officeFloorData->office_count - 1){
			officeC++;
		} else {
			officeC = 0;
			if (floorC < ((t_building *)g_city->officeBuildings->data[countC])->height - 1){
				floorC++;
			} else {
				floorC = 0;
				if (countC < (g_city->officeBuildings->size - 1)){
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
	return ((t_building *)g_city->officeBuildings->data[countC])->floors[floorC]->floorTypeData.officeFloorData->offices[officeC];
}

void set_coworkers()
{
	for (size_t i = 0; i < g_city->officeBuildings->size; i++)
	{
		t_building *b = g_city->officeBuildings->data[i];
		for (size_t j = 0; j < b->height; j++)
		{
			t_officeFloor *of = b->floors[j]->floorTypeData.officeFloorData;
			for (size_t k = 0; k < of->office_count; k++)
			{
				t_office *o = of->offices[k];
				for (size_t l = 0; l < o->employees->size; l++)
				{
					t_npc *n = o->employees->data[l];
					for (size_t m = 0; m < o->employees->size; m++)
					{
						if (m == l)
							continue;
						t_relationship *r = get_rel(n, o->employees->data[m]);
						r->type |= COWORKER;
					}
				}
			}
		}
	}
}

void populateCity(){
	for (unsigned i = 0; i < g_city->residentialBuildings->size; i++){
		for (unsigned j = 0; j < ((t_building *)g_city->residentialBuildings->data[i])->height; j++){
			for (unsigned k = 0; k < ((t_building *)g_city->residentialBuildings->data[i])->floors[j]->floorTypeData.residentialFloorData->room_count; k++){
				t_room* r = ((t_building *)g_city->residentialBuildings->data[i])->floors[j]->floorTypeData.residentialFloorData->rooms[k];
				if(rand()%4){
					t_npc* new_npc = (t_npc*)calloc(1, sizeof(t_npc));
					if (!new_npc) {
						printf("Error allocating memory for NPC.\n");
						exit(1);
					}
					generate_npc(new_npc);
					new_npc->placeOfResidence = getFreeResidence(g_city);
					vec_append(new_npc->placeOfResidence->assigned_npcs, new_npc);
					new_npc->x = new_npc->placeOfResidence->parentFloor->parentBuilding->x;
					new_npc->y = new_npc->placeOfResidence->parentFloor->parentBuilding->y;
					new_npc->placeOfWork = getFreeWorkplace(g_city);
					new_npc->currentRoom = new_npc->placeOfResidence;
					new_npc->currentFloor = new_npc->placeOfResidence->parentFloor;
					new_npc->currentBuilding = new_npc->placeOfResidence->parentFloor->parentBuilding;
					vec_append(r->current_npcs, new_npc);
					if (new_npc->placeOfWork)
					{
						vec_append(new_npc->placeOfWork->employees, new_npc);
						new_npc->dailySchedule->work_start = 9 * 60;	//9:00
						new_npc->dailySchedule->work_end = 17 * 60;		//17:00
					}
				}
				else{
					t_vec* family = r->assigned_npcs;
					unsigned count = (unsigned)zurand() % 3 + 2;
					generate_family(count, family);
					((t_npc *)family->data[0])->placeOfResidence = getFreeResidence(g_city);
					for (unsigned l = 0; l < count; l++)
					{
						t_npc* n = family->data[l];
						vec_append(r->current_npcs, n);
						n->x = ((t_npc *)family->data[0])->placeOfResidence->parentFloor->parentBuilding->x;
						n->y = ((t_npc *)family->data[0])->placeOfResidence->parentFloor->parentBuilding->y;
						n->placeOfResidence = ((t_npc *)family->data[0])->placeOfResidence;
						n->placeOfWork = getFreeWorkplace(g_city);
						n->currentRoom = r;
						n->currentFloor = n->placeOfResidence->parentFloor;
						n->currentBuilding = n->placeOfResidence->parentFloor->parentBuilding;
						if (n->placeOfWork)
						{
							vec_append(n->placeOfWork->employees, n);
							n->dailySchedule->work_start = 9 * 60;	//9:00
							n->dailySchedule->work_end = 17 * 60;	//17:00
						}
					}

				}
			}
		}
	}
}

void timeManager(t_city* g_city)
{
	t_npc *n = NULL;

	for (unsigned i = 0; i < g_city->npcList->size; i++)
	{
		n = g_city->npcList->data[i];
		n->tick(n);
	}
}

void addTime(unsigned minutes)
{
	for (unsigned i = 0; i < minutes; i++){
		g_city->time += 1;
		timeManager(g_city);
	}
}

size_t currentDay(void) //returns current day number
{
	return (g_city->time / (60 * 24));
}

size_t currentTimeHour(void) //returns current hour
{
	return ((g_city->time / 60) % 24);
}


size_t currentTimeMinute(void) //returns current minute
{
	return (g_city->time % 60);
}

size_t currentDayMinute(void) //returns current minute
{
	return (g_city->time % (60 * 24));
}
