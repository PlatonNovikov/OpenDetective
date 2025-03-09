#ifndef TYPES_H
#define TYPES_H

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