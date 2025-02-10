#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PREFIX_COUNT 50
#define BASE_COUNT 50
#define SUFFIX_COUNT 50
#define ARRAY_SIZE 100
#define FIRST_HALF_COMPANY 50
#define SECOND_HALF_COMPANY 50
#define THE_ANSWER_TO_LIFE_THE_UNIVERSE_AND_EVERYTHING 42
#define clear() printf("\033[H\033[J")

const char first_names[ARRAY_SIZE][50] = {
    "James", "Mary", "Robert", "Patricia", "John", "Jennifer", "Michael", "Linda",
    "William", "Elizabeth", "David", "Barbara", "Richard", "Susan", "Joseph", "Jessica",
    "Thomas", "Sarah", "Charles", "Karen", "Christopher", "Nancy", "Daniel", "Lisa",
    "Matthew", "Betty", "Anthony", "Margaret", "Mark", "Sandra", "Donald", "Ashley",
    "Paul", "Kimberly", "Steven", "Emily", "Andrew", "Donna", "Kenneth", "Michelle",
    "Joshua", "Dorothy", "Kevin", "Carol", "Brian", "Rebecca", "George", "Sharon",
    "Edward", "Laura", "Ronald", "Cynthia", "Timothy", "Kathleen", "Jason", "Amy",
    "Jeffrey", "Shirley", "Ryan", "Angela", "Gary", "Helen", "Jacob", "Anna",
    "Nicholas", "Brenda", "Eric", "Pamela", "Jonathan", "Nicole", "Stephen", "Samantha",
    "Larry", "Katherine", "Justin", "Emma", "Scott", "Ruth", "Brandon", "Christine",
    "Benjamin", "Deborah", "Samuel", "Rachel", "Frank", "Catherine", "Gregory", "Carolyn",
    "Raymond", "Janet", "Alexander", "Maria", "Patrick", "Heather", "Jack", "Diane",
    "Dennis", "Virginia", "Jerry", "Julie"
    };

const char last_names[ARRAY_SIZE][50] = {
    "Smith", "Johnson", "Williams", "Jones", "Brown", "Davis", "Miller", "Wilson",
    "Moore", "Taylor", "Anderson", "Thomas", "Jackson", "White", "Harris", "Martin",
    "Thompson", "Garcia", "Martinez", "Robinson", "Clark", "Rodriguez", "Lewis", "Lee",
    "Walker", "Hall", "Allen", "Young", "Hernandez", "King", "Wright", "Lopez",
    "Hill", "Scott", "Green", "Adams", "Baker", "Gonzalez", "Nelson", "Carter",
    "Mitchell", "Perez", "Roberts", "Turner", "Phillips", "Campbell", "Parker", "Evans",
    "Edwards", "Collins", "Stewart", "Sanchez", "Morris", "Rogers", "Reed", "Cook",
    "Morgan", "Bell", "Murphy", "Bailey", "Rivera", "Cooper", "Richardson", "Cox",
    "Howard", "Ward", "Torres", "Peterson", "Gray", "Ramirez", "James", "Watson",
    "Brooks", "Kelly", "Sanders", "Price", "Bennett", "Wood", "Barnes", "Ross",
    "Henderson", "Coleman", "Jenkins", "Perry", "Powell", "Long", "Patterson", "Hughes",
    "Flores", "Washington", "Butler", "Simmons", "Foster", "Gonzales", "Bryant", "Alexander",
    "Russell", "Griffin", "Diaz", "Hayes"
    };

const char *prefixes[PREFIX_COUNT] = {
    "Sunny", "Shady", "River", "Mountain", "Blooming", "Oak", "Pine", "Maple", "Elm", "Willow",
    "Cherry", "Apple", "Peach", "Lemon", "Orange", "Cedar", "Birch", "Spruce", "Holly", "Rosewood",
    "Lavender", "Magnolia", "Lilac", "Palm", "Juniper", "Ash", "Chestnut", "Cottonwood", "Hickory", "Fir",
    "Alder", "Aspen", "Beech", "Hazel", "Mulberry", "Sycamore", "Sequoia", "Redwood", "Poplar", "Cypress",
    "Ebony", "Eucalyptus", "Yew", "Dogwood", "Honeysuckle", "Ivy", "Jasmine", "Rowan", "Elder", "Bay"
};

