#include "unity.h"
#include "interfaces.h"
#include <malloc.h>

void setUp(void) {

}

void tearDown(void) {
	
}

void test_sort_list(void) {
	
	FILE *inp = NULL;
	struct RingList *testList = (struct RingList *)malloc(sizeof(struct RingList));
	struct NodeOfList *inspNode = NULL;
	struct NodeOfList *gettingNode = NULL;

	if ((inp = fopen("/home/dragon/prog/c/procTests/input_files/sort_list", "r")) == NULL) {
		printf("Cannot open input file!\n");
		return;
	}

	init_list(testList);
	fill_list(testList, inp);

	gettingNode = get_node(testList->head, 2);
	TEST_ASSERT_EQUAL_INT(2, gettingNode->automobile->key);
	TEST_ASSERT_EQUAL_INT(1, gettingNode->automobile->passCapacity);
	TEST_ASSERT_EQUAL_INT(22, gettingNode->automobile->enginePower);

	swap_nodes(testList->head, 2, 3);
	gettingNode = get_node(testList->head, 3);
	TEST_ASSERT_EQUAL_INT(2, gettingNode->automobile->key);
	TEST_ASSERT_EQUAL_INT(1, gettingNode->automobile->passCapacity);
	TEST_ASSERT_EQUAL_INT(22, gettingNode->automobile->enginePower);

	gettingNode = get_node(testList->head, 2);
	TEST_ASSERT_EQUAL_INT(0, gettingNode->automobile->key);
	TEST_ASSERT_EQUAL_INT(10, gettingNode->automobile->tr.loadCapacity);
	TEST_ASSERT_EQUAL_INT(14, gettingNode->automobile->enginePower);

	sort_list(testList->head, 0, testList->size - 1);
	inspNode = testList->head;

	TEST_ASSERT_EQUAL_INT(0, inspNode->automobile->key);
	TEST_ASSERT_EQUAL_INT(2, inspNode->automobile->tr.loadCapacity);
	TEST_ASSERT_EQUAL_INT(3, inspNode->automobile->enginePower);

	inspNode = inspNode->next;
	TEST_ASSERT_EQUAL_INT(0, inspNode->automobile->key);
	TEST_ASSERT_EQUAL_INT(10, inspNode->automobile->tr.loadCapacity);
	TEST_ASSERT_EQUAL_INT(14, inspNode->automobile->enginePower);

	inspNode = inspNode->next;
	TEST_ASSERT_EQUAL_INT(2, inspNode->automobile->key);
	TEST_ASSERT_EQUAL_INT(1, inspNode->automobile->passCapacity);
	TEST_ASSERT_EQUAL_INT(22, inspNode->automobile->enginePower);

	inspNode = inspNode->next;
	TEST_ASSERT_EQUAL_INT(1, inspNode->automobile->key);
	TEST_ASSERT_EQUAL_INT(22, inspNode->automobile->passCapacity);
	TEST_ASSERT_EQUAL_INT(33, inspNode->automobile->enginePower);
	
	clear_list(testList);
	TEST_ASSERT_NULL(testList->head);
	TEST_ASSERT_EQUAL_INT(0, testList->size);

	free(gettingNode);
	free(testList);
	fclose(inp);
	
}