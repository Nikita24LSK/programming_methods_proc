#include <stdio.h>
#include <malloc.h>
#include "interfaces.h"
#define WITH_BUS 1
#define WITHOUT_BUS 0

void input_truck(struct Transport *inpTransport, FILE *inpFile) {

	fscanf(inpFile, "%i %i %lf", &(inpTransport->tr.loadCapacity), &(inpTransport->enginePower), &(inpTransport->consumption));

}

void output_truck(struct Transport *optTransport, FILE *optFile) {
	
	fprintf(optFile, "Truck\tLoad capacity: %u\tEngine power: %u\tQuotient: %.3lf\tConsumption: %.3lf\n", optTransport->tr.loadCapacity, optTransport->enginePower, quotient_transport(optTransport), optTransport->consumption);

}

double quotient_transport(struct Transport *procTransport) {

	if (procTransport->key == TRUCK) {
		return (double)(procTransport->tr.loadCapacity) / (double)(procTransport->enginePower);
	}
	else {
		return (double)((procTransport->passCapacity) * 75) / (double)(procTransport->enginePower);
	}

}

void input_bus(struct Transport *inpTransport, FILE *inpFile) {

	fscanf(inpFile, "%hu %u %lf", &(inpTransport->passCapacity), &(inpTransport->enginePower), &(inpTransport->consumption));

}

void output_bus(struct Transport *optTransport, FILE *optFile) {

	fprintf(optFile, "Bus\tPassengers capacity: %hu\tEngine power: %u\tQuotient: %.3lf\tConsumption: %.3lf\n", optTransport->passCapacity, optTransport->enginePower, quotient_transport(optTransport), optTransport->consumption);

}

void input_car(struct Transport *inpTransport, FILE *inpFile) {

	fscanf(inpFile, "%hu %i %hu %lf", &(inpTransport->passCapacity), &(inpTransport->enginePower), &(inpTransport->cr.maxSpeed), &(inpTransport->consumption));

}


void output_car(struct Transport *optTransport, FILE *optFile) {

	fprintf(optFile, "Car\tPassengers capacity: %hu\tEngine power: %i\tMax speed: %hu\tQuotient: %.3lf\tConsumption: %.3lf\n", optTransport->passCapacity, optTransport->enginePower, optTransport->cr.maxSpeed, quotient_transport(optTransport), optTransport->consumption);

}

struct Transport *input_transport(FILE *inpFile) {

	struct Transport *inpTransport = (struct Transport *)malloc(sizeof(struct Transport));
	int key;

	fscanf(inpFile, "%i", &key);

	switch (key) {
		case 1:
			inpTransport->key = TRUCK;
			input_truck(inpTransport, inpFile);
			break;
		case 2:
			inpTransport->key = BUS;
			input_bus(inpTransport, inpFile);
			break;
		case 3:
			inpTransport->key = CAR;
			input_car(inpTransport, inpFile);
			break;
		default:
			free(inpTransport);
			inpTransport = NULL;
			break;
	}

	return inpTransport;

}

void output_transport(struct Transport *optTransport, FILE *optFile, char busFlag) {

	switch (optTransport->key) {
		case TRUCK:
			output_truck(optTransport, optFile);
			break;
		case BUS:
			if (busFlag) {
				output_bus(optTransport, optFile);
			}
			break;
		case CAR:
			output_car(optTransport, optFile);
			break;
		default:
			break;
	}

}

char compare_transport(struct Transport *first, struct Transport *second) {

	return quotient_transport(first) < quotient_transport(second);

}

char list_add_node(struct RingList *workList, FILE *inpFile) {

	struct NodeOfList *addingNode = (struct NodeOfList *)malloc(sizeof(struct NodeOfList));
	addingNode->automobile = input_transport(inpFile);

	if (addingNode->automobile == NULL) {
		free(addingNode);

		return 0;
	}

	if (workList->head == NULL) {
		workList->head = addingNode;
		addingNode->next = addingNode;
		addingNode->prev = addingNode;
	}
	else {
		addingNode->next = workList->head;
		addingNode->prev = workList->head->prev;
		workList->head->prev->next = addingNode;
		workList->head->prev = addingNode;
	}
	
	return 1;

}

void output_node(struct NodeOfList *firstNode, int offset, FILE *optFile, char busFlag) {

	struct NodeOfList *curNode = firstNode;
	int i;

	for (i=0; i < offset; i++) {
		curNode = curNode->next;
	}

	output_transport(curNode->automobile, optFile, busFlag);

}

void clear_node(struct NodeOfList *firstNode, int offset) {

	int i;
	struct NodeOfList *curNode = firstNode;

	for (i=0; i < offset - 1; i++) {
		curNode = curNode->next;
	}

	free(curNode->automobile);
	free(curNode);

}

struct NodeOfList *get_node(struct NodeOfList *head, int offset) {

	struct NodeOfList *retNode = head;
	int i;

	for (i=0; i < offset; i++) {
		retNode = retNode->next;
	}

	return retNode;
}

void swap_nodes(struct NodeOfList *head, int first, int second) {

	struct Transport *temp;

	temp = get_node(head, first)->automobile;
	get_node(head, first)->automobile = get_node(head, second)->automobile;
	get_node(head, second)->automobile = temp;

}

void init_list(struct RingList *initList) {

	initList->size = 0;
	initList->head = NULL;

}

void clear_list(struct RingList *clearingList) {

	int i;

	if (clearingList->head == NULL) {
		return;
	}
	else {
		for (i=clearingList->size; i > 0; i--) {
			clear_node(clearingList->head, i);
		}
		clearingList->head = NULL;
	}

	clearingList->size = 0;

}

void fill_list(struct RingList *list, FILE *inpFile) {

	while(list_add_node(list, inpFile)) {
		(list->size)++;
	}

}

void sort_list(struct NodeOfList *head, int left, int right) {

	int i, last;

	if (left >= right) {
		return;
	}

	swap_nodes(head, left, (left+right)/2);
	last = left;
	for (i=left+1; i <= right; i++) {
		if (compare_transport(get_node(head, i)->automobile, get_node(head, left)->automobile)) {
			swap_nodes(head, ++last, i);
		}
	}

	swap_nodes(head, left, last);
	sort_list(head, left, last-1);
	sort_list(head, last+1, right);
	
}

void out_list(struct RingList *list, FILE *optFile) {

	int i;

	if (list->size == 0) {
		printf("List is empty!\n");
		
		return;
	}

	for (i=0; i < list->size; i++) {
		output_node(list->head, i, optFile, WITH_BUS);
	}

	fprintf(optFile, "\nWithout bus\n");

	for (i=0; i < list->size; i++) {
		output_node(list->head, i, optFile, WITHOUT_BUS);
	}

}
