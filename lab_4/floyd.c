#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define maxV 1000

int i, j, n;
int it = 0;
int GR[maxV][maxV];

// Funcția pentru generarea fișierelor (graf dens și graf rar)
void generateGraphFile(const char *filename, int isDense) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        perror("Eroare la crearea fișierului");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                fprintf(f, "0 "); // Diagonală: fără arc (cost 0)
            } else {
                int random = rand() % 100; // Valoare aleatorie pentru densitate
                if (isDense) {
                    // Graf dens: șanse mari să existe un arc
                    fprintf(f, "%d ", (random < 90) ? (rand() % 20 + 1) : 0);
                } else {
                    // Graf rar: șanse mici să existe un arc
                    fprintf(f, "%d ", (random < 20) ? (rand() % 20 + 1) : 0);
                }
            }
        }
        fprintf(f, "\n");
    }

    fclose(f);
}

// Algoritmul Floyd-Warshall
void FU(int D[][maxV], int V) {
    int k;

    // Inițializare: diagonală principală cu 0
    for (i = 0; i < V; i++) {
        D[i][i] = 0;
    }

    // Algoritmul propriu-zis
    for (k = 0; k < V; k++) {
        for (i = 0; i < V; i++) {
            for (j = 0; j < V; j++) {
                it++;
                if (D[i][k] && D[k][j] && i != j) {
                    if (D[i][k] + D[k][j] < D[i][j] || D[i][j] == 0) {
                        D[i][j] = D[i][k] + D[k][j];
                    }
                }
                it++;
            }
        }
    }

    // Afișarea matricei drumurilor minime
    printf("\nMatricea Drumurilor Minime:\n");
    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {
            if (D[i][j] == 0 && i != j)
                printf("INF\t");
            else
                printf("%d\t", D[i][j]);
        }
        printf("\n");
    }
}

int main() {
    setlocale(LC_ALL, "");
    clock_t start, end;

    n = 250; // Numărul de noduri
    int x;

    // Generarea fișierelor
    generateGraphFile("gdes.txt", 1); // Graf dens
    generateGraphFile("grar.txt", 0); // Graf rar

    // Citirea din fișier
    FILE *f = fopen("grar.txt", "r");
    if (f == NULL) {
        perror("Eroare la deschiderea fișierului");
        return 1;
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (fscanf(f, "%d", &x) != 1) {
                perror("Eroare la citirea fișierului");
                fclose(f);
                return 1;
            }
            GR[i][j] = x;
        }
    }
    fclose(f);

    // Calcularea și afișarea drumurilor minime
    printf("\tFloyd-Warshall:\n");
    printf("--------------------------------------------\n");
    start = clock();
    FU(GR, n);
    end = clock();
    printf("--------------------------------------------\n");

    // Timpul de execuție și numărul de iterații
    printf("\n\nTimpul de execuție este: %.8f secunde\n", ((double)(end - start)) / CLOCKS_PER_SEC);
    printf("Număr de iterații: %d\n", it);

    return 0;
}
