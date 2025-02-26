CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -L./libft -lft 
INCLUDES = -I./libft -I.

SRC = main.c
OBJ = $(SRC:.c=.o)
NAME = cub3D

all: libs $(NAME)

libs:
	make -C ./libft
	make -C ./get_next_line

$(NAME): $(OBJ) ./libft/libft.a
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)

%.o: %.c Makefile minishell.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	make -C ./libft clean
	make -C ./get_next_line clean
	$(RM) $(OBJ)

fclean: clean
	make -C ./libft fclean
	make -C ./get_next_line fclean
	$(RM) $(NAME)

re: fclean all


.PHONY: all clean fclean re libs