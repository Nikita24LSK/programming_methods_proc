#include "unity.h"
#include "interfaces.h"
#include <malloc.h>

void setUp(void) {

}

void tearDown(void) {
	
}

void test_input_transport(void) {
	
	FILE *inp = NULL;
	struct Transport *firstTransport = NULL;
	struct Transport *secondTransport = NULL;

	if ((inp = fopen("/home/dragon/prog/c/procTests/input_files/compare_transport", "r")) == NULL) {
		printf("Cannot open input file!\n");
		return;
	}

	TEST_ASSERT_NOT_NULL(firstTransport = input_transport(inp));
	TEST_ASSERT(firstTransport != -1);
	
	TEST_ASSERT_NOT_NULL(secondTransport = input_transport(inp));
	TEST_ASSERT(secondTransport != -1);

	TEST_ASSERT_TRUE(compare_transport(firstTransport, secondTransport));
	
	free(firstTransport);
	free(secondTransport);
	fclose(inp);
	
}