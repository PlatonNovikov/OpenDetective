#ifndef STRUCTURES_H
#define STRUCTURES_H

#define PREFIX_COUNT 50
#define BASE_COUNT 50
#define SUFFIX_COUNT 50
#define ARRAY_SIZE 100
#define FIRST_HALF_COMPANY 50
#define SECOND_HALF_COMPANY 50
#define MAX_RELATIONSHIPS 100
#define THE_ANSWER_TO_LIFE_THE_UNIVERSE_AND_EVERYTHING 42
#define clear() printf("\033[H\033[J")

extern const char first_names[ARRAY_SIZE][50];

extern const char last_names[ARRAY_SIZE][50];

extern const char *prefixes[PREFIX_COUNT];

extern const char *bases[BASE_COUNT];

extern const char *suffixes[SUFFIX_COUNT];

extern const char *first_half[FIRST_HALF_COMPANY];

extern const char *second_half[SECOND_HALF_COMPANY];

typedef enum type {
    RESIDENTIAL, // Жилой этаж
    COMMERCIAL,  // Коммерческий этаж
    OFFICE  // Промышленный этаж
} type;

typedef enum relationship_type {
    FAMILY,
    FRIEND,
    COWORKER,
} relationship_type;

// Forward declaration of npc struct
typedef struct npc npc;
typedef struct room room;
typedef struct residentialFloor residentialFloor;
typedef struct office office;
typedef struct officeFloor officeFloor;
typedef struct floor floor;
typedef struct building building;
typedef struct city city;
typedef struct player player;

typedef struct relationship {
    npc* target;                // Pointer to the related NPC
    relationship_type type;     // Type of relationship
    int strength;               // 0-100 (e.g., closeness, trust)
    int count;                  // Number of interactions
} relationship;

typedef struct npc {
    char firstName[100];
    char lastName[100];
    room* placeOfResidence;
    office* placeOfWork;
    void* currentPlace;
    relationship* relationships; // Dynamic array of relationships
    int relationshipCount;
} npc;

typedef struct room {
    npc** npcs;          // Array of NPC pointers
    int npc_count;
    int room_number;
    floor* parentFloor;
} room;

typedef struct residentialFloor{
    room** rooms;
    int room_count;
    floor* parentFloor;
}residentialFloor;

typedef struct office{
    char name[100];
    npc** employees;
    int employee_count;
    floor* parentFloor;
    int office_number;
}office;

typedef struct officeFloor{
    office** offices;
    int office_count;
    floor* parentFloor;
}officeFloor;

typedef struct floor {
    int floorNumber;
    type floor_type;
    void* floor_type_data;
    building* parentBuilding;
} floor;

typedef struct building {
    char name[100];
    int x, y;
    int height;
    floor** floors;
    city* parentCity;
    type building_type;
} building;

typedef struct city {
    char name[100];
    int width, height;
    building*** cityMap;
    building** residentialBuildingsList;
    building** officeBuildingsList;
    int residentialBuildings;
    int officeBuildings;
    int time;  // 0-23 (часы)
    int day;   // Дни с начала игры
} city;

typedef struct player {
    int x;
    int y;
    building* currentBuilding;
    floor* currentFloor;
    room* currentRoom;
    char name[100];
} player;

#endif