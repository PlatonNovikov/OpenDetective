#include "../include/structures.h"
#include "../include/city.h"
#include "../include/ui.h"

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

static void ask_about_npc(t_player *p, t_npc *n)
{
	t_relationship *r = NULL;
	t_npc *choice;

	choice = choose_known_npc(p);

	if (choice == n)
	{
		printf("\"That's me\"\n");
		return ;
	}

	r = check_rel(n, choice);
	if (!r)
	{
		printf("\"I dont know anything about them\"\n");
		return ;
	}

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
		printf("they're great\"\n");
}

void handle_dialogue(t_player *p, t_npc *n)
{
	if (!know_dup(p, n))
		vec_append(p->known_npcs, n);
	greeting(p, n);
	unsigned choice;
	printf("0: stop talking\n");
	printf("1: ask about someone\n");
	choice = safeInput_u(0, 1);
	switch (choice)
	{
	case 1:
		ask_about_npc(p, n);
		break;

	default:
		break;
	}
}
