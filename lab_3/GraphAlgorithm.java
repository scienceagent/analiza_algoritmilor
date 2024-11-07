import java.util.Scanner;
import java.util.Random;

public class GraphAlgorithm {
    static final int MAX = 10000;
    static final int INF = 10000;
    static int[][] MS = new int[MAX][MAX];
    static int[][] MV = new int[MAX][MAX];
    static int[][] MVprim = new int[MAX][MAX];
    static int[][] MVkruskal = new int[MAX][MAX];
    static int n;
    static int count1 = 0, count2 = 0;
    static int[] parent = new int[MAX];
    static int[] visited = new int[MAX];

    public static void reset() {
        count1 = 0;
        count2 = 0;
        for (int i = 0; i < n; i++) {
            parent[i] = 0;
            visited[i] = 0;
            for (int j = 0; j < n; j++) {
                MVprim[i][j] = MV[i][j];
                MVkruskal[i][j] = MV[i][j];
            }
        }
    }

    public static void nrVirfDefavorabil() {
        System.out.print("Numarul de virfuri: ");
        Scanner sc = new Scanner(System.in);
        n = sc.nextInt();
        Random rand = new Random();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (j > i) {
                    MS[i][j] = rand.nextInt(10000);
                } else if (i > j) {
                    MS[i][j] = MS[j][i];
                } else {
                    MS[i][j] = 0;
                }
            }
        }
    }

    public static void costurileDefavorabil() {
        System.out.println("Costurile muchiilor:");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (MS[i][j] != 0 && i != j) {
                    MV[i][j] = MS[i][j];
                } else {
                    MV[i][j] = INF;
                }
            }
        }
        reset();
    }

    public static void nrVirfFavorabil() {
        System.out.print("Numarul de virfuri: ");
        Scanner sc = new Scanner(System.in);
        n = sc.nextInt();
        Random rand = new Random();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    MS[i][j] = rand.nextInt(1000) + 1;
                } else {
                    MS[i][j] = 0;
                }
            }
        }
    }

    public static void costurileFavorabil() {
        System.out.println("Costurile muchiilor:");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (MS[i][j] != 0 && i != j) {
                    MV[i][j] = MS[i][j];
                } else {
                    MV[i][j] = INF;
                }
            }
        }
        reset();
    }

    public static void nrVirfMediu() {
        System.out.print("Numarul de virfuri: ");
        Scanner sc = new Scanner(System.in);
        n = sc.nextInt();
        Random rand = new Random();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (j > i) {
                    MS[i][j] = rand.nextInt(1000) + 1;
                    MS[j][i] = MS[i][j];
                } else if (i == j) {
                    MS[i][j] = 0;
                }
            }
        }
    }

    public static void costurileMediu() {
        System.out.println("Costurile muchiilor:");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (MS[i][j] != 0 && i != j) {
                    System.out.println((i + 1) + " -> " + (j + 1) + " : " + MS[i][j]);
                    MV[i][j] = MS[i][j];
                } else {
                    MV[i][j] = INF;
                }
            }
        }
        reset();
    }

    public static int find(int i) {
        if (parent[i] == 0) return i;
        return parent[i] = find(parent[i]);
    }

    public static boolean union(int i, int j) {
        if (i != j) {
            parent[j] = i;
            return true;
        }
        return false;
    }

    public static void prim() {
        int a = -1, b = -1, u = -1, v = -1, ne = 1, min;
        visited[0] = 1;
        System.out.println("Algoritmul lui Prim:\n");
        long startTime = System.nanoTime();

        while (ne < n) {
            count1++;
            min = INF;
            for (int i = 0; i < n; i++) {
                if (visited[i] == 1) {
                    for (int j = 0; j < n; j++) {
                        if (MVprim[i][j] < min && visited[j] == 0) {
                            count1++;
                            min = MVprim[i][j];
                            a = i;
                            b = j;
                        }
                    }
                }
            }

            if (visited[b] == 0) {
                System.out.println("Muchia " + (ne++) + ": " + (a + 1) + " -> " + (b + 1) + ", costul = " + min);
                visited[b] = 1;
            }
            MVprim[a][b] = MVprim[b][a] = INF;
        }

        long endTime = System.nanoTime();
        double executionTime = (endTime - startTime) / 1_000_000_000.0;
        System.out.println("\nNr. Iteratii: " + count1);
        System.out.printf("Timpul de executie: %.6f secunde\n", executionTime);
    }
    

    public static void kruskal() {
        int a = -1, b = -1, u = -1, v = -1, ne = 1, min;
        System.out.println("Algoritmul Kruskal:\n");
        long startTime = System.nanoTime();

        while (ne < n) {
            count2++;
            min = INF;

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (MVkruskal[i][j] < min) {
                        count1++;
                        min = MVkruskal[i][j];
                        a = i;
                        b = j;
                    }
                }
            }

            u = find(a);
            v = find(b);
            if (union(u, v)) {
                System.out.println("Muchia " + (ne++) + ": " + (a + 1) + " -> " + (b + 1) + ", costul = " + min);
            }
            MVkruskal[a][b] = MVkruskal[b][a] = INF;
        }

        long endTime = System.nanoTime();
        double executionTime = (endTime - startTime) / 1_000_000_000.0;
        System.out.println("\nNr. Iteratii: " + count2);
        System.out.printf("Timpul de executie: %.6f secunde\n", executionTime);
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Random rand = new Random();
        int chooseMenu;
        while (true) {
            System.out.println("1. Cazul favorabil.");
            System.out.println("2. Cazul mediu.");
            System.out.println("3. Cazul defavorabil.");
            System.out.println("0. Stop Program.");
            System.out.print("Raspuns: ");
            chooseMenu = sc.nextInt();

            switch (chooseMenu) {
                case 1 -> {
                    nrVirfFavorabil();
                    costurileFavorabil();
                    prim();
                    kruskal();
                }
                case 2 -> {
                    nrVirfMediu();
                    costurileMediu();
                    prim();
                    kruskal();
                }
                case 3 -> {
                    nrVirfDefavorabil();
                    costurileDefavorabil();
                    prim();
                    kruskal();
                }
                case 0 -> System.exit(0);
                default -> System.out.println("ERROR");
            }
        }
    }
}
