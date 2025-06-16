#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Module A1: Maze Escape Program
#define MAX_SIZE 100

int maze[MAX_SIZE][MAX_SIZE];
int visited[MAX_SIZE][MAX_SIZE];
int rows, cols;
int start_row, start_col;

// Directions: up, down, left, right
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int is_valid(int x, int y) {
    return (x >= 0 && x < rows && y >= 0 && y < cols && 
            maze[x][y] != 1 && !visited[x][y]);
}

int is_edge(int x, int y) {
    return (x == 0 || x == rows-1 || y == 0 || y == cols-1);
}

int solve_maze(int x, int y) {
    // Mark current cell as visited
    visited[x][y] = 1;
    
    // If we reached an edge (except starting position), we found exit
    if (is_edge(x, y) && !(x == start_row && y == start_col)) {
        printf("Exit found at: (%d, %d)\n", x, y);
        return 1;
    }
    
    // Try all four directions
    for (int i = 0; i < 4; i++) {
        int new_x = x + dx[i];
        int new_y = y + dy[i];
        
        if (is_valid(new_x, new_y)) {
            if (solve_maze(new_x, new_y)) {
                return 1;
            }
        }
    }
    
    // Backtrack
    visited[x][y] = 0;
    return 0;
}

void read_maze_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Cannot open file %s\n", filename);
        return;
    }
    
    char line[1000];
    rows = 0;
    
    while (fgets(line, sizeof(line), file)) {
        cols = 0;
        char* token = strtok(line, ", \n");
        
        while (token != NULL) {
            maze[rows][cols] = atoi(token);
            token = strtok(NULL, ", \n");
            cols++;
        }
        rows++;
    }
    
    fclose(file);
}

void print_maze() {
    printf("Maze layout:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%2d ", maze[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void module_a1() {
    char filename[100];
    
    printf("=== Module A1: Maze Escape Program ===\n");
    printf("Enter maze file name: ");
    scanf("%s", filename);
    
    read_maze_from_file(filename);
    
    if (rows == 0 || cols == 0) {
        printf("Error: Invalid maze file\n");
        return;
    }
    
    print_maze();
    
    printf("Enter starting coordinates (row col): ");
    scanf("%d %d", &start_row, &start_col);
    
    if (start_row < 0 || start_row >= rows || start_col < 0 || start_col >= cols) {
        printf("Error: Invalid starting coordinates\n");
        return;
    }
    
    if (maze[start_row][start_col] == 1) {
        printf("Error: Starting position is a wall\n");
        return;
    }
    
    // Initialize visited array
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            visited[i][j] = 0;
        }
    }
    
    printf("Starting from position: (%d, %d)\n", start_row, start_col);
    
    if (solve_maze(start_row, start_col)) {
        printf("Escape route found!\n");
    } else {
        printf("No escape route found.\n");
    }
}


void read_string_from_file(const char* filename, char* str) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Cannot open file %s\n", filename);
        return;
    }
    
    if (fgets(str, 100, file)) {
        // Remove newline if present
        str[strcspn(str, "\n")] = 0;
        // Remove spaces and commas, keep only letters
        int write_pos = 0;
        for (int read_pos = 0; str[read_pos]; read_pos++) {
            if ((str[read_pos] >= 'A' && str[read_pos] <= 'Z') ||
                (str[read_pos] >= 'a' && str[read_pos] <= 'z')) {
                str[write_pos++] = str[read_pos];
            }
        }
        str[write_pos] = '\0';
    }
    
    fclose(file);
}



int main() {
    int choice;
    
    
      
        printf("Module - Maze Escape\n");
     
        
       
                module_a1();
               
    
    return 0;
}

/* 
Example maze file content (save as maze.txt):
-1,-1,-1,-1,-1,-1
0,0,0,0,1,-1
-1,1,0,0,0,0
-1,-1,-1,-1,-1,-1

Example string file content (save as string.txt):
A, B, C
*/
