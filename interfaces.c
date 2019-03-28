#include <stdio.h>
#include <malloc.h>
#include "interfaces.h"

void input_truck(struct transport *inpTransport, FILE *inpFile) {

	fscanf(inpFile, "%u %u", &(inpTransport->tr.loadCapacity), &(inpTransport->enginePower));

}

void output_truck(struct transport *optTransport, FILE *optFile) {

	fprintf(optFile, "Truck\tLoad capacity: %u\tEngine power: %u\tAttitude: %lf\n", optTransport->tr.loadCapacity, optTransport->enginePower, attitude_transport(optTransport));

}

double attitude_transport(struct transport *procTransport) {

	if (procTransport->key == TRUCK) {
		return (double)(procTransport->tr.loadCapacity)/(double)(procTransport->enginePower);
	}
	else {
		return (double)((procTransport->passCapacity)*75)/(double)(procTransport->enginePower);
	}

}

void input_bus(struct transport *inpTransport, FILE *inpFile) {

	fscanf(inpFile, "%hu %u", &(inpTransport->passCapacity), &(inpTransport->enginePower));

}

void output_bus(struct transport *optTransport, FILE *optFile) {

	fprintf(optFile, "Bus\tPassengers capacity: %hu\tEngine power: %u\tAttitude: %lf\n", optTransport->passCapacity, optTransport->enginePower, attitude_transport(optTransport));

}

void input_car(struct transport *inpTransport, FILE *inpFile) {
	fscanf(inpFile, "%hu %i %hu", &(inpTransport->passCapacity), &(inpTransport->enginePower), &(inpTransport->cr.maxSpeed));
}

void output_car(struct transport *optTransport, FILE *optFile) {
	fprintf(optFile, "Car\tPassengers capacity: %hu\tEngine power: %i\tMax speed: %hu\tAttitude: %lf\n", optTransport->passCapacity, optTransport->enginePower, optTransport->cr.maxSpeed, attitude_transport(optTransport));
}

struct transport *input_transport(FILE *inpFile) {

	struct transport *inpTransport = (struct transport *)malloc(sizeof(struct transport));
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

void output_transport(struct transport *optTransport, FILE *optFile) {

	switch (optTransport->key) {
		case TRUCK:
			output_truck(optTransport, optFile);
			break;
		case BUS:
			output_bus(optTransport, optFile);
			break;
		case CAR:
			output_car(optTransport, optFile);
			break;
		default:
			break;
	}

}

char compare_transport(struct transport *first, struct transport *second) {

	return attitude_transport(first) < attitude_transport(second);

}

char list_add_node(struct ringList *workList, FILE *inpFile) {

	struct nodeOfList *addingNode = (struct nodeOfList *)malloc(sizeof(struct nodeOfList));
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

void output_node(struct nodeOfList *firstNode, int offset, FILE *optFile) {

	struct nodeOfList *curNode = firstNode;
	int i;

	for (i = 0; i < offset; i++) {
		curNode = curNode->next;
	}

	output_transport(curNode->automobile, optFile);

}

void clear_node(struct nodeOfList *firstNode, int offset) {
	int i;
	struct nodeOfList *curNode = firstNode;

	for (i = 0; i < offset-1; i++) {
		curNode = curNode->next;
	}

	free(curNode->automobile);
	free(curNode);

}

struct nodeOfList *get_node(struct nodeOfList *head, int offset) {
	struct nodeOfList *retNode = head;
	int i;

	for (i = 0; i < offset; i++) {
		retNode = retNode->next;
	}

	return retNode;
}

void swap_nodes(struct nodeOfList *head, int first, int second) {
	struct transport *temp;

	temp = get_node(head, first)->automobile;
	get_node(head, first)->automobile = get_node(head, second)->automobile;
	get_node(head, second)->automobile = temp;
}

void init_list(struct ringList *initList) {

	initList->size = 0;
	initList->head = NULL;

}

void clear_list(struct ringList *clearingList) {

	int i;

	if (clearingList->head == NULL) {
		return;
	}
	else {
		for (i = clearingList->size; i > 0; i--) {
			clear_node(clearingList->head, i);
		}
		clearingList->head = NULL;
	}

	clearingList->size = 0;

}

void fill_list(struct ringList *list, FILE *inpFile) {

	while(list_add_node(list, inpFile)) {
		(list->size)++;
	}

}

void sort_list(struct nodeOfList *head, int left, int right) {
	int i, last;

	if (left >= right) {
		return;
	}

	swap_nodes(head, left, (left+right)/2);
	last = left;
	for (i = left+1; i <= right; i++) {
		if (compare_transport(get_node(head, i)->automobile, get_node(head, left)->automobile)) {
			swap_nodes(head, ++last, i);
		}
	}
	swap_nodes(head, left, last);
	sort_list(head, left, last-1);
	sort_list(head, last+1, right);
}

void out_list(struct ringList *list, FILE *optFile) {

	int i;

	if (list->size == 0) {
		printf("List is empty!\n");
		return;
	}

	for (i = 0; i < list->size; i++) {
		output_node(list->head, i, optFile);
	}

}