enum typeOfTransport {TRUCK, BUS};

struct truck {
	unsigned int loadCapacity;
};

struct bus {
	unsigned short passCapacity;
};

struct transport {
	enum typeOfTransport key;
	unsigned int enginePower;
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

void input_truck(struct transport *, FILE *);
void output_truck(struct transport *, FILE *);
void input_bus(struct transport *, FILE *);
void output_bus(struct transport *, FILE *);
double attitude_truck(unsigned int , unsigned int );
double attitude_bus(unsigned short , unsigned int );
struct transport *input_transport(FILE *);
void output_transport(struct transport *, FILE *);
char list_add_node(struct ringList *, FILE *);
void output_node(struct nodeOfList *, int , FILE *);
void init_list(struct ringList *);
void clear_list(struct ringList *);
void fill_list(struct ringList *, FILE *);
void out_list(struct ringList *, FILE *);