#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Create fib table with given size
#define SIZE 50000
static long fib_table[SIZE];

/*
* Helper function to print fibonacci value at n.
* Params:
*   - i: int, fibonacci n
*   - val: int, val at fibonacci n
* Returns: None
*/
void print_line(int i, int val) {
    printf("fib(%d): %d\n", i, val);
}

/*
* Fibonacci iterative algorithm.
* Params:
*   - n: int, n element in fibonacci sequence
* Returns: int, fib value at n
*/
int fib_iterative(int n) {
    // Create first and second values
    int first = 0;
    int second = 1;
    int val;

    for (int i = 0; i < n; i++) {
        // Inital fib vals
        if (i <= 1) {
            val = i;
        } else {
            val = first + second; // fib value is sum of previous two
            first = second; // make first value equal to second
            second = val; // second value is now the just calculated fib_r val
        }
    }
    return val;
}

/*
* Fibonacci recursive algorithm.
* Params:
*   - n: int, n element in fibonacci sequence
* Returns: int, fib value at n
*/
int fib_recursive(int n) {
    // Inital fib vals
    if(n <= 1) {
        return n;
    }
    // fib of n>1 is fib(n-1) + fib(n-2)
    return fib_recursive(n-1) + fib_recursive(n-2);
}

/**
* Helper function to call within fibonacci dynamic programming algorithm.
* Params:
*   - n: n element in fibonacci sequence
* Retuns: int, value at n in fibonacci sequence
*/
unsigned long fib_d(int n) {
    // Inital fib vals
    if(n <= 1) {
        return n;
    // Return val from table if already stored
    } else if (fib_table[n] != -1){
        return fib_table[n];
    }
    // Store next val; fib of n>1 is fib(n-1) + fib(n-2)
    fib_table[n] = fib_d(n-1) + fib_d(n-2);
    return fib_table[n];
}

/*
* Fibonacci dynamic programming algorithm.
* Params:
*   - n: int, n element in fibonacci sequence
* Returns: int, fib value at n
*/
int fib_dynamic(int n) {
    // Initialize table
    for(int i = 0; i < SIZE; i++) {
        fib_table[i] = -1;
    }
    // Base case
    fib_table[0] = 0;
    fib_table[1] = 1;
    // Use dynamic fib function
    int val;
    for (int i = 0; i < n; i++) {
        val = fib_d(i);
    }
    return val;
}

/*
* Helper function to call specific fibonacci sequence algorithm.
* Params:
*   - n: int, n element of fibonacci sequence
*   - call: int, type of algorithm (0 iterative, 1 recursive, 2 dynamic)
* Returns: int, value at n of fibonacci sequence
*/
int call_helper(int n, int call) {
    // Call iterative function
    if(call == 0) {
        return fib_iterative(n);
    // Call recursive function
    } else if(call == 1) {
        return fib_recursive(n - 1);
    // Call dynamic function
    } else {
        return fib_dynamic(n);
    }
}

/*
* Function to analyze execution time of algorithms.
* Params: 
*   - n: int, number of iterations of fibonacci series.
*   - call: int, type of algorithm (0 iterative, 1 recursive, 2 dynamic).
*   - print: int, 0 for no print, 1 for print N val, 2 for print all calculations.
* Returns: None
*/
void analyze_execution(int n, int call, int print) {
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    int n_val = call_helper(n, call);
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    // Print
    if(print == 1) {
        print_line(n, n_val);
    }

    printf("Execution time: %f seconds\n", cpu_time_used);
}

/*
* Function to analyze execution time of algorithms for specific iterations.
* Params: None
* Returns: None
*/
void analyze_empiric() {
    int calls[] = {0, 1, 2}; // 0 for iterative, 1 for recursive, 2 for dynamic
    int iterations[] = {10, 15, 20, 25, 30, 35, 40};

    printf("Empiric Analysis:\n");
    for(int i = 0; i < sizeof(iterations)/sizeof(iterations[0]); i++) {
        for(int j = 0; j < sizeof(calls)/sizeof(calls[0]); j++) {
            printf("n = %d, Algorithm: %s\n", iterations[i], (calls[j] == 0 ? "Iterative" : (calls[j] == 1 ? "Recursive" : "Dynamic")));
            analyze_execution(iterations[i], calls[j], 1);
        }
    }
}

int main() {
    int choice, n = 0, call = 0, print = 0;

    while(1) {
        printf("Menu:\n");
        printf("1. Set number of iterations (N)\n");
        printf("2. Set type of algorithm (0 for iterative, 1 for recursive, 2 for dynamic)\n");
        printf("3. Set print option (0 for no print, 1 for print N val, 2 for print all calculations)\n");
        printf("4. Run analysis\n");
        printf("5. Empiric Analysis\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter number of iterations (N): ");
                scanf("%d", &n);
                break;
            case 2:
                printf("Enter type of algorithm (0 for iterative, 1 for recursive, 2 for dynamic): ");
                scanf("%d", &call);
                break;
            case 3:
                printf("Enter print option (0 for no print, 1 for print N val, 2 for print all calculations): ");
                scanf("%d", &print);
                break;
            case 4:
                analyze_execution(n, call, print);
                break;
            case 5:
                analyze_empiric();
                break;
            case 6:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
