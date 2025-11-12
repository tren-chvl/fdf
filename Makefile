NAME = fdf
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS =	fdf.c \
		read_fdf.c \
		ft_split.c \
		ft_utils.c \
		get_next_line.c \
		get_next_line_utils.c \
		ft_printf/ft_addr.c \
		ft_printf/ft_auxilliere1.c \
		ft_printf/ft_auxilliere2.c \
		ft_printf/ft_hexa_unsigned.c \
		ft_printf/ft_printf.c \
		ft_printf/ft_put.c \
		ft_printf/ft_putnbr.c \
		ft_printf/ft_putstr.c 
OBJS = $(SRCS:.c=.o)
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS)$(SRCS) -lXext -Lminilibx-linux -lmlx_Linux -Iminilibx-linux -lX11 -lm -lz -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re


