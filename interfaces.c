#include <stdio.h>
#include <malloc.h>
#include "interfaces.h"

void input_truck(struct transport *inpTransport, FILE *inpFile) {

	fscanf(inpFile, "%i %i", &(inpTransport->tr.loadCapacity), &(inpTransport->enginePower));

}

void output_truck(struct transport *optTransport, FILE *optFile) {

	fprintf(optFile, "Truck\tLoad capacity: %i\tEngine power: %i\n", optTransport->tr.loadCapacity, optTransport->enginePower);

}

void input_bus(struct transport *inpTransport, FILE *inpFile) {

	fscanf(inpFile, "%hu %i", &(inpTransport->bs.passCapacity), &(inpTransport->enginePower));

}

void output_bus(struct transport *optTransport, FILE *optFile) {

	fprintf(optFile, "Bus\tPassengers capacity: %hu\tEngine power: %i\n", optTransport->bs.passCapacity, optTransport->enginePower);

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
		default:
			break;
	}

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