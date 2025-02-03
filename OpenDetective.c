#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PREFIX_COUNT 50
#define BASE_COUNT 50
#define SUFFIX_COUNT 50
#define ARRAY_SIZE 100
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

const char *first_half[50] = {
    "Tech", "Data", "Cyber", "Quantum", "Global", "Sky", "Future", "Net", "Digital", "Soft",
    "Mega", "Neo", "Alpha", "Blue", "Smart", "Core", "Eco", "Next", "Vision", "World",
    "Cloud", "Info", "Green", "Max", "Zen", "Vero", "Space", "Gen", "Secure", "Prime",
    "Virtual", "Flex", "Edge", "Inno", "Power", "Pro", "Data", "Logic", "Link", "Nova",
    "Perfect", "Bright", "Visionary", "Infinity", "Matrix", "Elite", "Start", "Techno", "Future",
    "Pixel"
};

const char *second_half[50] = {
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
    int firstPartIndex = rand()%50;
    int secondPartIndex = rand()%50;

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

void printMatrix(int** matrix, int height, int width) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%d", matrix[i][j]);
        }
        printf("\n");
    }
}

typedef enum type {
    RESIDENTIAL, // Жилой этаж
    COMMERCIAL,  // Коммерческий этаж
    OFFICE  // Промышленный этаж
} type;

typedef struct npc {
    char firstName[100];
    char lastName[100];
    void* placeOfResidence;
    void* placeOfWork;
} npc;

typedef struct room {
    npc* npc;
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
                r->npc = NULL;
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
            ((officeFloor*)f->floor_type_data)->office_count = 3;
            ((officeFloor*)f->floor_type_data)->offices = (office**)malloc(((officeFloor*)f->floor_type_data)->office_count * sizeof(office*));
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
    while (((residentialFloor*)c->residentialBuildingsList[countC]->floors[floorC]->floor_type_data)->rooms[roomC]->npc){
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
    ((residentialFloor*)c->residentialBuildingsList[countC]->floors[floorC]->floor_type_data)->rooms[roomC]->npc = n;
    }
}

