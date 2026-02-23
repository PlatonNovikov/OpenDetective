#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "vector.h"

#define PREFIX_COUNT 50
#define BASE_COUNT 50
#define SUFFIX_COUNT 50
#define ARRAY_SIZE 100
#define FIRST_HALF_COMPANY 50
#define SECOND_HALF_COMPANY 50
#define MAX_NPC_PRESENT 50
#define THE_ANSWER_TO_LIFE_THE_UNIVERSE_AND_EVERYTHING 42

#define ROOMS_PER_FLOOR 4
#define ASSIGNED_NPC_PER_ROOM 4

#define OFFICES_PER_FLOOR 3
#define EMPLOYEES_PER_OFFICE 5

#define clear() printf("\033[H\033[J")

extern const char first_names[ARRAY_SIZE][50];

extern const char last_names[ARRAY_SIZE][50];

extern const char *prefixes[PREFIX_COUNT];

extern const char *bases[BASE_COUNT];

extern const char *suffixes[SUFFIX_COUNT];

extern const char *first_half[FIRST_HALF_COMPANY];

extern const char *second_half[SECOND_HALF_COMPANY];

typedef enum e_type {
	RESIDENTIAL, // Жилой этаж
	COMMERCIAL,  // Коммерческий этаж
	OFFICE  // Промышленный этаж
} e_type;

// Forward declaration of npc struct
typedef struct t_npc t_npc;
typedef struct t_room t_room;
typedef struct t_residentialFloor t_residentialFloor;
typedef struct t_office t_office;
typedef struct t_officeFloor t_officeFloor;
typedef struct t_floor t_floor;
typedef struct t_building t_building;
typedef struct t_city t_city;
typedef struct t_player t_player;
typedef struct t_relationship t_relationship;

typedef struct t_room {
	t_vec		*assigned_npcs; // (t_npc *) Array of NPC pointers
	t_vec		*current_npcs;  // (t_npc *) Currently present NPCs
	unsigned 	room_number;
	t_floor		*parentFloor;
} t_room;

typedef struct t_residentialFloor{
	t_room		**rooms;
	unsigned	room_count;
	t_floor		*parentFloor;
} t_residentialFloor;

typedef struct t_office{
	char		name[100];
	t_npc		**employees;
	unsigned	employee_count;
	t_floor		*parentFloor;
	unsigned	office_number;
	t_vec		*current_npcs;  // (t_npc *) Currently present NPCs
} t_office;

typedef struct t_officeFloor{
	t_office	**offices;
	unsigned 	office_count;
	t_floor		*parentFloor;
} t_officeFloor;

typedef struct t_floor {
	unsigned				floorNumber;
	union {
		t_officeFloor*		officeFloorData;
		t_residentialFloor*	residentialFloorData;
	} floorTypeData;
	e_type					floorType;
	t_building				*parentBuilding;
	t_vec					*current_npcs;  // (t_npc *) Currently present NPCs
} t_floor;

typedef struct t_building {
	char		name[100];
	unsigned	x, y;
	unsigned	height;
	t_floor		**floors;
	t_city		*parentCity;
	e_type		building_type;
	t_vec		*current_npcs;  // (t_npc *) Currently present NPCs
} t_building;

typedef t_npc t_inner_npc;
// type that allows player interact with npc the same way as npcs with other npcs
typedef struct t_player {
	char		name[100];
	t_inner_npc	*npc;
} t_player;

#endif
