enum typeOfTransport {TRUCK, BUS, CAR};

struct truck {
	int loadCapacity;
};

struct bus {
	short passCapacity;
};

struct car {
	short passCapacity, maxSpeed;
};

struct transport {
	enum typeOfTransport key;
	int enginePower;
	union
	{
		struct truck tr;
		struct bus bs;
		struct car cr;
	};
};

struct nodeOfList {
	struct transport *automobile;
	struct nodeOfList *next;
	struct nodeOfList *prev;
};

struct ringList {
	long size;
	struct nodeOfList *head;
};

void input_truck(struct truck *, FILE *);
void output_truck(struct truck *, FILE *);
void input_bus(struct bus *, FILE *);
void output_bus(struct bus *, FILE *);
void input_car(struct car *, FILE *);
void output_car(struct car *, FILE *);
struct transport *input_transport(FILE *);
void output_transport(struct transport *, FILE *);
char list_add_node(struct ringList *, FILE *);
void output_node(struct nodeOfList *, int , FILE *);
void init_list(struct ringList *);
void clear_list(struct ringList *);
void fill_list(struct ringList *, FILE *);
void out_list(struct ringList *, FILE *);