const char *bases[BASE_COUNT] = {
    "Lane", "Street", "Avenue", "Boulevard", "Drive", "Way", "Court", "Place", "Road", "Terrace",
    "Parkway", "Circle", "Crescent", "Square", "Alley", "Trail", "Close", "Row", "Esplanade", "Highway",
    "Bridge", "Walk", "Path", "Track", "Plaza", "Garden", "Quay", "Promenade", "Vista", "Loop",
    "Meadow", "Ridge", "Hill", "Valley", "Hollow", "Crossing", "Fork", "Glade", "Heights", "Edge",
    "Overlook", "Harbor", "Point", "Landing", "Bay", "Bluff", "Knoll", "Oaks", "Pines", "Springs"
};

const char *suffixes[SUFFIX_COUNT] = {
    "of Peace", "of Friendship", "of Glory", "of Victory", "of Freedom", "of Hope", "of Unity", "of Harmony", "of Joy", "of Dreams",
    "of Stars", "of Lights", "of Rivers", "of Hills", "of Forests", "of Flowers", "of Meadows", "of Valleys", "of Creeks", "of Shores",
    "of Haven", "of Serenity", "of Solitude", "of Grace", "of Charm", "of Wonder", "of Bliss", "of Delight", "of Tranquility", "of Bloom",
    "of Radiance", "of Splendor", "of Majesty", "of Inspiration", "of Whimsy", "of Heritage", "of Legacy", "of Eternity", "of Fortune", "of Prosperity",
    "of Sanctity", "of Purity", "of Courage", "of Bravery", "of Honor", "of Wisdom", "of Knowledge", "of Triumph", "of Discovery", "of Adventure"
};

const char *first_half[FIRST_HALF_COMPANY] = {
    "Tech", "Data", "Cyber", "Quantum", "Global", "Sky", "Future", "Net", "Digital", "Soft",
    "Mega", "Neo", "Alpha", "Blue", "Smart", "Core", "Eco", "Next", "Vision", "World",
    "Cloud", "Info", "Green", "Max", "Zen", "Vero", "Space", "Gen", "Secure", "Prime",
    "Virtual", "Flex", "Edge", "Inno", "Power", "Pro", "Data", "Logic", "Link", "Nova",
    "Perfect", "Bright", "Visionary", "Infinity", "Matrix", "Elite", "Start", "Techno", "Future",
    "Pixel"
};

const char *second_half[SECOND_HALF_COMPANY] = {
    "Solutions", "Systems", "Group", "Labs", "Enterprises", "Corporation", "Technologies", "Inc", "Co", "Consulting",
    "Networks", "Studios", "Design", "Industries", "Partners", "International", "Holdings", "Industries", "Consultants", 
    "Development", "Team", "Ventures", "Services", "Experts", "Works", "Global", "Digital", "Connections",
    "Research", "Power", "Tech", "Media", "Consult", "Core", "Industry", "Innovations", "Dynamics", "Advisors",
    "Creations", "Innovation", "Pioneers", "Future", "Solutions", "Systems", "Manufacturers", "Engineering", "Apps", 
    "Integrations", "Technica", "Strive"
};

char* generateCompanyName() {
    // Аллоцируем память для названия
    static char companyName[100];

    // Генерация случайных индексов для двух частей
    int firstPartIndex = rand()%FIRST_HALF_COMPANY;
    int secondPartIndex = rand()%SECOND_HALF_COMPANY;

    // Формирование полного названия
    snprintf(companyName, sizeof(companyName), "%s %s", first_half[firstPartIndex], second_half[secondPartIndex]);
    return companyName;
}

