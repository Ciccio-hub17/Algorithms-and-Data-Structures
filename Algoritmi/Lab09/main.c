#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_N 30
#define MAX_S 31

typedef struct { int u, v, wt; } Edge;

int N, E = 0;
char names[MAX_N][MAX_S];
int adj[MAX_N][MAX_N];
Edge edges[MAX_N * MAX_N];
int removed[MAX_N * MAX_N];

// Array to store ALL minimum cardinality sets
typedef struct {
    int removed_edges[MAX_N * MAX_N];
    int total_weight;
} MinimalSet;

MinimalSet minimal_sets[10000]; // Array to store all sets
int num_sets_found = 0;
int min_cardinality = -1;

int check_cycle(int v, int *visited, int *stack) {
    visited[v] = 1; 
    stack[v] = 1;
    for (int w = 0; w < N; w++) {
        if (adj[v][w] != -1) {
            if (!visited[w] && check_cycle(w, visited, stack)) return 1;
            else if (stack[w]) return 1; // Found back edge
        }
    }
    stack[v] = 0; 
    return 0;
}

int is_dag() {
    int visited[MAX_N] = {0}, stack[MAX_N] = {0};
    for (int i = 0; i < N; i++)
        if (!visited[i] && check_cycle(i, visited, stack)) return 0;
    return 1;
}

void find_fas(int start, int k, int current_k) {
    if (current_k == k) {
        if (is_dag()) {
            // Calculate weight of current set
            int current_weight = 0;
            for (int i = 0; i < E; i++) 
                if (removed[i]) current_weight += edges[i].wt;
            
            // Store this set
            if (num_sets_found < 10000) {
                for (int i = 0; i < E; i++) {
                    minimal_sets[num_sets_found].removed_edges[i] = removed[i];
                }
                minimal_sets[num_sets_found].total_weight = current_weight;
                num_sets_found++;
            }
        }
        return;
    }
    
    // Explore combinations of edges to remove
    for (int i = start; i <= E - (k - current_k); i++) {
        int u = edges[i].u, v = edges[i].v, w = edges[i].wt;
        adj[u][v] = -1; // Temporarily remove
        removed[i] = 1;
        find_fas(i + 1, k, current_k + 1);
        adj[u][v] = w;  // Restore
        removed[i] = 0;
    }
}

void topological_sort(int v, int *visited, int *stack, int *pos) {
    visited[v] = 1;
    for (int w = 0; w < N; w++)
        if (adj[v][w] != -1 && !visited[w]) 
            topological_sort(w, visited, stack, pos);
    stack[(*pos)--] = v;
}

void calculate_distances() {
    int visited[MAX_N] = {0}, stack[MAX_N], pos = N - 1;
    

    for (int i = 0; i < N; i++) 
        if (!visited[i]) 
            topological_sort(i, visited, stack, &pos);
    
    printf("Calculating maximum distances\n");

    
    // For each possible source node
    for (int s = 0; s < N; s++) {
        int dist[MAX_N];
        for (int i = 0; i < N; i++) dist[i] = INT_MIN; 
        dist[s] = 0;
        
        // Calculate distances following topological order
        for (int i = 0; i < N; i++) {
            int u = stack[i];
            if (dist[u] != INT_MIN) {
                for (int v = 0; v < N; v++) {
                    if (adj[u][v] != -1) {
                        if (dist[u] + adj[u][v] > dist[v])
                            dist[v] = dist[u] + adj[u][v];
                    }
                }
            }
        }
        
        // Print results
        printf("\nSource %s:\n", names[s]);
        for (int i = 0; i < N; i++) {
            if (dist[i] == INT_MIN) 
                printf("  -> %s: unreachable\n", names[i]);
            else 
                printf("  -> %s: %d\n", names[i], dist[i]);
        }
    }
}

// Function to print a set of edges
void print_set(MinimalSet *set, int index) {
    printf("Set %d (total weight: %d):\n", index + 1, set->total_weight);
    printf("  Edges to remove: ");
    int first = 1;
    for (int i = 0; i < E; i++) {
        if (set->removed_edges[i]) {
            if (!first) printf(", ");
            printf("%s->%s(%d)", names[edges[i].u], names[edges[i].v], edges[i].wt);
            first = 0;
        }
    }
    printf("\n");
}

