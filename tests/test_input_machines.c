#include "unity.h"
#include "interfaces.h"
#include <malloc.h>

void setUp(void) {

}

void tearDown(void) {
	
}

void test_input_machines(void) {
	
	struct Transport *inpTransport = (struct Transport *)malloc(sizeof(struct Transport));
	FILE *inp = NULL;
	FILE *out = NULL;

	if ((inp = fopen("/home/dragon/prog/c/procTests/input_files/input_machines", "r")) == NULL) {
		printf("Cannot open input file!\n");
		return;
	}

	if ((out = fopen("/home/dragon/prog/c/procTests/input_files/output_machines", "w")) == NULL) {
		printf("Cannot open output file!\n");
		return;
	}

	TEST_ASSERT_EQUAL_INT(0, input_truck(inpTransport, inp));
	TEST_ASSERT_EQUAL_INT(2, inpTransport->tr.loadCapacity);
	TEST_ASSERT_EQUAL_INT(3, inpTransport->enginePower);
	TEST_ASSERT_EQUAL_FLOAT(4.4, inpTransport->consumption);
	TEST_ASSERT(output_truck(inpTransport, out) > 0);
	
	TEST_ASSERT_EQUAL_INT(0, input_bus(inpTransport, inp));
	TEST_ASSERT_EQUAL_INT(33, inpTransport->passCapacity);
	TEST_ASSERT_EQUAL_INT(11, inpTransport->enginePower);
	TEST_ASSERT_EQUAL_FLOAT(6.8, inpTransport->consumption);
	TEST_ASSERT(output_bus(inpTransport, out) > 0);

	TEST_ASSERT_EQUAL_INT(0, input_car(inpTransport, inp));
	TEST_ASSERT_EQUAL_INT(1, inpTransport->passCapacity);
	TEST_ASSERT_EQUAL_INT(2, inpTransport->enginePower);
	TEST_ASSERT_EQUAL_INT(3, inpTransport->cr.maxSpeed);
	TEST_ASSERT_EQUAL_FLOAT(7.7, inpTransport->consumption);
	TEST_ASSERT(output_car(inpTransport, out) > 0);
	
	free(inpTransport);
	fclose(inp);
	fclose(out);
	
}