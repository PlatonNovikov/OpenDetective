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
#define MAX_RELATIONSHIPS 100
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

void allocateFloors(building* b) {
    printf("Allocating memory for floors...\n");
    b->floors = (floor**)malloc(b->height * sizeof(floor*));
    if (!b->floors) {
        printf("Error allocating memory for floors.\n");
        exit(1);
    }

    for (int i = 0; i < b->height; i++) {
        floor* f = (floor*)malloc(sizeof(floor));
        if (!f) {
            printf("Error allocating memory for floor.\n");
            exit(1);
        }
        f->floorNumber = i;
        f->parentBuilding = b;

        printf("Allocating memory for floor type data...\n");
        
        switch (b->building_type) {
        case RESIDENTIAL:
            f->floor_type = RESIDENTIAL;
            f->floor_type_data = (residentialFloor*)malloc(sizeof(residentialFloor));
            printf("Allocating memory for residential floor data...\n");
            if (!f->floor_type_data) {
                printf("Error allocating memory for residential floor data.\n");
                free(f);
                exit(1);
            }
            ((residentialFloor*)f->floor_type_data)->room_count = 4;
            ((residentialFloor*)f->floor_type_data)->rooms = (room**)malloc(4 * sizeof(room*));
            printf("Allocating memory for rooms...\n");
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
                for(int k = 0; k < 4; k++){
                    r->npcs[k] = NULL;
                }
                r->parentFloor = f;
                r->room_number = j;
                ((residentialFloor*)f->floor_type_data)->rooms[j] = r;
            }
            break;

        case OFFICE:
            printf("Allocating memory for office floor data...\n");
            f->floor_type = OFFICE;
            f->floor_type_data = (officeFloor*)malloc(sizeof(officeFloor));
            if (!f->floor_type_data) {
                printf("Error allocating memory for office floor data.\n");
                free(f);
                exit(1);
            }
            officeFloor* of = (officeFloor*)f->floor_type_data;
            of->office_count = 3;
            of->parentFloor = f;
            of->offices = (office**)malloc(of->office_count * sizeof(office*));
            if (!of->offices) {
                printf("Error allocating memory for offices.\n");
                free(of);
                exit(1);
            }

            for (int j = 0; j < of->office_count; j++) {
                printf("Allocating memory for office...\n");
                of->offices[j] = (office*)malloc(sizeof(office));
                of->offices[j]->parentFloor = f;
                if (!of->offices[j]) {
                    printf("Error allocating memory for office.\n");
                    exit(1);
                }
                of->offices[j]->employee_count = 0;
                of->offices[j]->employees = (npc**)malloc(5 * sizeof(npc*));
                if (!of->offices[j]->employees) {
                    printf("Error allocating memory for employees.\n");
                    free(of->offices[j]);
                    exit(1);
                }
                of->offices[j]->office_number = j;
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

void generate_npc(npc* new_npc) {
    snprintf(new_npc->firstName, sizeof(new_npc->firstName), "%s", first_names[rand() % ARRAY_SIZE]);
    snprintf(new_npc->lastName, sizeof(new_npc->lastName), "%s", last_names[rand() % ARRAY_SIZE]);
    new_npc->relationships = (relationship*)malloc(MAX_RELATIONSHIPS * sizeof(relationship));
    if (!new_npc->relationships) {
        printf("Error allocating memory for relationships.\n");
        free(new_npc);
        exit(1);
    }
    new_npc->relationshipCount = 0;
}

void generate_family(int count, npc** family) {
    if (!family) {
        printf("Error allocating memory for family.\n");
        exit(1);
    }
    for (int i = 0; i < count; i++){
        family[i] = (npc*)malloc(sizeof(npc));
        if (!family[i]) {
            printf("Error allocating memory for NPC.\n");
            exit(1);
        }
        generate_npc(family[i]);
        strcpy(family[i]->lastName, family[0]->lastName);
    }
}

room* getFreeResidence(city* c){
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
            if (floorC < c->residentialBuildingsList[countC]->height - 1){
                floorC++;
            } else {
                floorC = 0;
                if (countC < c->residentialBuildings - 1){
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
    return ((residentialFloor*)c->residentialBuildingsList[countC]->floors[floorC]->floor_type_data)->rooms[roomC];
}

office* getFreeWorkplace(city* c){
    int countC = rand() % c->officeBuildings;
    int countB = countC;
    int floorC = rand() % c->officeBuildingsList[countC]->height;
    int floorB = floorC;
    int officeC = rand() % ((officeFloor*)c->officeBuildingsList[countC]->floors[floorC]->floor_type_data)->office_count;
    int officeB = officeC;
    while (((officeFloor*)c->officeBuildingsList[countC]->floors[floorC]->floor_type_data)->offices[officeC]->employee_count == 5){
        if (officeC < ((officeFloor*)c->officeBuildingsList[countC]->floors[floorC]->floor_type_data)->office_count - 1){
            officeC++;
        } else {
            officeC = 0;
            if (floorC < c->officeBuildingsList[countC]->height - 1){
                floorC++;
            } else {
                floorC = 0;
                if (countC < c->officeBuildings - 1){
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
    return ((officeFloor*)c->officeBuildingsList[countC]->floors[floorC]->floor_type_data)->offices[officeC];
}

void populateCity(city* c){
    for (int i = 0; i < c->residentialBuildings; i++){
        for (int j = 0; j < c->residentialBuildingsList[i]->height; j++){
            for (int k = 0; k < ((residentialFloor*)c->residentialBuildingsList[i]->floors[j]->floor_type_data)->room_count; k++){
                room* r = ((residentialFloor*)c->residentialBuildingsList[i]->floors[j]->floor_type_data)->rooms[k];
                if(rand()%4){
                    npc* new_npc = (npc*)malloc(sizeof(npc));
                    if (!new_npc) {
                        printf("Error allocating memory for NPC.\n");
                        exit(1);
                    }
                    generate_npc(new_npc);
                    new_npc->placeOfResidence = getFreeResidence(c);
                    new_npc->placeOfResidence->npcs[0] = new_npc;
                    new_npc->placeOfResidence->npc_count = 1;
                    new_npc->currentPlace = new_npc->placeOfResidence;
                    new_npc->placeOfWork = getFreeWorkplace(c);
                    if (new_npc->placeOfWork){
                        new_npc->placeOfWork->employees[new_npc->placeOfWork->employee_count] = new_npc;
                        new_npc->placeOfWork->employee_count++;
                    }
                }
                else{
                    npc** family = (npc**)malloc(4 * sizeof(npc*));
                    int count = rand() % 3 + 2;
                    if (!family) {
                        printf("Error allocating memory for family.\n");
                        exit(1);
                    }
                    generate_family(count, family);
                    
                    family[0]->placeOfResidence = getFreeResidence(c);
                    family[0]->placeOfResidence->npcs = family;
                    family[0]->placeOfResidence->npc_count = count;
                    for (int l = 0; l < count; l++){
                        family[l]->currentPlace = family[0]->placeOfResidence;
                        family[l]->placeOfResidence = family[0]->placeOfResidence;
                        family[l]->placeOfWork = getFreeWorkplace(c);
                        if (family[l]->placeOfWork){
                            family[l]->placeOfWork->employees[family[l]->placeOfWork->employee_count] = family[l];
                            family[l]->placeOfWork->employee_count++;
                        }
                    }

                }
            }
        }
    }
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
            b->height = rand() % 7 + 3; // Высота от 3 до 10 этажей
            b->parentCity = c;
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
                    } 
                }
            }
        }
    }
    
    populateCity(c);

    p->x = rand() % c->height;
    p->y = rand() % c->width;
    player_building_spawn(c, p);
    p->currentBuilding = c->cityMap[p->x][p->y];
    p->currentFloor = p->currentBuilding->floors[rand() % p->currentBuilding->height];
    p->currentRoom = ((residentialFloor*)p->currentFloor->floor_type_data)->rooms[rand() % 4];

    printf("City generated successfully!\n\n");

}

void makeSavefile(city* c, player* p) {
    FILE* savefile = fopen("savefile.txt", "w");
    if (!savefile) {
        printf("Error opening savefile.\n");
        exit(1);
    }

    // Сохраняем данные города
    fprintf(savefile, "CITYDATA\n%s\n%d %d\n%d %d\n%d %d\n",
        c->name, c->width, c->height, c->residentialBuildings, c->officeBuildings, c->time, c->day);

    // Сохраняем данные игрока
    fprintf(savefile, "PLAYERDATA\n%d %d\n%d %d\n%d\n%d\n",
        p->x, p->y, 
        p->currentBuilding ? p->currentBuilding->x : -1, p->currentBuilding ? p->currentBuilding->y : -1,
        p->currentFloor ? p->currentFloor->floorNumber : -1,
        p->currentRoom ? p->currentRoom->room_number : -1);

    // Проходим по всем зданиям, этажам и комнатам за один проход
    fprintf(savefile, "BUILDINGDATA\n");
    for (int i = 0; i < c->height; i++) {
        for (int j = 0; j < c->width; j++) {
            building* b = c->cityMap[i][j];
            fprintf(savefile, "%s\n%d %d %d %d\n", b->name, b->x, b->y, b->height, b->building_type);

            // Сохранение этажей
            for (int k = 0; k < b->height; k++) {
                floor* f = b->floors[k];
                fprintf(savefile, "FLOOR %d %d %d %d\n", b->x, b->y, f->floorNumber, f->floor_type);

                if (f->floor_type == RESIDENTIAL) {
                    residentialFloor* rf = (residentialFloor*)f->floor_type_data;
                    fprintf(savefile, "ROOMS %d\n", rf->room_count);
                    
                    for (int l = 0; l < rf->room_count; l++) {
                        room* r = rf->rooms[l];
                        fprintf(savefile, "ROOM %d %d %d %d\n", b->x, b->y, f->floorNumber, r->room_number);
                        fprintf(savefile, "NPCS %d\n", r->npc_count);

                        // Сохранение NPC
                        for (int m = 0; m < r->npc_count; m++) {
                            npc* n = r->npcs[m];
                            fprintf(savefile, "NPC %s %s\n", n->firstName, n->lastName);
                            fprintf(savefile, "RESIDENCE %d %d %d %d\n",
                                n->placeOfResidence->parentFloor->parentBuilding->x,
                                n->placeOfResidence->parentFloor->parentBuilding->y,
                                n->placeOfResidence->parentFloor->floorNumber,
                                n->placeOfResidence->room_number);

                            if (n->placeOfWork) {
                                fprintf(savefile, "WORK %d %d %d %d\n",
                                    n->placeOfWork->parentFloor->parentBuilding->x,
                                    n->placeOfWork->parentFloor->parentBuilding->y,
                                    n->placeOfWork->parentFloor->floorNumber,
                                    n->placeOfWork->office_number);
                            }
                        }
                    }
                } else if (f->floor_type == OFFICE) {
                    officeFloor* of = (officeFloor*)f->floor_type_data;
                    fprintf(savefile, "OFFICES %d\n", of->office_count);

                    for (int l = 0; l < of->office_count; l++) {
                        office* o = of->offices[l];
                        fprintf(savefile, "OFFICE %d %d %d %s %d\n",
                            b->x, b->y, f->floorNumber, o->name, o->employee_count);
                    }
                }
            }
        }
    }

    fprintf(savefile, "END\n"); // Маркер конца файла
    fclose(savefile);
}

void loadSavefile(city* c, player* p) {
    FILE* savefile = fopen("savefile.txt", "r");
    if (!savefile) {
        printf("Error opening savefile.\n");
        exit(1);
    }

    char buffer[256];
    int currentBuildingX, currentBuildingY, currentFloorNum, currentRoomNum;

    // Читаем CITYDATA
    fscanf(savefile, "%s", buffer);
    if (strcmp(buffer, "CITYDATA") != 0) {
        printf("Invalid save file format.\n");
        fclose(savefile);
        exit(1);
    }
    fscanf(savefile, "%s", c->name);
    fscanf(savefile, "%d %d", &c->width, &c->height);
    fscanf(savefile, "%d %d", &c->residentialBuildings, &c->officeBuildings);
    fscanf(savefile, "%d %d", &c->time, &c->day);

    // Инициализация cityMap
    c->cityMap = (building***)malloc(c->height * sizeof(building**));
    for (int i = 0; i < c->height; i++) {
        c->cityMap[i] = (building**)malloc(c->width * sizeof(building*));
    }

    // Читаем PLAYERDATA
    fscanf(savefile, "%s", buffer);
    if (strcmp(buffer, "PLAYERDATA") != 0) {
        printf("Invalid save file format.\n");
        fclose(savefile);
        exit(1);
    }
    fscanf(savefile, "%d %d", &p->x, &p->y);
    fscanf(savefile, "%d %d", &currentBuildingX, &currentBuildingY);
    fscanf(savefile, "%d", &currentFloorNum);
    fscanf(savefile, "%d", &currentRoomNum);

    // Пока игнорируем восстановление currentBuilding, currentFloor, currentRoom
    p->currentBuilding = NULL;
    p->currentFloor = NULL;
    p->currentRoom = NULL;

    // Читаем BUILDINGDATA
    fscanf(savefile, "%s", buffer);
    if (strcmp(buffer, "BUILDINGDATA") != 0) {
        printf("Invalid save file format. Expected BUILDINGDATA.\n");
        fclose(savefile);
        exit(1);
    }

    // Загрузка зданий, этажей и комнат
    for (int i = 0; i < c->height; i++) {
        for (int j = 0; j < c->width; j++) {
            building* b = (building*)malloc(sizeof(building));
            fscanf(savefile, "%s", b->name);
            fscanf(savefile, "%d %d %d %d", &b->x, &b->y, &b->height, &b->building_type);
            b->floors = (floor**)malloc(b->height * sizeof(floor*));

            for (int k = 0; k < b->height; k++) {
                fscanf(savefile, "%s", buffer);
                if (strcmp(buffer, "FLOOR") != 0) {
                    printf("Unexpected token: %s, expected FLOOR\n", buffer);
                    fclose(savefile);
                    exit(1);
                }
                floor* f = (floor*)malloc(sizeof(floor));
                fscanf(savefile, "%d %d %d %d", &b->x, &b->y, &f->floorNumber, &f->floor_type);

                if (f->floor_type == RESIDENTIAL) {
                    residentialFloor* rf = (residentialFloor*)malloc(sizeof(residentialFloor));
                    fscanf(savefile, "%s %d", buffer, &rf->room_count);
                    rf->rooms = (room**)malloc(rf->room_count * sizeof(room*));

                    for (int l = 0; l < rf->room_count; l++) {
                        room* r = (room*)malloc(sizeof(room));
                        fscanf(savefile, "%s %d %d %d %d", buffer, &b->x, &b->y, &f->floorNumber, &r->room_number);
                        fscanf(savefile, "%s %d", buffer, &r->npc_count);
                        r->npcs = (npc**)malloc(r->npc_count * sizeof(npc*));

                        for (int m = 0; m < r->npc_count; m++) {
                            npc* n = (npc*)malloc(sizeof(npc));
                            fscanf(savefile, "%s %s", buffer, n->firstName);
                            fscanf(savefile, "%s", buffer);
                            fscanf(savefile, "%s %d %d %d %d", buffer,
                                   &n->placeOfResidence->parentFloor->parentBuilding->x,
                                   &n->placeOfResidence->parentFloor->parentBuilding->y,
                                   &n->placeOfResidence->parentFloor->floorNumber,
                                   &n->placeOfResidence->room_number);

                            if (fscanf(savefile, "%s", buffer) == 1 && strcmp(buffer, "WORK") == 0) {
                                fscanf(savefile, "%d %d %d %d",
                                       &n->placeOfWork->parentFloor->parentBuilding->x,
                                       &n->placeOfWork->parentFloor->parentBuilding->y,
                                       &n->placeOfWork->parentFloor->floorNumber,
                                       &n->placeOfWork->office_number);
                            }
                            r->npcs[m] = n;
                        }
                        rf->rooms[l] = r;
                    }
                    f->floor_type_data = rf;
                } else if (f->floor_type == OFFICE) {
                    officeFloor* of = (officeFloor*)malloc(sizeof(officeFloor));
                    fscanf(savefile, "%s %d", buffer, &of->office_count);
                    of->offices = (office**)malloc(of->office_count * sizeof(office*));

                    for (int l = 0; l < of->office_count; l++) {
                        office* o = (office*)malloc(sizeof(office));
                        fscanf(savefile, "%s %d %d %d %s %d", buffer, &b->x, &b->y, &f->floorNumber, o->name, &o->employee_count);
                        of->offices[l] = o;
                    }
                    f->floor_type_data = of;
                }
                b->floors[k] = f;
            }
            c->cityMap[i][j] = b;
        }
    }

    fscanf(savefile, "%s", buffer);
    if (strcmp(buffer, "END") != 0) {
        printf("Savefile corrupted. Missing END marker.\n");
        fclose(savefile);
        exit(1);
    }

    fclose(savefile);
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
// Добавим вспомогательные функции для улучшения читаемости
void printSeparator() {
    printf("\n\033[35m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m\n");
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int safeInput(int min, int max) {
    int choice;
    while(1) {
        if(scanf("%d", &choice) == 1) {
            if(choice >= min && choice <= max) {
                clearInputBuffer();
                return choice;
            }
        }
        clearInputBuffer();
        printf("Invalid input. Please enter a number between %d-%d: ", min, max);
    }
}

void handleDialogue(player* p, npc* n) {
    printf("\n🗨️ \033[1m%s %s\033[0m\n", n->firstName, n->lastName);
    printf("1. Ask about work\n");
    printf("2. Ask about family\n");
    printf("3. Ask about hobbies\n");
    printf("4. Say goodbye\n» Choice: ");
    int choice = safeInput(1, 4);
    clear();
    switch(choice) {
        case 1:
            printf("%s %s says: 'I work at %s.'\n", n->firstName, n->lastName, n->placeOfWork->name);
            break;
        case 2:
            printf("%s %s says: 'I live at %s.'\n", n->firstName, n->lastName, n->placeOfResidence->parentFloor->parentBuilding->name);
            break;
        case 3:
            printf("%s %s says: 'I like to read books.'\n", n->firstName, n->lastName);
            break;
        case 4:
            printf("%s %s says: 'Goodbye!'\n", n->firstName, n->lastName);
            break;
    }
}

// Подфункции для разных состояний игры
void handleResidentialRoom(player* p) {
    room* r = p->currentRoom;

    if(r->npc_count > 1){
        printf("\n👥 \033[1m%s's Room\033[0m\n", r->npcs[0]->lastName);
        printf("1. Talk to %s's\n", r->npcs[0]->lastName);
    } else {
        printf("\n👤 \033[1m%s %s's Room\033[0m\n", r->npcs[0]->firstName, r->npcs[0]->lastName);
        printf("1. Talk to %s\n", r->npcs[0]->firstName);
    }

    printf("2. Search the room\n");
    printf("3. Leave\n» Choice: ");
    
    int choice = safeInput(1, 3);
    clear();
    
    switch(choice) {
        case 1:
            if (r->npc_count == 1) {
                handleDialogue(p, r->npcs[0]);
            } else {
                for (int i = 0; i < r->npc_count; i++) {
                    printf("%d. Talk to %s %s\n", i + 1, r->npcs[i]->firstName, r->npcs[i]->lastName);
                }
                printf("%d. Leave\n» Choice: ", r->npc_count + 1);
                int npcChoice = safeInput(1, r->npc_count + 1);
                clear();
                if (npcChoice == r->npc_count + 1) {
                    break;
                }
                handleDialogue(p, r->npcs[npcChoice - 1]);
            }
            break;
        case 2:
            printf("\n🔍 You find dusty code snippets and a half-eaten pizza.\n");
            break;
        case 3:
            p->currentRoom = NULL;
            break;
    }
} 

void handleEmptyRoom(player* p){
    printf("\n🚪 Empty Room\n");
    printf("1. Search the room\n");
    printf("2. Leave\n» Choice: ");
    int choice = safeInput(1, 2);
    clear();

    switch(choice) {
        case 1:
            printf("\n🔍 You find nothing but dust and a flickering light.\n");
            break;
        case 2:
            p->currentRoom = NULL;
            break;
    }
}

void handleResidentialFloor(player* p) {
    printf("\n🏠 Floor Menu:\n");
    printf("1. Enter a room (1-4)\n");
    printf("2. Exit building\n");
    printf("3. Switch floor\n» Choice: ");
    
    int choice = safeInput(1, 3);
    clear();
    
    switch(choice) {
        case 1: {
            printf("Enter room number: ");
            int roomChoice = safeInput(1, 4);
            residentialFloor* resFloor = (residentialFloor*)p->currentFloor->floor_type_data;
            
            if(resFloor) {
                p->currentRoom = resFloor->rooms[roomChoice - 1];
            } else {
                printf("Invalid floor data.\n");
            }
            break;
        }
        case 2:
            p->currentFloor = NULL;
            p->currentBuilding = NULL;
            break;
        case 3: {
            printf("Choose a floor (1-%d):\n", p->currentBuilding->height);
            for(int i = 0; i < p->currentBuilding->height; i++) {
                printf("%d. Floor %d\n", i + 1, i + 1);
            }
            int floorChoice = safeInput(1, p->currentBuilding->height);
            p->currentFloor = p->currentBuilding->floors[floorChoice - 1];
            break;
        }
    }
}

void handleOfficeFloor(player* p) {
    printf("\n🏢 Office Floor\n");
    printf("1. Exit building\n");
    printf("2. List companies\n");
    printf("3. Switch floor\n» Choice: ");
    
    int choice = safeInput(1, 3);
    clear();
    
    switch(choice) {
        case 1:
            p->currentFloor = NULL;
            p->currentBuilding = NULL;
            break;
        case 2: {
            officeFloor* officeFlr = (officeFloor*)p->currentFloor->floor_type_data;
            if(!officeFlr) break;

            printf("Choose an office:\n");
            for(int i = 0; i < officeFlr->office_count; i++) {
                printf("%d. %s\n", i + 1, officeFlr->offices[i]->name);
            }
            int officeChoice = safeInput(1, officeFlr->office_count);
            office* o = officeFlr->offices[officeChoice - 1];

            printf("Employees of %s:\n", o->name);
            for(int i = 0; i < o->employee_count; i++) {
                printf("%d. %s %s\n", i + 1, o->employees[i]->firstName, o->employees[i]->lastName);
            }
            int empChoice = safeInput(1, o->employee_count);
            npc* n = o->employees[empChoice - 1];

            printf("1. Talk to %s %s\n", n->firstName, n->lastName);
            printf("2. Leave\n» Choice: ");
            int action = safeInput(1, 2);
            
            if(action == 1) {
                printf("%s %s says: 'Hello! Welcome to my office.'\n", 
                      n->firstName, n->lastName);
            }
            break;
        }
        case 3: {
            printf("Choose a floor (1-%d):\n", p->currentBuilding->height);
            for(int i = 0; i < p->currentBuilding->height; i++) {
                printf("%d. Floor %d\n", i + 1, i + 1);
            }
            int floorChoice = safeInput(1, p->currentBuilding->height);
            p->currentFloor = p->currentBuilding->floors[floorChoice - 1];
            break;
        }
    }
}

void handleBuildingInteraction(city* c, player* p) {
    printSeparator();
    printf("📍 \033[1m%s\033[0m | Floor: %d\n", 
          p->currentBuilding->name, 
          p->currentFloor->floorNumber + 1);
    printSeparator();

    if(p->currentRoom) {
        printf("%d", p->currentRoom->npc_count);
        if (p->currentRoom->npc_count > 0) {
            handleResidentialRoom(p);
        } else {
            handleEmptyRoom(p);
        }
    } else {
        switch(p->currentFloor->floor_type) {
            case RESIDENTIAL:
                handleResidentialFloor(p);
                break;
            case OFFICE:
                handleOfficeFloor(p);
                break;
        }
    }
}

void handleMapMovement(city* c, player* p) {
    printf("1. North 🡹\n2. South 🡻\n3. West 🡸\n4. East 🡺\n» ");
    int dir = safeInput(1, 4);
    
    switch(dir) {
        case 1:
            if(p->x > 0) p->x--;
            else printf("You're at the city's northern edge!\n");
            break;
        case 2:
            if(p->x < c->height - 1) p->x++;
            else printf("You're at the city's southern edge!\n");
            break;
        case 3: 
            if(p->y > 0) p->y--;
            else printf("You're at the city's western edge!\n");
            break;
        case 4:
            if(p->y < c->width - 1) p->y++;
            else printf("You're at the city's eastern edge!\n");
            break;
    }
}

void handleOutsideInteraction(city* c, player* p) {
    printSeparator();
    printf("🌆 You're at \033[1m%s\033[0m\n", c->cityMap[p->x][p->y]->name);
    printSeparator();
    
    printf("1. Enter building\n");
    printf("2. Move\n");
    printf("3. View map\n»");
    printf("4. Save\n» Choice: ");
    
    int choice = safeInput(1, 4);
    clear();
    
    switch(choice) {
        case 1:
            if(c->cityMap[p->x][p->y]) {
                p->currentBuilding = c->cityMap[p->x][p->y];
                p->currentFloor = p->currentBuilding->floors[0]; // Start at ground floor
            } else {
                printf("There is no building here.\n");
            }
            break;
        case 2:
            handleMapMovement(c, p);
            break;
        case 3:
            printMap(c, p);
            break;
        case 4:
            makeSavefile(c, p);
            break;
    }
}

// Основная функция
void playerControl(city* c, player* p) {
    if(p->currentBuilding) {
        handleBuildingInteraction(c, p);
    } else {
        handleOutsideInteraction(c, p);
    }
}
void freeCity(city* c) {
    if (!c) return;

    for (int i = 0; i < c->height; i++) {
        for (int j = 0; j < c->width; j++) {
            building* b = c->cityMap[i][j];
            if (!b) continue;

            // Освобождаем этажи
            for (int k = 0; k < b->height; k++) {
                floor* f = b->floors[k];
                if (!f) continue;

                // Освобождаем данные этажа в зависимости от типа
                switch (f->floor_type) {
                    case RESIDENTIAL: {
                        residentialFloor* resFloor = (residentialFloor*)f->floor_type_data;
                        if (resFloor) {
                            for (int l = 0; l < resFloor->room_count; l++) {
                                room* r = resFloor->rooms[l];
                                if (r) {
                                    // Освобождаем NPC в комнате
                                    if (r->npcs[0]) {
                                        free(r->npcs[0]);
                                    }
                                    free(r->npcs); // Освобождаем массив NPC
                                    free(r);       // Освобождаем саму комнату
                                }
                            }
                            free(resFloor->rooms); // Освобождаем массив комнат
                            free(resFloor);        // Освобождаем данные жилого этажа
                        }
                        break;
                    }

                    case OFFICE: {
                        officeFloor* of = (officeFloor*)f->floor_type_data;
                        if (of) {
                            for (int l = 0; l < of->office_count; l++) {
                                office* o = of->offices[l];
                                if (o) {
                                    // Освобождаем сотрудников офиса
                                    for (int m = 0; m < o->employee_count; m++) {
                                        if (o->employees[m]) {
                                            free(o->employees[m]);
                                        }
                                    }
                                    free(o->employees); // Освобождаем массив сотрудников
                                    free(o);            // Освобождаем сам офис
                                }
                            }
                            free(of->offices); // Освобождаем массив офисов
                            free(of);         // Освобождаем данные офисного этажа
                        }
                        break;
                    }

                    default:
                        // Неизвестный тип этажа
                        break;
                }

                free(f); // Освобождаем сам этаж
            }

            free(b->floors); // Освобождаем массив этажей
            free(b);         // Освобождаем само здание
        }

        free(c->cityMap[i]); // Освобождаем строку карты
    }

    // Освобождаем списки зданий
    if (c->residentialBuildingsList) {
        free(c->residentialBuildingsList);
    }
    if (c->officeBuildingsList) {
        free(c->officeBuildingsList);
    }

    free(c->cityMap); // Освобождаем карту города
}

void openCMD(){
    #if defined(_WIN32) || defined(_WIN64)
        system("start cmd.exe /K OpenDetective.exe --child");
    #elif defined(__linux__) || defined(__unix__)
        if (system("which gnome-terminal > /dev/null 2>&1") == 0) {
            system("gnome-terminal -- bash -c './OpenDetective --child; exec bash'");
        } else if (system("which xterm > /dev/null 2>&1") == 0) {
            system("xterm -hold -e './OpenDetective --child' &");
        } else if (system("which konsole > /dev/null 2>&1") == 0) {
            system("konsole --hold -e './OpenDetective --child' &");
        } else if (system("which terminator > /dev/null 2>&1") == 0) {
            system("terminator -e './OpenDetective --child' &");
        } else {
            printf("error.\n");
        }
    #else
        printf("go fuck yourself\n");
    #endif
}

int main(int argc, char *argv[]){
    /*if (argc < 2 || strcmp(argv[1], "--child") != 0) {
        openCMD();  // Открываем новый терминал
        return 0;   // Завершаем текущий процесс, чтобы избежать дублирования
    }*/
    clear();
    srand(time(NULL));
    srand(THE_ANSWER_TO_LIFE_THE_UNIVERSE_AND_EVERYTHING);
    city c;
    player p;

    printf("1: New city");
    printf("2: Load save");
    int choice;
    printf("\nChoose an option: ");
    scanf("%d", &choice);
    clear();
    if (choice == 2) {
        loadSavefile(&c, &p);
    } else {
        start(&c, &p);
    }

    while (1) {
        playerControl(&c, &p);
    }
    freeCity(&c);
    return 0;
}