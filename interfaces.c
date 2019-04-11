#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "interfaces.h"
#define WITH_BUS 1
#define WITHOUT_BUS 0
#define INPUT_INT 0
#define INPUT_DOUBLE 1

char int_validator_of_input(int *inputField, FILE *inpFile) {
	char inp_str[255];
	int temp_val;

	if (fscanf(inpFile, "%254s", inp_str) == EOF) {
		printf("Error! Unexpected end of input!\n");
		return 1;
	}
	temp_val = atoi(inp_str);
	if (!temp_val) {
		printf("Error! Invalid input data: %s\n", inp_str);
		return 1;
	}

	*inputField = temp_val;

	return 0;
}

char double_validator_of_input(double *inputField, FILE *inpFile) {
	char inp_str[255];
	double temp_val;

	if (fscanf(inpFile, "%254s", inp_str) == EOF) {
		printf("Error! Unexpected end of input!\n");
		return 1;
	}
	temp_val = atof(inp_str);
	if (!temp_val) {
		printf("Error! Invalid input data: %s\n", inp_str);
		return 1;
	}

	*inputField = temp_val;

	return 0;
}

char input_truck(struct Transport *inpTransport, FILE *inpFile) {

	if (int_validator_of_input(&(inpTransport->tr.loadCapacity), inpFile)) {
		return 1;
	}
	
	if (int_validator_of_input(&(inpTransport->enginePower), inpFile)) {
		return 1;
	}

	if (double_validator_of_input(&(inpTransport->consumption), inpFile)) {
		return 1;
	}

	return 0;

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

char input_bus(struct Transport *inpTransport, FILE *inpFile) {

	if (int_validator_of_input(&(inpTransport->passCapacity), inpFile)) {
		return 1;
	}

	if (int_validator_of_input(&(inpTransport->enginePower), inpFile)) {
		return 1;
	}

	if (double_validator_of_input(&(inpTransport->consumption), inpFile)) {
		return 1;
	}

	return 0;

}

void output_bus(struct Transport *optTransport, FILE *optFile) {

	fprintf(optFile, "Bus\tPassengers capacity: %hu\tEngine power: %u\tQuotient: %.3lf\tConsumption: %.3lf\n", optTransport->passCapacity, optTransport->enginePower, quotient_transport(optTransport), optTransport->consumption);

}

char input_car(struct Transport *inpTransport, FILE *inpFile) {

	if (int_validator_of_input(&(inpTransport->passCapacity), inpFile)) {
		return 1;
	}

	if (int_validator_of_input(&(inpTransport->enginePower), inpFile)) {
		return 1;
	}

	if (int_validator_of_input(&(inpTransport->cr.maxSpeed), inpFile)) {
		return 1;
	}

	if (double_validator_of_input(&(inpTransport->consumption), inpFile)) {
		return 1;
	}

	return 0;

}


void output_car(struct Transport *optTransport, FILE *optFile) {

	fprintf(optFile, "Car\tPassengers capacity: %hu\tEngine power: %i\tMax speed: %hu\tQuotient: %.3lf\tConsumption: %.3lf\n", optTransport->passCapacity, optTransport->enginePower, optTransport->cr.maxSpeed, quotient_transport(optTransport), optTransport->consumption);

}

struct Transport *input_transport(FILE *inpFile) {

	struct Transport *inpTransport = (struct Transport *)malloc(sizeof(struct Transport));
	int key;

	if (fscanf(inpFile, "%i", &key) == EOF) {
		return NULL;
	}

	switch (key) {
		case 1:
			inpTransport->key = TRUCK;
			if (input_truck(inpTransport, inpFile)) {
				free(inpTransport);
				return inpTransport = -1;
			}
			break;
		case 2:
			inpTransport->key = BUS;
			if (input_bus(inpTransport, inpFile)) {
				free(inpTransport);
				return -1;
			}
			break;
		case 3:
			inpTransport->key = CAR;
			if (input_car(inpTransport, inpFile)) {
				free(inpTransport);
				return -1;
			}
			break;
		default:
			printf("Error! Invalid key: %i\n", key);
			free(inpTransport);
			return -1;
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

	if (addingNode->automobile == -1) {
		free(addingNode);

		return -1;
	}

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

char fill_list(struct RingList *list, FILE *inpFile) {

	if (list->head != NULL) {
		printf("\nError! List is not empty!\n");
		return 0;
	}

	char status = list_add_node(list, inpFile);

	while(status) {
		if (status == -1) {
			return 1;
		}
		(list->size)++;
		status = list_add_node(list, inpFile);
	}

	return 0;

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
