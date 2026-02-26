#include <inttypes.h>

#include "../include/npc.h"

unsigned rand_sanity()
{
	double u = rand() / (RAND_MAX + 1.0);
	double lambda = 4.0; // чем больше λ — тем сильнее шанс больших чисел

	double x = -log(1 - u) / lambda; // экспонента
	if (x > 1.0) x = 1.0; // обрезаем до 0..1

	return (100 - (unsigned)(x * 100.0));
}

void generate_npc(t_npc* new_npc) {
	snprintf(new_npc->firstName, sizeof(new_npc->firstName), "%s", first_names[rand() % ARRAY_SIZE]);
	snprintf(new_npc->lastName, sizeof(new_npc->lastName), "%s", last_names[rand() % ARRAY_SIZE]);\
	new_npc->dailySchedule = calloc(1, sizeof(t_schedule));
	if (!new_npc->dailySchedule)
	{
		printf("Error allocating memory for daily schedule.\n");
		exit(1);
	}
	new_npc->tick = npc_tick;

	new_npc->isAlive = 1;
	new_npc->leftLeg.health = 100;
	new_npc->rightLeg.health = 100;
	new_npc->leftArm.health = 100;
	new_npc->rightArm.health = 100;
	new_npc->headPart.health = 100;
	new_npc->torsoPart.health = 100;

	new_npc->eyeColor = rand() % 4;
	new_npc->hairColor = rand() % 5;
	new_npc->bloodType = rand() % 8;
	new_npc->fingerprintType = rand() % 20;

	new_npc->sanity = rand_sanity();

	vec_append(g_city->npcList, new_npc);
}

void generate_family(unsigned count, t_vec *family) {
	t_npc	*n = NULL;
	if (!family) {
		printf("Error allocating memory for family.\n");
		exit(1);
	}
	for (unsigned i = 0; i < count; i++){
		n = calloc(1, sizeof(t_npc));
		if (!n) {
			printf("Error allocating memory for NPC.\n");
			exit(1);
		}
		vec_append(family, n);
		generate_npc(n);
		strcpy(n->lastName, ((t_npc *)family->data[0])->lastName);
	}

	for (unsigned i = 0; i < count; i++){
		n = family->data[i];
		for (unsigned j = 0; j < count; j++){
			if (i == j){
				continue;
			}
			t_relationship* r = get_rel(n, family->data[j]);
			r->strength = 50;
			r->target = family->data[j];
			r->type |= FAMILY;
		}
	}
}

void gotoWork(t_npc* n){
	//check if npc has work or if he is already there
	if(!n->placeOfWork || n->currentOffice == n->placeOfWork)
	{
		return;
	}

	if (n->currentRoom)
	{
		vec_append(n->currentRoom->parentFloor->current_npcs, n);
		vec_ord_rm(n->currentRoom->current_npcs, n);
		n->currentRoom = NULL;
		return ;
	}
	if (n->currentFloor && (n->currentBuilding != n->placeOfWork->parentFloor->parentBuilding))
	{
		vec_append(n->currentFloor->parentBuilding->current_npcs, n);
		vec_ord_rm(n->currentFloor->current_npcs, n);
		n->currentFloor = NULL;
		return ;
	}
	unsigned work_x, work_y;
	work_x = n->placeOfWork->parentFloor->parentBuilding->x;
	work_y = n->placeOfWork->parentFloor->parentBuilding->y;
	if (n->currentBuilding->x != work_x || n->currentBuilding->y != work_y)
	{
		if (n->x < work_x)
			n->x++;
		else if (n->x > work_x)
			n->x--;
		else if (n->y < work_y)
			n->y++;
		else if (n->y > work_y)
			n->y--;
		vec_ord_rm(n->currentBuilding->current_npcs, n);
		n->currentBuilding = n->currentBuilding->parentCity->cityMap[n->x][n->y];
		vec_append(n->currentBuilding->current_npcs, n);
		return ;
	}
	if ((n->currentBuilding->x == work_x && n->currentBuilding->y == work_y) && !n->currentFloor)
	{
		n->currentFloor = n->placeOfWork->parentFloor;
		vec_append(n->currentFloor->current_npcs, n);
		vec_ord_rm(n->currentBuilding->current_npcs, n);
		return ;
	}
	if (n->currentFloor == n->placeOfWork->parentFloor)
	{
		n->currentOffice = n->placeOfWork;
		vec_append(n->currentOffice->current_npcs, n);
		vec_ord_rm(n->currentFloor->current_npcs, n);
		return ;
	}
}

