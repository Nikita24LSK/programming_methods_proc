/*

	Заголовочный файл с описанием структур, используемых
	в программе, и прототипов функций.

	Задается три вида транспорта - грузовик, автобус и автомобиль.
	
	Для хранения данных используется кольцевой двусвязный список,
	который поддерживает функцию сортировки по вычисляемому параметру -
	отношению грузоподъемности к мощности двигателя.

*/

enum typeOfTransport {TRUCK, BUS, CAR};

struct Truck {
	int loadCapacity;
};

struct Car {
	short maxSpeed;
};

struct Transport {
	enum typeOfTransport key;
	short passCapacity;
	unsigned int enginePower;
	double consumption;
	union
	{
		struct Truck tr;
		struct Car cr;
	};
};

struct NodeOfList {
	struct Transport *automobile;
	struct NodeOfList *next;
	struct NodeOfList *prev;
};

struct RingList {
	long size;
	struct NodeOfList *head;
};

char int_validator_of_input(int *, FILE *);
char double_validator_of_input(double *, FILE *);
char input_truck(struct Transport *, FILE *);
char output_truck(struct Transport *, FILE *);
char input_bus(struct Transport *, FILE *);
char output_bus(struct Transport *, FILE *);
char input_car(struct Transport *, FILE *);
char output_car(struct Transport *, FILE *);
double quotient_transport(struct Transport *);
struct Transport *input_transport(FILE *);
char compare_transport(struct Transport *, struct Transport *);
char output_transport(struct Transport *, FILE *, char );
char list_add_node(struct RingList *, FILE *);
char output_node(struct NodeOfList *, int , FILE *, char );
struct NodeOfList *get_node(struct NodeOfList *, int );
void swap_nodes(struct NodeOfList *, int , int );
void init_list(struct RingList *);
void clear_list(struct RingList *);
char fill_list(struct RingList *, FILE *);
void sort_list(struct NodeOfList *, int , int );
char out_list(struct RingList *, FILE *);