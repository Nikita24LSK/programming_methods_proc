#include <stdio.h>
#include "interfaces.h"

int main(int argc, char *argv[]) {
	
	FILE *inp, *out;

	if (argc != 3) {
		printf("\nUsage lab_proc <input_file> <output_file>\n");

		return 1;
	}

	// Проверка на неудачное открытие входного файла
	if ((inp = fopen(argv[1], "r")) == NULL) {
		printf("\nCould not to open input file!\n");

		return 1;
	}


	// Проверка на неудачное открытие выходного файла
	if ((out = fopen(argv[2], "w")) == NULL) {
		printf("\nCould not to open output file!\n");
		
		return 1;
	}

	printf("\nStart\n");
	
	// Инициализируем кольцевой двусвязный список, используемый в качестве контейнера
	struct RingList container;
	init_list(&container);

	// Заполняем контейнер - считываем данные из входного файла
	printf("Filling list\n");
	if (fill_list(&container, inp)) {
		fclose(inp);
		fclose(out);

		return 1;
	}
	printf("List was fill\n");

	// Записываем данные в выходной файл
	printf("Writing data\n");
	out_list(&container, out);
	printf("Data was written\n");

	// Сортируем элементы контейнера
	printf("Sorting container\n");
	fprintf(out, "\nSorting data\n");
	sort_list(container.head, 0, (container.size)-1);

	// Записываем отсортированные данные в файл
	out_list(&container, out);

	// Вызываем мультиметод
	printf("Calling multimethod\n");
	multimethod(&container, out);

	// Очищаем контейнер
	printf("Clearing container\n");
	clear_list(&container);
	printf("Container was clear!\n");

	// Попытка вывести пустой контейнер
	out_list(&container, out);

	fclose(inp);
	fclose(out);

	return 0;

}