char* generate_street_name() {
    static char result[100];
    const char *prefix = prefixes[rand() % PREFIX_COUNT];
    const char *base = bases[rand() % BASE_COUNT];
    const char *suffix = suffixes[rand() % SUFFIX_COUNT];

    snprintf(result, sizeof(result), "%s %s %s", prefix, base, suffix);
    return result;
}

typedef enum type {
    RESIDENTIAL, // Жилой этаж
    COMMERCIAL,  // Коммерческий этаж
    OFFICE  // Промышленный этаж
} type;

typedef enum relationship_type {
    FAMILY,
    FRIEND,
    COWORKER,
    ROMANTIC
} relationship_type;

// Forward declaration of npc struct
typedef struct npc npc;

typedef struct relationship {
    npc* target;                // Pointer to the related NPC
    relationship_type type;     // Type of relationship
    int strength;               // 0-100 (e.g., closeness, trust)
} relationship;

typedef struct npc {
    char firstName[100];
    char lastName[100];
    void* placeOfResidence;
    void* placeOfWork;
    void* currentPlace;
    relationship* relationships; // Dynamic array of relationships
    int relationshipCount;
} npc;

typedef struct room {
    npc** npcs;          // Array of NPC pointers
    int npc_count;
    void* parentFloor;
    int room_number;
} room;

typedef struct residentialFloor{
    room** rooms;
    int room_count;
}residentialFloor;

typedef struct office{
    char name[100];
    npc** employees;
    int employee_count;
}office;

typedef struct officeFloor{
    office** offices;
    int office_count;
}officeFloor;

typedef struct floor {
    int floorNumber;
    type floor_type;
    void* floor_type_data;
} floor;

typedef struct building {
    char name[100];
    int x, y;
    int height;
    floor** floors;
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
} city;

typedef struct player {
    int x;
    int y;
    building* currentBuilding;
    floor* currentFloor;
    room* currentRoom;
    char name[100];
} player;


void allocateFloors(building* b) {
    // Выделяем память для этажей
    b->floors = (floor**)malloc(b->height * sizeof(floor*));
    if (!b->floors) {
        printf("Error allocating memory for floors.\n");
        exit(1);
    }

    for (int i = 0; i < b->height; i++) {
        printf("Allocating memory for floor %d\n", i);
        floor* f = (floor*)malloc(sizeof(floor));
        if (!f) {
            printf("Error allocating memory for floor.\n");
            exit(1);
        }
        f->floorNumber = i;

        // Определяем тип этажа
        switch (b->building_type) {
        case RESIDENTIAL:
            f->floor_type = RESIDENTIAL;
            f->floor_type_data = (residentialFloor*)malloc(sizeof(residentialFloor));
            if (!f->floor_type_data) {
                printf("Error allocating memory for residential floor data.\n");
                free(f);
                exit(1);
            }
            ((residentialFloor*)f->floor_type_data)->room_count = 4;
            ((residentialFloor*)f->floor_type_data)->rooms = (room**)malloc(4 * sizeof(room*));
            if (!((residentialFloor*)f->floor_type_data)->rooms) {
                printf("Error allocating memory for rooms.\n");
                free(f->floor_type_data);
                free(f);
                exit(1);
            }
            for (int j = 0; j < 4; j++) {
                room* r = (room*)malloc(sizeof(room));
                if (!r) {
                    printf("Error allocating memory for room.\n");
                    for (int k = 0; k < j; k++) {
                        free(((residentialFloor*)f->floor_type_data)->rooms[k]);
                    }
                    free(((residentialFloor*)f->floor_type_data)->rooms);
                    free(f->floor_type_data);
                    free(f);
                    exit(1);
                }
                r->npcs = (npc**)malloc(4 * sizeof(npc*));
                if (!r->npcs) {
                    printf("Error allocating memory for NPCs.\n");
                    free(r);
                    for (int k = 0; k < j; k++) {
                        free(((residentialFloor*)f->floor_type_data)->rooms[k]);
                    }
                    free(((residentialFloor*)f->floor_type_data)->rooms);
                    free(f->floor_type_data);
                    free(f);
                    exit(1);
                }
                r->npc_count = 0;
                r->parentFloor = f;
                r->room_number = j;
                ((residentialFloor*)f->floor_type_data)->rooms[j] = r;
            }
            break;

        case OFFICE:
            f->floor_type = OFFICE;
            f->floor_type_data = (officeFloor*)malloc(sizeof(officeFloor));
            if (!f->floor_type_data) {
                printf("Error allocating memory for office floor data.\n");
                free(f);
                exit(1);
            }
            officeFloor* of = (officeFloor*)f->floor_type_data;
            of->office_count = 3;
            of->offices = (office**)malloc(of->office_count * sizeof(office*));

            if (!of->offices) {
                printf("Error allocating memory for offices.\n");
                free(of);
                exit(1);
            }

            for (int i = 0; i < of->office_count; i++) {
                of->offices[i] = (office*)malloc(sizeof(office));
                if (!of->offices[i]) {
                    printf("Error allocating memory for office.\n");
                    exit(1);
                }
            }
            break;
        default:
            printf("Unknown building type.\n");
            free(f);
            exit(1);
        }
        b->floors[i] = f;
    }
}

