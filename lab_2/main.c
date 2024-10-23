#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10000

#include "merge_sort.c"
#include "quick_sort.c"

void print_array(int*, int);
void avg();
void worst_case();

int main() {
	
	avg();
	worst_case();
	
	return 0;
}

void avg() {

	FILE *h;
	h = fopen("avg.dat","w");

	for (int len = 10; len <= MAX; len+=10) {
		
		int *B = malloc(len*sizeof(int));
		int *D = malloc(len*sizeof(int));

		srand(time(NULL));

		for (int i=0; i<len; i++) {
			int value = rand();
			B[i] = value;
			D[i] = value;
		}



		clock_t start, end;
		double  cpu_time_merge_sort, cpu_time_quick_sort;

		start = clock();
		merge_sort(B, 0, len-1);
		end = clock();
		cpu_time_merge_sort = ((double) (end - start)) / CLOCKS_PER_SEC;

		printf("\nSorted	%i	items in	%f	%f \n\n", len, cpu_time_merge_sort, cpu_time_quick_sort);
		fprintf(h,"%i,%f,%f\n", len, cpu_time_merge_sort, cpu_time_quick_sort);

	}

	fclose(h);
}

void worst_case() {
	
	FILE *h;
	h = fopen("worst_case.dat","w");

	for (int len = 10; len <= MAX; len+=10) {
		
		int *B = malloc(len*sizeof(int));
		int *D = malloc(len*sizeof(int));

		merge_sort_worst_case(B, len);
		quick_sort_worst_case(D, len);


		clock_t start, end;
		double cpu_time_merge_sort, cpu_time_quick_sort;
		
		start = clock();
		merge_sort(B, 0, len-1);
		end = clock();
		cpu_time_merge_sort = ((double) (end - start)) / CLOCKS_PER_SEC;
		
		start = clock();
		quick_sort(D, 0, len-1);
		end = clock();
		cpu_time_quick_sort = ((double) (end - start)) / CLOCKS_PER_SEC;
		

		printf("\nSorted	%i	items in	%f	%f	\n\n", len, cpu_time_merge_sort, cpu_time_quick_sort);
		fprintf(h,"%i,%f,%f\n", len, cpu_time_merge_sort, cpu_time_quick_sort);

	}

	fclose(h);
}

void print_array(int A[], int len) {

	for (int i = 0; i < len-1; i++) {
		printf("%i, ", A[i]);
	}
	printf("%i\n", A[len-1]);

}
