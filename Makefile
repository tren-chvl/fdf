NAME = fdf
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX = ./minilibx-linux/libmlx.a
LIBS = -lminilibx-linux -lmlx -lXext -lX11 -lm
SRCS =	fdf.c 
OBJS = $(SRCS:.c=.o)
INCLUDE = -I ./minilibx-linux
all: $(NAME)

$(NAME): $(OBJS)
	$(CC)  $(CFLAGS) -o $(NAME) $(OBJS) $(MLX) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re