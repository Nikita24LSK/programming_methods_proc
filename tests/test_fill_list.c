#include "unity.h"
#include "interfaces.h"
#include <malloc.h>

void setUp(void) {

}

void tearDown(void) {
	
}

void test_fill_list(void) {
	
	FILE *inp = NULL;
	struct RingList *testList = (struct RingList *)malloc(sizeof(struct RingList));

	if ((inp = fopen("/home/dragon/prog/c/procTests/input_files/fill_list", "r")) == NULL) {
		printf("Cannot open input file!\n");
		return;
	}

	init_list(testList);

	TEST_ASSERT_EQUAL_INT(1, fill_list(testList, inp));
	
	free(testList);
	fclose(inp);
	
}