#include "../include/structures.h"
#include "../include/city.h"
#include "../include/ui.h"

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

static void ask_about_npc(t_player *p, t_npc *n)
{
	size_t i = 0;
	t_relationship *r = NULL;
	t_npc **seen = NULL;
	unsigned choice;

	printf("Ask about:\n");
	seen = p->known_npcs->data;
	for (size_t i = 0; i < p->known_npcs->size; i++)
		printf("%zu: %s %s\n", i + 1, seen[i]->firstName, seen[i]->lastName);
	choice = safeInput_u(1, i - 1) - 1;

	if (seen[choice] == n)
	{
		printf("\"That's me\"\n");
		return ;
	}

	r = check_rel(n, seen[choice]);
	if (!r)
	{
		printf("\"I dont know anything about them\n\"");
		return ;
	}

	printf("\"I know them, ");
	switch (r->type)
	{
	case NEUTRAL:
		printf("nothing special, ");
		break;

	case FAMILY:
		printf("they're my family, ");
		break;

	case FRIEND:
		printf("we're friends, ");
		break;

	case COWORKER:
		printf("we're coworkers, ");
		break;
	}
	if (r->strength < 20)
		printf("i hate them\"\n");
	else if (r->strength < 70)
		printf("not much to say about it\"\n");
	else
		printf("they're great\"\n");
}

void handle_dialogue(t_player *p, t_npc *n)
{
	vec_append(p->known_npcs, n);
	greeting(p, n);
	unsigned choice;
	printf("1: ask about someone\n");
	choice = safeInput_u(1, 1);
	switch (choice)
	{
	case 1:
		ask_about_npc(p, n);
		break;

	default:
		break;
	}
}