// Function to print the DAG
void print_dag() {
    printf("\nResulting DAG:\n");
    for (int i = 0; i < N; i++) {
        int has_edges = 0;
        for (int j = 0; j < N; j++) {
            if (adj[i][j] != -1) has_edges = 1;
        }
        if (has_edges) {
            printf("  %s:", names[i]);
            for (int j = 0; j < N; j++) {
                if (adj[i][j] != -1) {
                    printf(" -> %s(%d)", names[j], adj[i][j]);
                }
            }
            printf("\n");
        }
    }
}

int main() {
    FILE *f = fopen("grafo4.txt", "r");
    if (!f) {
        fprintf(stderr, "Error: cannot open grafo.txt\n");
        return 1;
    }
    
    // Reading the graph
    fscanf(f, "%d", &N);
    for (int i = 0; i < N; i++) {
        fscanf(f, "%s", names[i]);
        for (int j = 0; j < N; j++) adj[i][j] = -1;
    }
    
    char s1[MAX_S], s2[MAX_S]; 
    int wt;
    while (fscanf(f, "%s %s %d", s1, s2, &wt) == 3) {
        int u = -1, v = -1;
        for (int i = 0; i < N; i++) {
            if (strcmp(names[i], s1) == 0) u = i;
            if (strcmp(names[i], s2) == 0) v = i;
        }
        if (u != -1 && v != -1) {
            adj[u][v] = wt;
            edges[E].u = u; 
            edges[E].v = v; 
            edges[E].wt = wt;
            E++;
        }
    }
    
    
    printf("Original graph loaded:\n");
    printf("  Nodes: %d\n", N);
    printf("  Edges: %d\n\n", E);
    for (int i = 0; i < N; i++) {
        int has_edges = 0;
        for (int j = 0; j < N; j++) {
            if (adj[i][j] != -1) has_edges = 1;
        }
        if (has_edges) {
            printf("  %s:", names[i]);
            for (int j = 0; j < N; j++) {
                if (adj[i][j] != -1) {
                    printf(" -> %s(%d)", names[j], adj[i][j]);
                }
            }
            printf("\n");
        }
    }
    printf("\n");
    
    printf("Identifying minimal sets\n");
    
    
    if (is_dag()) {
        printf("The graph is already a DAG, no need to remove edges.\n");
    } else {
        printf("Searching for ALL minimum cardinality sets...\n\n");
        
        // Search by increasing cardinality until sets are found
        for (int k = 1; k <= E; k++) {
            int sets_before = num_sets_found;
            find_fas(0, k, 0);
            
            if (num_sets_found > sets_before) {
                // Found minimum cardinality
                min_cardinality = k;
                printf("Minimum cardinality found: %d edges\n", min_cardinality);
                printf("Total number of sets: %d\n\n", num_sets_found);
                break;
            }
        }
        
        // Show all found sets
        if (num_sets_found > 0) {
            printf("List of all sets:\n");
            printf("----------------------------\n");
            for (int i = 0; i < num_sets_found; i++) {
                print_set(&minimal_sets[i], i);
            }
        }
        
        printf("\n");
        printf("Building maximum weight DAG\n");
        
        
        int max_weight_idx = 0;
        int max_weight = minimal_sets[0].total_weight;
        
        for (int i = 1; i < num_sets_found; i++) {
            if (minimal_sets[i].total_weight > max_weight) {
                max_weight = minimal_sets[i].total_weight;
                max_weight_idx = i;
            }
        }
        
        printf("Chosen set (maximum weight = %d):\n", max_weight);
        print_set(&minimal_sets[max_weight_idx], max_weight_idx);
        
        // Apply definitive removal
        for (int i = 0; i < E; i++) {
            if (minimal_sets[max_weight_idx].removed_edges[i]) {
                adj[edges[i].u][edges[i].v] = -1;
            }
        }
        
        print_dag();
    }
    
    calculate_distances();
    
    fclose(f);
    
    return 0;
}