npc* generate_npc() {
    npc* new_npc = (npc*)malloc(sizeof(npc));
    if (!new_npc) {
        printf("Error allocating memory for NPC.\n");
        exit(1);
    }
    snprintf(new_npc->firstName, sizeof(new_npc->firstName), "%s", first_names[rand() % ARRAY_SIZE]);
    snprintf(new_npc->lastName, sizeof(new_npc->lastName), "%s", last_names[rand() % ARRAY_SIZE]);
    return new_npc;
}

void player_building_spawn(city* c, player* p){
    for (int x = p->x; x < c->height; ++x) {
        for (int y = (x == p->x ? p->y : 0); y < c->width; ++y) {
            if (c->cityMap[x][y]->building_type == RESIDENTIAL) {
                p->x = x;
                p->y = y;
                p->currentBuilding = c->cityMap[x][y];
                return; // Остановка поиска
            }
        }
    }

    // Если не нашли здание, начинаем заново с (0, 0)
    for (int x = 0; x < c->height; ++x) {
        for (int y = 0; y < c->width; ++y) {
            if (c->cityMap[x][y]->building_type == RESIDENTIAL) {
                p->x = x;
                p->y = y;
                p->currentBuilding = c->cityMap[x][y];
                return;
            }
        }
    }
}

void getNPCresidence(city* c, npc* n){
    int countC = rand() % c->residentialBuildings;
    int countB = countC;
    int floorC = rand() % c->residentialBuildingsList[countC]->height;
    int floorB = floorC;
    int roomC = rand() % 4;
    int roomB = roomC;
    while (((residentialFloor*)c->residentialBuildingsList[countC]->floors[floorC]->floor_type_data)->rooms[roomC]->npcs[0]){
        if (roomC < 3){
            roomC++;
        } else {
            roomC = 0;
            if (floorC < c->residentialBuildingsList[countC]->height){
                floorC++;
            } else {
                floorC = 0;
                if (countC < c->residentialBuildings){
                    countC++;
                } else {
                    countC = 0;
                }
            }
        }
        if (countC == countB && floorC == floorB && roomC == roomB){
            return;
        }
    n->placeOfResidence = ((residentialFloor*)c->residentialBuildingsList[countC]->floors[floorC]->floor_type_data)->rooms[roomC];
    ((residentialFloor*)c->residentialBuildingsList[countC]->floors[floorC]->floor_type_data)->rooms[roomC]->npcs[0] = n;
    }
}

