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
		o->employee_count = 0;
		o->employees = (t_npc**)calloc(EMPLOYEES_PER_OFFICE, sizeof(t_npc*));
		if (!o->employees) {
			printf("Error allocating memory for employees.\n");
			exit(1);
		}
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
t_room* getFreeResidence(t_city* c){
	unsigned countC = (unsigned)zurand() % c->residentialBuildings->size;
	unsigned countB = countC;
	unsigned floorC = (unsigned)zurand() % ((t_building *)c->residentialBuildings->data[countC])->height;
	unsigned floorB = floorC;
	unsigned roomC = (unsigned)zurand() % 4;
	unsigned roomB = roomC;
	while (vec_get(((t_building *)c->residentialBuildings->data[countC])->floors[floorC]->floorTypeData.residentialFloorData->rooms[roomC]->assigned_npcs, 0)){
		if (roomC < 3){
			roomC++;
		} else {
			roomC = 0;
			if (floorC < ((t_building *)c->residentialBuildings->data[countC])->height - 1){
				floorC++;
			} else {
				floorC = 0;
				if (countC < c->residentialBuildings->size - 1){
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
	return ((t_building *)c->residentialBuildings->data[countC])->floors[floorC]->floorTypeData.residentialFloorData->rooms[roomC];
}

// returns a pointer to a free office
t_office* getFreeWorkplace(t_city* c){
	unsigned countC = (unsigned)zurand() % c->officeBuildings->size;
	unsigned countB = countC;
	unsigned floorC = (unsigned)zurand() % ((t_building *)c->officeBuildings->data[countC])->height;
	unsigned floorB = floorC;
	unsigned officeC = (unsigned)zurand() % ((t_building *)c->officeBuildings->data[countC])->floors[floorC]->floorTypeData.officeFloorData->office_count;
	unsigned officeB = officeC;
	while (((t_building *)c->officeBuildings->data[countC])->floors[floorC]->floorTypeData.officeFloorData->offices[officeC]->employee_count == 5){
		if (officeC < ((t_building *)c->officeBuildings->data[countC])->floors[floorC]->floorTypeData.officeFloorData->office_count - 1){
			officeC++;
		} else {
			officeC = 0;
			if (floorC < ((t_building *)c->officeBuildings->data[countC])->height - 1){
				floorC++;
			} else {
				floorC = 0;
				if (countC < (c->officeBuildings->size - 1)){
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
	return ((t_building *)c->officeBuildings->data[countC])->floors[floorC]->floorTypeData.officeFloorData->offices[officeC];
}

void populateCity(t_city* c){
	for (unsigned i = 0; i < c->residentialBuildings->size; i++){
		for (unsigned j = 0; j < ((t_building *)c->residentialBuildings->data[i])->height; j++){
			for (unsigned k = 0; k < ((t_building *)c->residentialBuildings->data[i])->floors[j]->floorTypeData.residentialFloorData->room_count; k++){
				t_room* r = ((t_building *)c->residentialBuildings->data[i])->floors[j]->floorTypeData.residentialFloorData->rooms[k];
				if(rand()%4){
					t_npc* new_npc = (t_npc*)calloc(1, sizeof(t_npc));
					if (!new_npc) {
						printf("Error allocating memory for NPC.\n");
						exit(1);
					}
					generate_npc(new_npc, c);
					new_npc->placeOfResidence = getFreeResidence(c);
					vec_append(new_npc->placeOfResidence->assigned_npcs, new_npc);
					new_npc->x = new_npc->placeOfResidence->parentFloor->parentBuilding->x;
					new_npc->y = new_npc->placeOfResidence->parentFloor->parentBuilding->y;
					new_npc->placeOfWork = getFreeWorkplace(c);
					new_npc->currentRoom = new_npc->placeOfResidence;
					new_npc->currentFloor = new_npc->placeOfResidence->parentFloor;
					new_npc->currentBuilding = new_npc->placeOfResidence->parentFloor->parentBuilding;
					vec_append(r->current_npcs, new_npc);
					if (new_npc->placeOfWork)
					{
						new_npc->placeOfWork->employees[new_npc->placeOfWork->employee_count] = new_npc;
						new_npc->dailySchedule->work_start = 9 * 60;	//9:00
						new_npc->dailySchedule->work_end = 17 * 60;		//17:00
						new_npc->placeOfWork->employee_count++;
					}
				}
				else{
					t_vec* family = r->assigned_npcs;
					unsigned count = (unsigned)zurand() % 3 + 2;
					generate_family(count, family, c);
					((t_npc *)family->data[0])->placeOfResidence = getFreeResidence(c);
					for (unsigned l = 0; l < count; l++)
					{
						vec_append(r->current_npcs, family->data[l]);
						((t_npc *)family->data[l])->x = ((t_npc *)family->data[0])->placeOfResidence->parentFloor->parentBuilding->x;
						((t_npc *)family->data[l])->y = ((t_npc *)family->data[0])->placeOfResidence->parentFloor->parentBuilding->y;
						((t_npc *)family->data[l])->placeOfResidence = ((t_npc *)family->data[0])->placeOfResidence;
						((t_npc *)family->data[l])->placeOfWork = getFreeWorkplace(c);
						((t_npc *)family->data[l])->currentRoom = r;
						((t_npc *)family->data[l])->currentFloor = ((t_npc *)family->data[l])->placeOfResidence->parentFloor;
						((t_npc *)family->data[l])->currentBuilding = ((t_npc *)family->data[l])->placeOfResidence->parentFloor->parentBuilding;
						if (((t_npc *)family->data[l])->placeOfWork)
						{
							((t_npc *)family->data[l])->placeOfWork->employees[((t_npc *)family->data[l])->placeOfWork->employee_count] = ((t_npc *)family->data[l]);
							((t_npc *)family->data[l])->placeOfWork->employee_count++;
							((t_npc *)family->data[l])->dailySchedule->work_start = 9 * 60;	//9:00
							((t_npc *)family->data[l])->dailySchedule->work_end = 17 * 60;	//17:00
						}
					}

				}
			}
		}
	}
}

void timeManager(t_city* c)
{
	t_npc *n = NULL;

	for (unsigned i = 0; i < c->npcList->size; i++)
	{
		n = c->npcList->data[i];
		n->tick(n, c);
	}
}

void addTime(t_city* c, unsigned minutes)
{
	for (unsigned i = 0; i < minutes; i++){
		c->time += 1;
		timeManager(c);
	}
}

size_t currentDay(t_city *c) //returns current day number
{
	return (c->time / (60 * 24));
}

size_t currentTimeHour(t_city *c) //returns current hour
{
	return ((c->time / 60) % 24);
}


size_t currentTimeMinute(t_city *c) //returns current minute
{
	return (c->time % 60);
}

size_t currentDayMinute(t_city *c) //returns current minute
{
	return (c->time % (60 * 24));
}
