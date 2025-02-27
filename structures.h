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