void start(city* c, player* p) {
    printf("Enter city name: ");
    scanf("%99s", c->name);
    clear();
    printf("Enter city width: ");
    scanf("%d", &c->width);
    clear();
    printf("Enter city height: ");
    scanf("%d", &c->height);
    clear();
    printf("Generating...\n");

    c->cityMap = (building***)malloc(c->height * sizeof(building**));
    if (!c->cityMap) {
        printf("Error allocating memory for city map.\n");
        exit(1);
    }

    for (int i = 0; i < c->height; i++) {
        c->cityMap[i] = (building**)malloc(c->width * sizeof(building*));
        if (!c->cityMap[i]) {
            printf("Error allocating memory for city map row.\n");
            exit(1);
        }

        for (int j = 0; j < c->width; j++) {
            building* b = (building*)malloc(sizeof(building));
            if (!b) {
                printf("Error allocating memory for building.\n");
                exit(1);
            }

            snprintf(b->name, sizeof(b->name), "%s", generate_street_name());
            b->x = i;
            b->y = j;
            b->height = rand() % 5 + 1; // Высота от 1 до 5 этажей
            switch (rand()%10)
            {
            case 0:
                b->building_type = OFFICE;
                break;

            default:
                b->building_type = RESIDENTIAL;
                break;
            }

            allocateFloors(b);
            c->cityMap[i][j] = b;
        }
    }

    c->residentialBuildings = 0;
    c->officeBuildings = 0;
    for (int i = 0; i < c->height; i++) {
        for (int j = 0; j < c->width; j++) {
            if (c->cityMap[i][j]->building_type == RESIDENTIAL) {
                c->residentialBuildings++;
            } else {
                c->officeBuildings++;
            }
        }
    }

    c->residentialBuildingsList = (building**)malloc(c->residentialBuildings * sizeof(building*));
    if (!c->residentialBuildingsList) {
        printf("Error allocating memory for residential buildings.\n");
        exit(1);
    }
    c->officeBuildingsList = (building**)malloc(c->officeBuildings * sizeof(building*));
    if (!c->officeBuildingsList) {
        printf("Error allocating memory for office buildings.\n");
        exit(1);
    }

    int countR = 0;
    int countO = 0;
    for (int i = 0; i < c->height; i++) {
        for (int j = 0; j < c->width; j++) {
            if (c->cityMap[i][j]->building_type == RESIDENTIAL) {
                c->residentialBuildingsList[countR] = c->cityMap[i][j];
                countR++;
            } else {
                c->officeBuildingsList[countO] = c->cityMap[i][j];
                countO++;
            }
        }
    }

    for (int i = 0; i < c->height; i++) {
        for (int j = 0; j < c->width; j++) {
            building* b = c->cityMap[i][j];
            for (int k = 0; k < b->height; k++) {
                if (b->floors[k]->floor_type == OFFICE){
                    for (int l = 0; l < ((officeFloor*)b->floors[k]->floor_type_data)->office_count; l++){
                        office* o = ((officeFloor*)b->floors[k]->floor_type_data)->offices[l];
                        snprintf(o->name, sizeof(o->name), "%s", generateCompanyName());
                        o->employee_count = rand() % 10 + 1; // От 1 до 10 сотрудников
                        o->employees = (npc**)malloc(o->employee_count * sizeof(npc*));
                        if (!o->employees) {
                            printf("Error allocating memory for employees.\n");
                            free(o);
                            exit(1);
                        }
                    } 
                }
            }
        }
    }
    
    for (int i = 0; i < c->officeBuildings; i++){
        for (int j = 0; j < c->officeBuildingsList[i]->height; j++){
            for (int k = 0; k < ((officeFloor*)c->officeBuildingsList[i]->floors[j]->floor_type_data)->office_count; k++){
                for (int l = 0; l < ((officeFloor*)c->officeBuildingsList[i]->floors[j]->floor_type_data)->offices[k]->employee_count; l++){
                    ((officeFloor*)c->officeBuildingsList[i]->floors[j]->floor_type_data)->offices[k]->employees[l] = generate_npc();
                    getNPCresidence(c, ((officeFloor*)c->officeBuildingsList[i]->floors[j]->floor_type_data)->offices[k]->employees[l]);
                }
            }
        }
    }

    for (int i = 0; i < c->residentialBuildings; i++){
        for (int j = 0; j < c->residentialBuildingsList[i]->height; j++){
            for (int k = 0; k < ((residentialFloor*)c->residentialBuildingsList[i]->floors[j]->floor_type_data)->room_count; k++){
                if (!((residentialFloor*)c->residentialBuildingsList[i]->floors[j]->floor_type_data)->rooms[k]->npcs[0]){
                    ((residentialFloor*)c->residentialBuildingsList[i]->floors[j]->floor_type_data)->rooms[k]->npcs[0] = generate_npc();
                    ((residentialFloor*)c->residentialBuildingsList[i]->floors[j]->floor_type_data)->rooms[k]->npcs[0]->placeOfResidence = ((residentialFloor*)c->residentialBuildingsList[i]->floors[j]->floor_type_data)->rooms[k];
                    ((residentialFloor*)c->residentialBuildingsList[i]->floors[j]->floor_type_data)->rooms[k]->npcs[0]->currentPlace = ((residentialFloor*)c->residentialBuildingsList[i]->floors[j]->floor_type_data)->rooms[k];

                }
            }
        }
    }

    p->x = rand() % c->height;
    p->y = rand() % c->width;
    player_building_spawn(c, p);
    p->currentBuilding = c->cityMap[p->x][p->y];
    p->currentFloor = p->currentBuilding->floors[rand() % p->currentBuilding->height];
    p->currentRoom = ((residentialFloor*)p->currentFloor->floor_type_data)->rooms[rand() % 4];


    printf("City generated successfully!\n\n");

}

