#include <stdio.h>
#include "interfaces.h"

int main(int argc, char *argv[]) {
	
	FILE *inp, *out;

	if (argc != 3) {
		printf("\nUsage lab_proc <input_file> <output_file>\n");
		return 1;
	}

	if ((inp = fopen(argv[1], "r")) == NULL) {
		printf("\nCannot to open input file!\n");
		return 1;
	}

	if ((out = fopen(argv[2], "w")) == NULL) {
		printf("\nCannot to open output file!\n");
		return 1;
	}

	printf("\nStart\n");
	
	struct ringList container;
	init_list(&container);

	printf("Filling list\n");
	fill_list(&container, inp);
	printf("List was fill\n");
	printf("Writing data\n");
	out_list(&container, out);
	printf("Data was written\n");
	printf("Clearing container\n");
	clear_list(&container);
	printf("Container was clear!\n");
	out_list(&container, out);

	fclose(inp);
	fclose(out);

	return 0;
}