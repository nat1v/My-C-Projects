#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

int maze[MAX_SIZE][MAX_SIZE];
int visited[MAX_SIZE][MAX_SIZE];
int rows, cols;
int start_row, start_col;
int found_exit = 0;

// Directions: up, down, left, right
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

int is_valid(int r, int c) {
    return r >= 0 && r < rows && c >= 0 && c < cols;
}

void solve_maze(int r, int c) {
    // If we found an exit, stop searching
    if (found_exit) return;
    
    // Check if we reached the edge (exit)
    if (r == 0 || r == rows-1 || c == 0 || c == cols-1) {
        if (!(r == start_row && c == start_col)) { // Not the starting position
            printf("Exit found at: (%d, %d)\n", r, c);
            found_exit = 1;
            return;
        }
    }
    
    visited[r][c] = 1;
    
    // Try all four directions
    for (int i = 0; i < 4; i++) {
        int new_r = r + dr[i];
        int new_c = c + dc[i];
        
        if (is_valid(new_r, new_c) && 
            !visited[new_r][new_c] && 
            maze[new_r][new_c] != 1) { // Not a wall
            
            solve_maze(new_r, new_c);
        }
    }
}

void read_maze_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Cannot open file %s\n", filename);
        exit(1);
    }
    
    char line[1000];
    rows = 0;
    
    // Read the maze
    while (fgets(line, sizeof(line), file)) {
        cols = 0;
        char* token = strtok(line, ",");
        
        while (token != NULL) {
            maze[rows][cols] = atoi(token);
            token = strtok(NULL, ",");
            cols++;
        }
        rows++;
    }
    
    fclose(file);
    
    printf("Maze loaded: %d x %d\n", rows, cols);
    
    // Print the maze
    printf("Maze:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%2d ", maze[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    char filename[256];
    
    printf("=== Maze Escape Program ===\n");
    printf("Enter maze file name: ");
    scanf("%s", filename);
    
    // Read maze from file
    read_maze_from_file(filename);
    
    // Get starting position
    printf("Enter starting position (row col): ");
    scanf("%d %d", &start_row, &start_col);
    
    // Validate starting position
    if (!is_valid(start_row, start_col)) {
        printf("Invalid starting position!\n");
        return 1;
    }
    
    if (maze[start_row][start_col] == 1) {
        printf("Starting position is a wall!\n");
        return 1;
    }
    
    // Initialize visited array
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            visited[i][j] = 0;
        }
    }
    
    printf("Starting escape from position: (%d, %d)\n", start_row, start_col);
    
    // Solve the maze
    solve_maze(start_row, start_col);
    
    if (!found_exit) {
        printf("No exit found from the given position.\n");
    }
    
    return 0;
}
