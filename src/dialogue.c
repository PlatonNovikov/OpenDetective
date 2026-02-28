#include "../include/structures.h"
#include "../include/city.h"
#include "../include/ui.h"

// returns vector of all relationship of given npc
static t_vec *list_npcs_known_npcs(t_npc *n)
{
	t_vec *rel = init_vec();
	t_relationship *r;
	for (r = g_city->rel; r != NULL; r = r->hh.next)
	{
		if (r->from == n)
			vec_append(rel, r);
	}
	return (rel);
}
// checks if player is already knows given npc
static bool know_dup(t_player *p, t_npc *n)
{
	for (size_t i = 0; i < p->known_npcs->size; i++)
	{
		if (p->known_npcs->data[i] == n)
			return (true);
	}
	return (false);
}

static void greeting(t_player *p, t_npc *n)
{
	t_relationship *rel = get_rel(n, p->npc);
	if (rel->strength < 20)
		printf("%s %s says: Hello there, you fucker\n", n->firstName, n->lastName);
	else if (rel->strength < 70)
		printf("%s %s says: Hello there\n", n->firstName, n->lastName);
	else
		printf("%s %s says: Wassup homie? *swag* *swag*\n", n->firstName, n->lastName);
}

static t_npc *choose_known_npc(t_player *p)
{
	unsigned choice;
	size_t i;
	t_npc **seen = (t_npc **)p->known_npcs->data;
	for (i = 0; i < p->known_npcs->size; i++)
		printf("%zu: %s %s\n", i + 1, seen[i]->firstName, seen[i]->lastName);
	choice = safeInput_u(1, i) - 1;
	return (seen[choice]);
}

static void introduce_person(t_relationship *r)
{
	printf("\"I know them, ");
	if (!r->type)
		printf("nothing special, ");

	if (r->type & FAMILY)
		printf("they're my family, ");

	if (r->type & FRIEND)
		printf("we're friends, ");

	if (r->type & COWORKER)
		printf("we're coworkers, ");

	if (r->strength < 20)
		printf("i hate them\"\n");
	else if (r->strength < 70)
		printf("not much to say about it\"\n");
	else
		printf("they're great\"\n\n");
}

static void tell_npc_workplace(t_npc *n, t_npc *to_ask)
{
	if (!to_ask->placeOfWork)
	{
		printf("They don't work anywhere\n");
		return ;
	}
	t_building *b = to_ask->placeOfWork->parentFloor->parentBuilding;
	t_floor *f = to_ask->placeOfWork->parentFloor;
	t_office *o = to_ask->placeOfWork;
	printf("They work at office number %d, floor number %d at building %s (x: %d, y: %d)\n", o->office_number, f->floorNumber, b->name, b->x, b->y);
}

static void tell_npc_residence(t_npc *n, t_npc *to_ask)
{
	t_building *b = to_ask->placeOfResidence->parentFloor->parentBuilding;
	t_floor *f = to_ask->placeOfResidence->parentFloor;
	t_room *r = to_ask->placeOfResidence;
	printf("They live in room number %d, floor number %d at building %s (x: %d, y: %d)\n", r->room_number, f->floorNumber, b->name, b->x, b->y);
}

static void ask_about_npc(t_player *p, t_npc *n)
{
	t_relationship	*r = NULL;
	int				choice = -1;
	t_npc			*to_ask;

	to_ask = choose_known_npc(p);

	if (to_ask == n)
	{
		printf("\"That's me\"\n");
		return ;
	}

	r = check_rel(n, to_ask);
	if (!r)
	{
		printf("\"I dont know anything about them\"\n");
		return ;
	}
	introduce_person(r);

	while (choice)
	{
		printf("1: ask about %s %s's place of residence\n", to_ask->firstName, to_ask->lastName);
		printf("2: ask about %s %s's place of workplace\n", to_ask->firstName, to_ask->lastName);
		printf("0: stop asking about %s %s\n", to_ask->firstName, to_ask->lastName);
		choice = safeInput_u(0, 2);

		switch (choice)
		{
		case 1:
			tell_npc_residence(n, to_ask);
			break;

		case 2:
			tell_npc_workplace(n, to_ask);
			break;

		default:
			break;
		}
	}
}

static void tell_about_connections(t_player *p, t_npc *n)
{
	t_vec					*rel_vec = list_npcs_known_npcs(n);
	const t_relationship	**rel_list = rel_vec->data;

	for (size_t i = 0; i < rel_vec->size; i++)
	{
		printf("%ld: %s %s. Type: %d\n", i + 1, rel_list[i]->target->firstName, rel_list[i]->target->lastName, rel_list[i]->type);
		vec_append(p->known_npcs, rel_list[i]->target);
	}
	vec_free(rel_vec);
}

void handle_dialogue(t_player *p, t_npc *n)
{
	if (!know_dup(p, n))
		vec_append(p->known_npcs, n);
	greeting(p, n);
	unsigned choice;
	printf("1: ask about someone\n");
	printf("2: ask about their connections\n");
	printf("0: stop talking\n");
	choice = safeInput_u(0, 2);
	switch (choice)
	{
	case 1:
		ask_about_npc(p, n);
		break;

	case 2:
		tell_about_connections(p, n);
		break;

	default:
		break;
	}
}
