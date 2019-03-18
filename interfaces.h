enum typeOfTransport {TRUCK, BUS};

struct truck {
	int loadCapacity, enginePower;
	double consumption;
};

struct bus {
	short passCapacity;
	int enginePower;
	double consumption;
};

struct transport {
	enum typeOfTransport key;
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
void output_bus(struct bus *, FILE *);
struct transport *input_transport(FILE *);
void output_transport(struct transport *, FILE *);
char list_add_node(struct ringList *, FILE *);
void output_node(struct nodeOfList *, int , FILE *);
void init_list(struct ringList *);
void clear_list(struct ringList *);
void fill_list(struct ringList *, FILE *);
void out_list(struct ringList *, FILE *);