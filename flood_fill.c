#include <stdio.h>

#define WALL '1'
#define EMPTY '0'

// Flood fill function (corrected)
int flood_fill(char **map, int x, int y, int rows, int cols, int **visited) {
    // If out of bounds, the map is open
    if (x < 0 || y < 0 || x >= rows || y >= cols)
        return 0;

    // If we hit a wall or visited cell, stop
    if (map[x][y] == WALL || visited[x][y])
        return 1;

    // Mark as visited
    visited[x][y] = 1;

    // Explore all directions
    int up = flood_fill(map, x - 1, y, rows, cols, visited);
    int down = flood_fill(map, x + 1, y, rows, cols, visited);
    int left = flood_fill(map, x, y - 1, rows, cols, visited);
    int right = flood_fill(map, x, y + 1, rows, cols, visited);

    // If any direction leads outside, the map is open
    return up && down && left && right;
}

// Wrapper function
int is_map_closed(char **map, int x, int y, int rows, int cols) {
    // Create a visited array
    int visited[rows][cols];
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            visited[i][j] = 0;

    return flood_fill(map, x, y, rows, cols, (int **)visited);
}

int main() {
    char *map[] = {
        "001111",
        "000000",
        "101101",
        "100001",
        "111111"
    };

    int rows = 5, cols = 6;
    int start_x = 2, start_y = 2;

    if (is_map_closed(map, start_x, start_y, rows, cols))
        printf("✅ The map is closed!\n");
    else
        printf("❌ The map is NOT closed!\n");

    return 0;
}