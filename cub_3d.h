/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emikhayl <emikhayl@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 19:29:42 by emikhayl          #+#    #+#             */
/*   Updated: 2025/04/02 19:38:19 by emikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_3D_H
# define CUB_3D_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# ifndef MAP_SIZE
#define MAP_SIZE 50
# endif

//** STRUCTS */
typedef struct s_location{
    int r;
    int g;
    int b;
} t_location;

typedef struct s_point{
    int x;
    int y;
} t_point;

typedef struct s_player{
    char dir;
    t_point pos;
} t_player;

typedef struct s_data {
    char *NO;  // ./path_to_the_north_texture
    char *SO;
    char *WE;
    char *EA;

    t_location F;
    t_location C;

    int filled; // 6 filled all data exept map, map goes last
    
    int inside; //flag for map checking

    size_t rows; //number of rows
    size_t cols; //str len

    char **map;

    t_player me;
} t_data;



//**FOR GET NEXT LINE */
char	*get_next_line(int fd);

//** PARSING */
char* get_filename(int arg, char **argv);
int err_open(char *file);
int is_empty_or_whitespace(char *str);
int	ft_isspace(char c);
char	**ft_split_global(const char *s, char c);

//** STRUCT INIT */
void inputDataInit(t_data *data);
void free_data(t_data *data);
void free_arr(char **arr);

//* MAP HANDLING
int map_is_valid(const t_data data);
int normalize_map(t_data *data);
int trim_empty_lines(t_data *data);
int is_map_closed(t_data *data);

#endif