void printMap(city* c, player* p) {
    printf("\n\033[36m%s City Map\033[0m\n", c->name); // Cyan city name
    printf("╔");
    for(int i = 0; i < c->width; i++) {
        printf("═══");
        if (i < c->width - 1) {
            printf("╦");
        }
    }
    printf("╗\n");
    for (int i = 0; i < c->height; i++) {
        for (int j = 0; j < c->width; j++) {
            printf("║ "); // Vertical separator
            if (p->x == i && p->y == j) {
                printf("\033[1;31m☺\033[0m"); // Bold red player
            } else if (c->cityMap[i][j]) {
                switch (c->cityMap[i][j]->building_type) {
                    case RESIDENTIAL: 
                        printf("\033[32m⌂\033[0m"); // Green house
                        break;
                    case OFFICE: 
                        printf("\033[34mF\033[0m"); // Blue office
                        break;
                    default: 
                        printf("?");
                        break;
                }
            } else {
                printf("·"); // Middle dot for empty
            }
            printf(" ");
        }
        printf("║\n");
        if (i < c->height - 1) {
            printf("╠");
            for (int j = 0; j < c->width; j++) {
                printf("═══");
                if (j < c->width - 1) {
                    printf("╬");
                }
            }
            printf("╣\n");
        }
    }
    printf("╚");
    for (int i = 0; i < c->width; i++) {
        printf("═══");
        if (i < c->width - 1) {
            printf("╩");
        }
    }
    printf("╝\n");
    printf("\n\033[33mLegend:\033[0m ☺=You | ⌂=Home | F=Office | ·=Empty\n\n");
}

