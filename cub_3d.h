/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emikhayl <emikhayl@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 19:29:42 by emikhayl          #+#    #+#             */
/*   Updated: 2023/11/30 23:22:22 by emikhayl         ###   ########.fr       */
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
#  define BUFFER_SIZE 42
# endif

//** STRUCTS */
typedef struct s_textures {
    char *NO;  // Path to the texture file
    char *SO;
    char *WE;
    char *EA;
} t_textures;

typedef struct s_color{
    char location;  // Floor or Ceiling
    int r;
    int g;
    int b;
} t_color;



//**FOR GET NEXT LINE */
char	*get_free(char **str1);
char	*extract_line(char *buffer);
char	*update_storage(char *buffer);
char	*read_from_file(int fd, char *persistent_buffer);
char	*get_next_line(int fd);

//** PARSING */
char* getFilename(int arg, char **argv);
int errOpen(char *file);
int is_empty_or_whitespace(char *str);

#endif
