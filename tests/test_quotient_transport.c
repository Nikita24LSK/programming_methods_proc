#include "unity.h"
#include "unity_internals.h"
#include "interfaces.h"
#include <malloc.h>
#include <stdlib.h>

void setUp(void) {

}

void tearDown(void) {
	
}

void test_quotient_transport(void) {
	
	struct Transport *inpTransport = (struct Transport *)malloc(sizeof(struct Transport));
	FILE *inp = NULL;
	if ((inp = fopen("/home/dragon/prog/c/procTests/input_files/quotient_transport", "r")) == NULL) {
		printf("Cannot open input file!\n");
		return;
	}

	input_truck(inpTransport, inp);
	TEST_ASSERT_EQUAL_FLOAT(0.666667, quotient_transport(inpTransport));
	
	free(inpTransport);
	fclose(inp);
	
}
