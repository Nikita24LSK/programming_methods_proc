#include "unity.h"
#include "unity_internals.h"
#include "interfaces.h"
#include <malloc.h>
#include <stdlib.h>

void setUp(void) {

}

void tearDown(void) {

}

void test_init_list(void) {
	
	struct RingList *test_list = (struct RingList *)malloc(sizeof(struct RingList));

	init_list(test_list);

	TEST_ASSERT_EQUAL_INT(0, test_list->size);
	TEST_ASSERT_EQUAL_PTR(NULL, test_list->head);

	free(test_list);
}