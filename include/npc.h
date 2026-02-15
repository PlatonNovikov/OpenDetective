#ifndef NPC_H
#define NPC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "structures.h"
#include "city.h"

#define MAX_RELATIONSHIPS 100
#define EYE_COLOR_COUNT 4
#define HAIR_COLOR_COUNT 5
#define BLOOD_TYPE_COUNT 8
#define FINGERPRINT_TYPE_COUNT 20

typedef enum e_relationship_type {
	FAMILY,
	FRIEND,
	COWORKER,
} e_relationship_type;

typedef struct t_relationship {
	t_npc				*target;	// Pointer to the related NPC
	e_relationship_type	type;		// Type of relationship
	unsigned			strength;	// 0-100 (e.g., closeness, trust)
	unsigned			count;		// Number of interactions
} t_relationship;

typedef struct t_schedule {
	unsigned	work_start;
	unsigned	work_end;
} t_schedule;

typedef struct t_leg{
	unsigned health;
} t_leg;

typedef struct t_arm{
	unsigned health;
} t_arm;

typedef struct t_head{
	unsigned health;
} t_head;

typedef struct t_torso{
	unsigned health;
} t_torso;

typedef enum e_eye_color {
	EYE_COLOR_BLUE,
	EYE_COLOR_GREEN,
	EYE_COLOR_BROWN,
	EYE_COLOR_GRAY,
} e_eye_color;

typedef enum e_hair_color {
	HAIR_COLOR_BLACK,
	HAIR_COLOR_BROWN,
	HAIR_COLOR_BLONDE,
	HAIR_COLOR_RED,
	HAIR_COLOR_GRAY,
} e_hair_color;

typedef enum e_blood_type {
	BLOOD_TYPE_A_POS,
	BLOOD_TYPE_A_NEG,
	BLOOD_TYPE_B_POS,
	BLOOD_TYPE_B_NEG,
	BLOOD_TYPE_AB_POS,
	BLOOD_TYPE_AB_NEG,
	BLOOD_TYPE_O_POS,
	BLOOD_TYPE_O_NEG,
} e_blood_type;

typedef enum e_fingerprint {
	FINGER_PRINT_A1, FINGER_PRINT_A2, FINGER_PRINT_A3, FINGER_PRINT_A4, FINGER_PRINT_A5,
	FINGER_PRINT_B1, FINGER_PRINT_B2, FINGER_PRINT_B3, FINGER_PRINT_B4, FINGER_PRINT_B5,
	FINGER_PRINT_C1, FINGER_PRINT_C2, FINGER_PRINT_C3, FINGER_PRINT_C4, FINGER_PRINT_C5,
	FINGER_PRINT_D1, FINGER_PRINT_D2, FINGER_PRINT_D3, FINGER_PRINT_D4, FINGER_PRINT_D5,
} e_fingerprint;

typedef struct t_npc {
	char			firstName[100];
	char			lastName[100];
	t_room			*placeOfResidence;
	t_office		*placeOfWork;
	unsigned 		x,y;
	t_building		*currentBuilding;
	t_floor			*currentFloor;
	t_room			*currentRoom;
	t_office		*currentOffice;
	int				isAlive;

	t_relationship	*relationships; // Dynamic array of relationships
	unsigned		relationshipCount;
	unsigned		sanity;         // 0-100

	t_schedule		*dailySchedule;

	//body parts
	t_leg			leftLeg;
	t_leg			rightLeg;
	t_arm			leftArm;
	t_arm			rightArm;
	t_head			headPart;
	t_torso			torsoPart;

	//distinctive features
	e_eye_color		eyeColor;
	e_hair_color	hairColor;
	e_blood_type	bloodType;
	e_fingerprint	fingerprintType;

	void			(*tick)(struct t_npc* n, t_city* c);
} t_npc;

void generate_npc(t_npc* new_npc, t_city* c);

void generate_family(unsigned count, t_npc** family, t_city* c);

void gotoWork(t_npc* n);

void npc_tick(t_npc* n, t_city* c);

void add_npc(t_npc *n, t_npc **npc_list);

void remove_npc(t_npc *n, t_npc **npc_list);

#endif
