#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <locale.h>

#define V 100 // Numărul de noduri
#define MAX_WEIGHT 20 // Greutatea maximă a unui arc

int it = 0;

// Funcția pentru generarea fișierelor
void generateGraphFile(const char *filename, int isDense) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        perror("Eroare la crearea fișierului");
        exit(1);
    }

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i == j) {
                fprintf(f, "0 "); // Diagonală: fără arc (cost 0)
            } else {
                int random = rand() % 100; // Valoare aleatorie pentru densitate
                if (isDense) {
                    // Graf dens: șanse mari să existe un arc
                    fprintf(f, "%d ", (random < 90) ? (rand() % MAX_WEIGHT + 1) : 0);
                } else {
                    // Graf rar: șanse mici să existe un arc
                    fprintf(f, "%d ", (random < 20) ? (rand() % MAX_WEIGHT + 1) : 0);
                }
            }
        }
        fprintf(f, "\n");
    }

    fclose(f);
}

// Algoritmul Dijkstra
void Dijkstra(int GR[V][V], int st) {
    int distance[V], visited[V];
    int i, count, u, min, index;

    for (i = 0; i < V; i++) {
        distance[i] = INT_MAX; // Inițializare distanțe la infinit
        visited[i] = 0;        // Niciun vârf nu este vizitat
    }

    distance[st] = 0; // Distanța către sine este 0

    for (count = 0; count < V - 1; count++) {
        min = INT_MAX;

        // Găsește nodul cu cea mai mică distanță
        for (i = 0; i < V; i++) {
            if (!visited[i] && distance[i] <= min) {
                min = distance[i];
                index = i;
            }
        }

        u = index; // Vârful curent
        visited[u] = 1;

        // Actualizează distanțele pentru vecinii nevizitați
        for (i = 0; i < V; i++) {
            it++;
            if (!visited[i] && GR[u][i] && distance[u] != INT_MAX &&
                distance[u] + GR[u][i] < distance[i]) {
                distance[i] = distance[u] + GR[u][i];
            }
        }
    }

    printf("Costul din vârful inițial până în restul vârfurilor:\n");
    printf("-----------\n");
    for (i = 0; i < V; i++) {
        if (distance[i] != INT_MAX)
            printf("%d -> %d = %d\n", st + 1, i + 1, distance[i]);
        else
            printf("%d -> %d = inaccesibil\n", st + 1, i + 1);
    }
    printf("-----------\n");
}

int main() {
    setlocale(LC_ALL, ""); // Setează localizarea pentru afișare
    clock_t start, end;
    int GR[V][V];
    int i, j, x;

    srand(time(NULL)); // Inițializare generator random

    // Generarea fișierelor
    generateGraphFile("gdes.txt", 1); // Graf dens
    generateGraphFile("grar.txt", 0); // Graf rar

    // Alegerea fișierului de utilizat
    printf("Se va utiliza matricea din fișierul gdes.txt (graf dens).\n");
    FILE *f = fopen("grar.txt", "r");
    if (f == NULL) {
        perror("Eroare la deschiderea fișierului");
        return 1;
    }

    // Citirea matricei de adiacență
    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {
            if (fscanf(f, "%d", &x) != 1) {
                perror("Eroare la citirea fișierului");
                fclose(f);
                return 1;
            }
            GR[i][j] = x;
        }
    }
    fclose(f);

    // Rulează Dijkstra pentru fiecare vârf
    start = clock();
    for (i = 0; i < V; i++) {
        Dijkstra(GR, i);
    }
    end = clock();

    // Timpul de execuție
    printf("\n\nTimpul de execuție este: %.8f secunde\n", ((double)(end - start)) / CLOCKS_PER_SEC);
    printf("Număr de iterații: %d\n", it);

    return 0;
}
