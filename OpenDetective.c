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
} npc;

typedef struct room {
    npc* npc;
    void* parentFloor;
    int room_number;
} room;

typedef struct floor {
    int floorNumber;
    room** rooms;
    int room_count;
    type floor_type;
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
            break;
        case OFFICE:
            f->floor_type = OFFICE;
            break;
        default:
            printf("Unknown building type.\n");
            free(f);
            exit(1);
        }

        // Выделяем память для комнат
        f->rooms = (room**)malloc(4 * sizeof(room*));
        if (!f->rooms) {
            printf("Error allocating memory for rooms.\n");
            free(f);
            exit(1);
        }

        for (int j = 0; j < 4; j++) {
            room* r = (room*)malloc(sizeof(room));
            if (!r) {
                printf("Error allocating memory for room.\n");
                for (int k = 0; k < j; k++) {
                    free(f->rooms[k]);
                }
                free(f->rooms);
                free(f);
                exit(1);
            }
            r->npc = NULL;
            r->parentFloor = f;
            r->room_number = j;
            f->rooms[j] = r;
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

    for (int i = 0; i < c->height; i++) {
        for (int j = 0; j < c->width; j++) {
            building* b = c->cityMap[i][j];
            for (int k = 0; k < b->height; k++) {
                if (b->floors[k]->floor_type == RESIDENTIAL){
                    for (int l = 0; l < 4; l++) {
                        room* r = b->floors[k]->rooms[l];
                        r->npc = generate_npc();    
                    }     
                }
            }
        }
    }
    p->x = rand() % c->height;
    p->y = rand() % c->width;
    player_building_spawn(c, p);
    p->currentBuilding = c->cityMap[p->x][p->y];
    p->currentFloor = p->currentBuilding->floors[rand() % p->currentBuilding->height];
    p->currentRoom = p->currentFloor->rooms[rand() % 4];


    printf("City generated successfully.\n");

}

/*void inspect_building(city* c) {
    int x, y;
    printf("Enter building coordinates (x y): ");
    scanf("%d %d", &x, &y);
    
    if (x < 0 || x >= c->height || y < 0 || y >= c->width) {
        printf("Invalid coordinates.\n");
        return;
    }
    
    building* b = c->cityMap[x][y];
    printf("Building: %s\n", b->name);
    printf("Height: %d floors\n", b->height);
    
    for (int i = 0; i < b->height; i++) {
        printf(" Floor %d:\n", i + 1);
        for (int j = 0; j < 4; j++) {
            room r = b->floors[i]->rooms[j];
            if (r.npc) {
                printf("  Room %d: %s %s\n", j + 1, r.npc->firstName, r.npc->lastName);
            } else {
                printf("  Room %d: Empty\n", j + 1);
            }
        }
    }
}*/

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
                    p->currentRoom = p->currentFloor->rooms[roomNumber - 1];
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
        printf("2. Explore the City\n");
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
                printf("\nYou are exploring the city...\n");
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
                    room* r = b->floors[k]->rooms[l];
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

void printMap(city* c, player* p) {
    for (int i = 0; i < c->height; i++) {
        for (int j = 0; j < c->width; j++) {
            if (p->x == i && p->y == j) {
                printf("☺");
            } else{
            if (c->cityMap[i][j]) {
                printf("⌂");
            } else {
                printf(" ");
            }}
        }
        printf("\n");
    }
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
