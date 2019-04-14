#include "unity.h"
#include "interfaces.h"
#include <malloc.h>

void setUp(void) {

}

void tearDown(void) {
	
}

void test_out_list(void) {
	
	FILE *inp = NULL;
	FILE *out = NULL;
	struct RingList *testList = (struct RingList *)malloc(sizeof(struct RingList));

	if ((inp = fopen("/home/dragon/prog/c/procTests/input_files/out_list", "r")) == NULL) {
		printf("Cannot open input file!\n");
		return;
	}

	if ((out = fopen("/home/dragon/prog/c/procTests/output_files/out_list", "w")) == NULL) {
		printf("Cannot open output file!\n");
		return;
	}

	init_list(testList);
	fill_list(testList, inp);

	TEST_ASSERT_EQUAL_INT(0, out_list(testList, out));
	
	clear_list(testList);
	
	free(testList);
	fclose(inp);
	fclose(out);
	
}