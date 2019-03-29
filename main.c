#include <stdio.h>
#include "interfaces.h"

int main(int argc, char *argv[]) {
	
	FILE *inp, *out;

	if (argc != 3) {
		printf("\nUsage lab_proc <input_file> <output_file>\n");

		return 1;
	}

	if ((inp = fopen(argv[1], "r")) == NULL) {
		printf("\nCould not to open input file!\n");

		return 1;
	}

	if ((out = fopen(argv[2], "w")) == NULL) {
		printf("\nCould not to open output file!\n");
		
		return 1;
	}

	printf("\nStart\n");
	
	struct RingList container;
	init_list(&container);

	printf("Filling list\n");
	fill_list(&container, inp);
	printf("List was fill\n");
	printf("Writing data\n");
	out_list(&container, out);
	printf("Data was written\n");
	printf("Sorting container\n");
	fprintf(out, "\nSorting data\n");
	sort_list(container.head, 0, (container.size)-1);
	out_list(&container, out);
	printf("Clearing container\n");
	clear_list(&container);
	printf("Container was clear!\n");
	out_list(&container, out);

	fclose(inp);
	fclose(out);

	return 0;
}