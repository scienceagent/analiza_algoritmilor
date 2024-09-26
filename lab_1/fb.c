#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 500 
static long long *fib_table; 

long long fib_iterative(int n) {
    long long first = 0, second = 1, val = 0;
    if (n == 0) return first;
    if (n == 1) return second; 
    for (int i = 2; i <= n; i++) {
        val = first + second;
        first = second;
        second = val;
    }
    return second;
}

long long fib_recursive(int n) {
    if (n <= 1) return n;
    return fib_recursive(n - 1) + fib_recursive(n - 2);
}

long long fib_d(int n) {
    if (n <= 1) return n;
    if (fib_table[n] != -1) return fib_table[n];
    fib_table[n] = fib_d(n - 1) + fib_d(n - 2);
    return fib_table[n];
}

long long fib_dynamic(int n) {
    for (int i = 0; i < SIZE; i++) fib_table[i] = -1;
    fib_table[0] = 0;
    fib_table[1] = 1;
    return fib_d(n);
}

void analyze_execution(int n, int call) {
    struct timespec start, end;
    double cpu_time_used;
    long long n_val;

    clock_gettime(CLOCK_MONOTONIC, &start);
    if (call == 0) {
        n_val = fib_iterative(n);
    } else if (call == 1) {
        n_val = fib_recursive(n);
    } else {
        n_val = fib_dynamic(n);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);

    cpu_time_used = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Fibonacci number at position %d: %lld\n", n, n_val);
    printf("Execution time: %f seconds\n", cpu_time_used);
}

int main() {
    int choice, n = 0, call = 0;

    fib_table = (long long *)malloc(SIZE * sizeof(long long));
    if (fib_table == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    while (1) {
        printf("\nMenu:\n");
        printf("1. Set Fibonacci term (N)\n");
        printf("2. Set type of algorithm (0 for iterative, 1 for recursive, 2 for dynamic)\n");
        printf("3. Run analysis\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Fibonacci term (N): ");
                scanf("%d", &n);
                break;
            case 2:
                printf("Enter type of algorithm (0 for iterative, 1 for recursive, 2 for dynamic): ");
                scanf("%d", &call);
                break;
            case 3:
                analyze_execution(n, call);
                break;
            case 4:
                printf("Exiting...\n");
                free(fib_table); 
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    free(fib_table); 
    return 0;
}