void playerControl(city* c, player* p) {
    int choice;
    
    if (p->currentBuilding) {
        printf("\n\033[35m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m\n");
        printf("📍 \033[1m%s\033[0m | Floor: %d\n", p->currentBuilding->name, p->currentFloor->floorNumber + 1);
        printf("\033[35m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m\n");
        
        switch (p->currentFloor->floor_type) {
            case RESIDENTIAL:
                if (p->currentRoom) {
                    if (p->currentRoom->npcs[0]) {
                        printf("\n👤 \033[1m%s %s's Room\033[0m\n", p->currentRoom->npcs[0]->firstName, p->currentRoom->npcs[0]->lastName);
                        printf("1. Talk to %s\n", p->currentRoom->npcs[0]->firstName);
                        printf("2. Search the room\n");
                        printf("3. Leave\n");
                        printf("» Choice: ");
                        scanf("%d", &choice);
                        clear();
                        switch (choice) {
                            case 1:
                                printf("\n💬 %s says: 'I've lived here since the Great Pixel War!'\n", p->currentRoom->npcs[0]->firstName);
                                break;
                            case 2:
                                printf("\n🔍 You find dusty code snippets and a half-eaten pizza.\n");
                                break;
                            case 3:
                                p->currentRoom = NULL;
                                break;
                            default:
                                printf("Invalid choice.\n");
                        }
                    } else {
                        printf("\n🚪 Empty Room\n1. Leave\n» Choice: ");
                        scanf("%d", &choice);
                        clear();
                        if (choice == 1) p->currentRoom = NULL;
                    }
                } else {
                    printf("\n🏠 Floor Menu:\n");
                    printf("1. Enter a room (1-4)\n");
                    printf("2. Exit building\n");
                    printf("3. Switch floor\n");
                    printf("» Choice: ");
                    scanf("%d", &choice);
                    clear();

                    switch (choice) {
                        case 1:
                            printf("Enter room number: ");
                            scanf("%d", &choice);
                            clear();
                            if (choice >= 1 && choice <= 4) {
                                residentialFloor* resFloor = (residentialFloor*)p->currentFloor->floor_type_data;
                                if (resFloor) {
                                    p->currentRoom = resFloor->rooms[choice - 1];
                                } else {
                                    printf("Invalid floor data.\n\n");
                                }
                            } else {
                                printf("Invalid room number.\n\n");
                            }
                            break;
                        case 2:
                            p->currentFloor = NULL;
                            p->currentBuilding = NULL;
                            break;
                        case 3:
                            printf("Choose a floor (1-%d):\n", p->currentBuilding->height);
                            for (int i = 0; i < p->currentBuilding->height; i++) {
                                printf("%d. Floor %d\n", i + 1, i + 1);
                            }
                            printf("Your choice: ");
                            scanf("%d", &choice);
                            clear();
                            if (choice >= 1 && choice <= p->currentBuilding->height) {
                                p->currentFloor = p->currentBuilding->floors[choice - 1];
                            } else {
                                printf("Invalid floor number.\n\n");
                            }
                            break;
                        default:
                            printf("Invalid choice.\n\n");
                            break;
                    }
                }
                break;

            case OFFICE:
                printf("\n🏢 Office Floor\n");
                printf("1. Exit building\n");
                printf("2. List companies\n");
                printf("3. Switch floor\n");
                printf("» Choice: ");
                scanf("%d", &choice);
                 clear();
                switch (choice) {
                    case 1:
                        p->currentFloor = NULL;
                        p->currentBuilding = NULL;
                        break;
                    case 2:
                        officeFloor* officeFlr = (officeFloor*)p->currentFloor->floor_type_data;
                        if (officeFlr) {
                            printf("Choose an office:\n");
                            for (int i = 0; i < officeFlr->office_count; i++) {
                                printf("%d. %s\n", i + 1, officeFlr->offices[i]->name);
                            }
                            printf("Your choice: ");
                            scanf("%d", &choice);
                            if (choice >= 1 && choice <= officeFlr->office_count) {
                                office* o = officeFlr->offices[choice - 1];
                                printf("Employees of %s:\n", o->name);
                                for (int i = 0; i < o->employee_count; i++) {
                                    printf("%d. %s %s\n", i + 1, o->employees[i]->firstName, o->employees[i]->lastName);
                                }
                                printf("Choose an employee:\n");
                                printf("Your choice: ");
                                scanf("%d", &choice);
                                if (choice >= 1 && choice <= o->employee_count) {
                                    npc* n = o->employees[choice - 1];
                                    printf("You are talking to %s %s.\n", n->firstName, n->lastName);
                                    printf("1. Talk to %s %s\n", n->firstName, n->lastName);
                                    printf("2. Leave the office\n");
                                    printf("Your choice: ");
                                    scanf("%d", &choice);
                                    if (choice == 1) {
                                        printf("%s %s says: 'Hello! Welcome to my office.'\n", n->firstName, n->lastName);
                                    }
                                } else {
                                    printf("Invalid employee number.\n");
                                }
                            } else {
                                printf("Invalid office number.\n");
                            }
                        }
                        break;
                    case 3:
                        printf("Choose a floor (0-%d):\n", p->currentBuilding->height - 1);
                        for (int i = 0; i < p->currentBuilding->height; i++) {
                            printf("%d. Floor %d\n", i, i);
                        }
                        printf("Your choice: ");
                        scanf("%d", &choice);
                        if (choice >= 0 && choice < p->currentBuilding->height) {
                            p->currentFloor = p->currentBuilding->floors[choice];
                        } else {
                            printf("Invalid floor number.\n");
                        }
                        break;
                    default:
                        printf("Invalid choice.\n");
                        break;
                }
                break;
        }
    } else {
        printf("\n\033[35m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m\n");
        printf("🌆 You're at \033[1m%s\033[0m\n", c->cityMap[p->x][p->y]->name);
        printf("\033[35m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m\n");
        printf("1. Enter building\n");
        printf("2. Move\n");
        printf("3. View map\n");
        printf("» Choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                if (c->cityMap[p->x][p->y]) {
                    p->currentBuilding = c->cityMap[p->x][p->y];
                    p->currentFloor = p->currentBuilding->floors[rand() % p->currentBuilding->height];
                } else {
                    printf("There is no building here.\n");
                }
                break;
            case 2:
                printf("1. North 🡹\n2. South 🡻\n3. West 🡸\n4. East 🡺\n» ");
                scanf("%d", &choice);
                switch (choice) {
                    case 1:
                        if (p->x > 0) {
                            p->x--;
                        } else {
                            printf("You are at the top of the city.\n");
                        }
                        break;
                    case 2:
                        if (p->x < c->height - 1) {
                            p->x++;
                        } else {
                            printf("You are at the bottom of the city.\n");
                        }
                        break;
                    case 3: 
                        if (p->y > 0) {
                            p->y--;
                        } else {
                            printf("You are at the left edge of the city.\n");
                        }
                        break;
                    case 4:
                        if (p->y < c->width - 1) {
                            p->y++;
                        } else {
                            printf("You are at the right edge of the city.\n");
                        }
                        break;
                    }
                break;
            case 3:
                printMap(c, p);
                break;
        }
    }
}

void freeCity(city* c) {
    for (int i = 0; i < c->height; i++) {
        for (int j = 0; j < c->width; j++) {
            building* b = c->cityMap[i][j];
            for (int k = 0; k < b->height; k++) {
                for (int l = 0; l < 4; l++) {
                    room* r = ((residentialFloor*)b->floors[k]->floor_type_data)->rooms[l];
                    if (r->npcs[0]) {
                        free(r->npcs[0]);
                    }
                }
                free(b->floors[k]);
            }
            free(b->floors);
            free(b);
        }
        free(c->cityMap[i]);
    }
    free(c->cityMap);
}

int main(){
    clear();
    //srand(time(NULL));
    srand(THE_ANSWER_TO_LIFE_THE_UNIVERSE_AND_EVERYTHING);
    city c;
    player p;
    start(&c, &p);
    while (1) {
        playerControl(&c, &p);
    }
    freeCity(&c);
    return 0;
}