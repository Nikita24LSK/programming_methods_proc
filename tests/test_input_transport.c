#include "unity.h"
#include "interfaces.h"
#include <malloc.h>

void setUp(void) {

}

void tearDown(void) {
	
}

void test_input_transport(void) {
	
	FILE *inp = NULL;
	struct Transport *inpTransport = NULL;

	if ((inp = fopen("/home/dragon/prog/c/procTests/input_files/input_transport", "r")) == NULL) {
		printf("Cannot open input file!\n");
		return;
	}

	TEST_ASSERT_NOT_NULL(inpTransport = input_transport(inp));
	TEST_ASSERT(inpTransport != -1);
	TEST_ASSERT_EQUAL_INT(0, inpTransport->key);
	free(inpTransport);
	inpTransport = NULL;
	
	TEST_ASSERT_NOT_NULL(inpTransport = input_transport(inp));
	TEST_ASSERT(inpTransport != -1);
	TEST_ASSERT_EQUAL_INT(1, inpTransport->key);
	free(inpTransport);
	inpTransport = NULL;

	TEST_ASSERT_NOT_NULL(inpTransport = input_transport(inp));
	TEST_ASSERT(inpTransport != -1);
	TEST_ASSERT_EQUAL_INT(2, inpTransport->key);
	free(inpTransport);
	inpTransport = NULL;

	TEST_ASSERT_NOT_NULL(inpTransport = input_transport(inp));
	TEST_ASSERT(inpTransport == -1);
	
	fclose(inp);
	
}