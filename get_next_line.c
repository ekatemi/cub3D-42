#include "cub_3d.h"
#include "./libft/libft.h"
#include <string.h>

/**
 * Safely frees memory and returns NULL
 */
static char *safe_free(char **ptr)
{
    if (ptr && *ptr)
    {
        free(*ptr);
        *ptr = NULL;
    }
    return (NULL);
}

/**
 * Extract a line from the buffer (up to and including newline if present)
 */
static char *extract_line(const char *buffer)
{
    size_t line_len = 0;
    char *line;
    
    if (!buffer || buffer[0] == '\0')
        return (NULL);
    
    // Find the end of the line
    while (buffer[line_len] && buffer[line_len] != '\n')
        line_len++;
    
    // Include the newline if present
    if (buffer[line_len] == '\n')
        line_len++;
    
    // Allocate and copy the line
    line = malloc(sizeof(char) * (line_len + 1));
    if (!line)
        return (NULL);
    
    ft_memcpy(line, buffer, line_len);
    line[line_len] = '\0';
    
    return (line);
}

/**
 * Update the storage buffer after extracting a line
 * Returns a new buffer with the remaining content
 */
static char *update_storage(char *buffer)
{
    char *newline_pos;
    char *new_buffer;
    
    if (!buffer)
        return (NULL);
    
    newline_pos =  ft_strchr(buffer, '\n');
    if (!newline_pos)
    {
        // No more newlines - we've consumed the entire buffer
        safe_free(&buffer);
        return (NULL);
    }
    
    // Create a new buffer with the remaining content after the newline
    new_buffer =  ft_strdup(newline_pos + 1);
    safe_free(&buffer);
    
    return (new_buffer);
}

/**
 * Read from file and append to buffer until newline or EOF
 */
static char *read_file_chunk(int fd, char *buffer)
{
    char chunk[BUFFER_SIZE + 1];
    ssize_t bytes_read;
    char *temp;
    
    if (fd < 0)
        return (safe_free(&buffer));
    
    if (!buffer)
    {
        buffer = malloc(1);
        if (!buffer)
            return (NULL);
        buffer[0] = '\0';
    }
    
    // Read until we find a newline or reach EOF
    while (! ft_strchr(buffer, '\n') && 
           (bytes_read = read(fd, chunk, BUFFER_SIZE)) > 0)
    {
        chunk[bytes_read] = '\0';
        
        // Join the new chunk with existing buffer
        temp = malloc(ft_strlen(buffer) + bytes_read + 1);
        if (!temp)
            return (safe_free(&buffer));
        
        strcpy(temp, buffer);
        strcat(temp, chunk);
        
        safe_free(&buffer);
        buffer = temp;
    }
    
    // Handle read error
    if (bytes_read < 0)
        return (safe_free(&buffer));
    
    return (buffer);
}

/**
 * Get the next line from a file descriptor
 */
char *get_next_line(int fd)
{
    static char *storage = NULL;
    char *line;
    
    // Validate input
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    
    // Read from file until we have a complete line or reach EOF
    storage = read_file_chunk(fd, storage);
    if (!storage || storage[0] == '\0')
        return (safe_free(&storage));
    
    // Extract the current line
    line = extract_line(storage);
    if (!line)
        return (safe_free(&storage));
    
    // Update storage for next call
    storage = update_storage(storage);
    
    return (line);
}
