#include <stdio.h>

#define WALL '1'
#define EMPTY '0'

// Flood fill function
int flood_fill(char **map, int x, int y, int rows, int cols) {
    // If out of bounds, map is open
    if (x < 0 || y < 0 || x >= rows || y >= cols)
        return 0;

    // If we hit a wall, stop
    if (map[x][y] == WALL)
        return 1;

    // Temporarily change the value to avoid infinite loops
    char temp = map[x][y];
    map[x][y] = WALL; // Simulate "visited" without permanent change

    // Explore all directions
    int up = flood_fill(map, x - 1, y, rows, cols);
    int down = flood_fill(map, x + 1, y, rows, cols);
    int left = flood_fill(map, x, y - 1, rows, cols);
    int right = flood_fill(map, x, y + 1, rows, cols);

    // Restore the original value
    map[x][y] = temp;

    // If any direction leads outside, map is open
    return up && down && left && right;
}

// Wrapper function to check if map is closed
int is_map_closed(char **map, int x, int y, int rows, int cols) {
    return flood_fill(map, x, y, rows, cols);
}

// Example usage
int main() {
    char *map[] = {
        "111111",
        "100001",
        "101101",
        "100001",
        "111111"
    };

    int rows = 5, cols = 6;
    int start_x = 2, start_y = 2; // Starting point inside the map

    if (is_map_closed(map, start_x, start_y, rows, cols))
        printf("✅ The map is closed!\n");
    else
        printf("❌ The map is NOT closed!\n");

    return 0;
}