void gotoHome(t_npc *n)
{
	if(!n->placeOfResidence || (n->placeOfResidence == n->currentRoom)){
		return ;
	}

	if (n->currentOffice)
	{
		vec_append(n->currentOffice->parentFloor->current_npcs, n);
		vec_ord_rm(n->currentOffice->current_npcs, n);
		n->currentOffice = NULL;
		return ;
	}
	if (n->currentFloor && (n->currentBuilding != n->placeOfResidence->parentFloor->parentBuilding))
	{
		vec_append(n->currentBuilding->current_npcs, n);
		vec_ord_rm(n->currentFloor->current_npcs, n);
		n->currentFloor = NULL;
		return ;
	}
	unsigned home_x, home_y;
	home_x = n->placeOfResidence->parentFloor->parentBuilding->x;
	home_y = n->placeOfResidence->parentFloor->parentBuilding->y;
	if (n->currentBuilding->x != home_x || n->currentBuilding->y != home_y)
	{
		if (n->x < home_x)
			n->x++;
		else if (n->x > home_x)
			n->x--;
		else if (n->y < home_y)
			n->y++;
		else if (n->y > home_y)
			n->y--;
		vec_ord_rm(n->currentBuilding->current_npcs, n);
		n->currentBuilding = n->currentBuilding->parentCity->cityMap[n->x][n->y];
		vec_append(n->currentBuilding->current_npcs, n);
		return ;
	}
	if ((n->currentBuilding->x == home_x && n->currentBuilding->y == home_y) && !n->currentFloor)
	{
		n->currentFloor = n->placeOfResidence->parentFloor;
		vec_append(n->currentFloor->current_npcs, n);
		vec_ord_rm(n->currentBuilding->current_npcs, n);
		return ;
	}
	if (n->currentFloor == n->placeOfResidence->parentFloor)
	{
		n->currentRoom = n->placeOfResidence;
		vec_append(n->currentRoom->current_npcs, n);
		vec_ord_rm(n->currentFloor->current_npcs, n);
		return ;
	}
}

void npc_tick(t_npc* n)
{
	if (!n->dailySchedule)
		return; // No schedule defined

	if (currentDayMinute() >= n->dailySchedule->work_start && currentDayMinute() < n->dailySchedule->work_end)
	{
		gotoWork(n);
	}
	else
	{
		gotoHome(n);
	}
}

static t_relationship	*gen_rel(t_npc *from, t_npc *to)
{
	t_relationship	*r = NULL;

	r = calloc(1, sizeof(t_relationship));
	if (!r)
		exit(EXIT_FAILURE);

	r->from = from;
	r->target = to;
	r->type = 0;
	r->strength = 50;
	r->key = (t_ptrs_key){(uintptr_t)from, (uintptr_t)to};
	return (r);
}

//return a pointer to a relationship between two given npcs
//if such relationship do not exist, creates one
t_relationship	*get_rel(t_npc *from, t_npc *to)
{
	t_ptrs_key 		k;
	t_relationship *o;
	o = NULL;
	k = (t_ptrs_key){(uintptr_t)from, (uintptr_t)to};
	HASH_FIND(hh, g_city->rel, &k, sizeof(t_ptrs_key), o);
	if (o)
		return (o);
	else
	{
		t_relationship *r = gen_rel(from, to);
		HASH_ADD(hh, g_city->rel, key, sizeof(t_ptrs_key), r);
		return (r);
	}
}

//return a pointer to a relationship between two given npcs
//if such relationship do not exist, return NULL
t_relationship	*check_rel(t_npc *from, t_npc *to)
{
	t_ptrs_key 		k;
	t_relationship *o;
	o = NULL;
	k = (t_ptrs_key){(uintptr_t)from, (uintptr_t)to};
	HASH_FIND(hh, g_city->rel, &k, sizeof(t_ptrs_key), o);
	return (o);
}
