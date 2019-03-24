enum typeOfTransport {TRUCK, BUS};

struct truck {
	int loadCapacity;
};

struct bus {
	short passCapacity;
};

struct transport {
	enum typeOfTransport key;
	int enginePower;
	union
	{
		struct truck tr;
		struct bus bs;
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
void output_bus(struct bus *, FILE *, char );
struct transport *input_transport(FILE *);
void output_transport(struct transport *, FILE *, char );
char list_add_node(struct ringList *, FILE *);
void output_node(struct nodeOfList *, int , FILE *, char );
void init_list(struct ringList *);
void clear_list(struct ringList *);
void fill_list(struct ringList *, FILE *);
void out_list(struct ringList *, FILE *);