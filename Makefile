CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -L./libft -lft 
INCLUDES = -I./libft -I.

SRC = main.c get_next_line.c helper_input.c helper_errors.c struct_init.c \
	handle_map.c flood_fill.c
OBJ = $(SRC:.c=.o)
NAME = cub3D

all: libs $(NAME)

libs:
	make -C ./libft
	
$(NAME): $(OBJ) ./libft/libft.a
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)

%.o: %.c Makefile cub_3d.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	make -C ./libft clean
	$(RM) $(OBJ)

fclean: clean
	make -C ./libft fclean
	$(RM) $(NAME)

re: fclean all


.PHONY: all clean fclean re libs