void start(city* c, player* p) {
    printf("Enter city name: ");
    scanf("%99s", c->name);
    printf("Enter city width: ");
    scanf("%d", &c->width);
    printf("Enter city height: ");
    scanf("%d", &c->height);
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
    printf("AAAAAA");
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
                for (int l = 0; l < ((office*)c->officeBuildingsList[i]->floors[j]->floor_type_data)->employee_count; l++){
                    ((office*)c->officeBuildingsList[i]->floors[j]->floor_type_data)->employees[l] = generate_npc();
                    getNPCresidence(c, ((office*)c->officeBuildingsList[i]->floors[j]->floor_type_data)->employees[l]);
                }
            }
        }
    }

    for (int i = 0; i < c->residentialBuildings; i++){
        for (int j = 0; j < c->residentialBuildingsList[i]->height; j++){
            for (int k = 0; k < ((residentialFloor*)c->residentialBuildingsList[i]->floors[j]->floor_type_data)->room_count; k++){
                if (!((residentialFloor*)c->residentialBuildingsList[i]->floors[j]->floor_type_data)->rooms[k]->npc){
                    ((residentialFloor*)c->residentialBuildingsList[i]->floors[j]->floor_type_data)->rooms[k]->npc = generate_npc();
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


    printf("City generated successfully.\n");

}

void printMap(city* c, player* p) {
    for (int i = 0; i < c->height; i++) {
        for (int j = 0; j < c->width; j++) {
            if (p->x == i && p->y == j) {
                printf("☺");
            } else{
            if (c->cityMap[i][j]) {
                switch (c->cityMap[i][j]->building_type)
                {
                case RESIDENTIAL:
                    printf("⌂");
                    break;
                
                case OFFICE:
                    printf("F");
                    break;
                    
                default:
                    break;
                }
            } else {
                printf(" ");
            }}
        }
        printf("\n");
    }
}

void playerControl(city* c, player* p) {
    int choice;
    
    if (p->currentRoom) {
        if (p->currentRoom->npc) {
            printf("\n--- You are in %s %s's room ---\n", 
                   p->currentRoom->npc->firstName, 
                   p->currentRoom->npc->lastName);
        } else {
            printf("\n--- You are in an empty room ---\n");
        }
        printf("1. View Address\n");
        printf("2. Leave the Room\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nAddress: Building '%s', Floor %d, Room %d\n", 
                       p->currentBuilding->name, 
                       p->currentFloor->floorNumber + 1, 
                       (int)(p->currentRoom->room_number) + 1);
                break;
            case 2:
                printf("\nYou left the room.\n");
                p->currentRoom = NULL;
                break;
            default:
                printf("\nInvalid choice. Try again.\n");
        }
    } 
    else if (p->currentFloor) {
        printf("\n--- You are on Floor %d ---\n", p->currentFloor->floorNumber + 1);
        printf("1. Enter a Room\n");
        printf("2. Change Floor\n");
        printf("3. Leave the Building\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                printf("Enter room number (1-4): ");
                int roomNumber;
                scanf("%d", &roomNumber);

                if (roomNumber < 1 || roomNumber > 4) {
                    printf("\nInvalid room number. Try again.\n");
                } else {
                    p->currentRoom = ((residentialFloor*)p->currentFloor->floor_type_data)->rooms[roomNumber - 1];
                    printf("\nYou entered Room %d.\n", roomNumber);
                }
                break;
            }
            case 2: {
                printf("Enter floor number (1-%d): ", p->currentBuilding->height);
                int floorNumber;
                scanf("%d", &floorNumber);

                if (floorNumber < 1 || floorNumber > p->currentBuilding->height) {
                    printf("\nInvalid floor number. Try again.\n");
                } else {
                    p->currentFloor = p->currentBuilding->floors[floorNumber - 1];
                    printf("\nYou moved to Floor %d.\n", floorNumber);
                }
                break;
            }
            case 3:
                printf("\nYou left the building.\n");
                p->currentFloor = NULL;
                p->currentBuilding = NULL;
                break;
            default:
                printf("\nInvalid choice. Try again.\n");
        }
    } 
    else if (p->currentBuilding) {
        printf("\n--- You are outside the building '%s' ---\n", p->currentBuilding->name);
        printf("1. Enter a Floor\n");
        printf("2. Leave the Building\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                printf("Enter floor number (1-%d): ", p->currentBuilding->height);
                int floorNumber;
                scanf("%d", &floorNumber);

                if (floorNumber < 1 || floorNumber > p->currentBuilding->height) {
                    printf("\nInvalid floor number. Try again.\n");
                } else {
                    p->currentFloor = p->currentBuilding->floors[floorNumber - 1];
                    printf("\nYou entered Floor %d.\n", floorNumber);
                }
                break;
            }
            case 2:
                printf("\nYou left the building.\n");
                p->currentBuilding = NULL;
                break;
            default:
                printf("\nInvalid choice. Try again.\n");
        }
    } 
    else {
        printf("\n--- You are outside ---\n");
        printf("1. Enter a Building\n");
        printf("2. See a city map\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                printf("Enter building coordinates (x y): ");
                int x, y;
                scanf("%d %d", &x, &y);

                if (x < 0 || x >= c->height || y < 0 || y >= c->width) {
                    printf("\nInvalid coordinates. Try again.\n");
                } else {
                    p->currentBuilding = c->cityMap[x][y];
                    printf("\nYou entered the building '%s'.\n", p->currentBuilding->name);
                }
                break;
            }
            case 2:
                printMap(c, p);
                break;
            default:
                printf("\nInvalid choice. Try again.\n");
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
                    if (r->npc) {
                        free(r->npc);
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
