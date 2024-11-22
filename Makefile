LIBFT_DIR = ./libft
MLX_DIR	= ./minilibx-linux
SRC_DR = ./src
LIBFT = $(LIBFT_DIR)/libft.a
MINILIBX = $(MLX_DIR)

SRCS = main.c drawing_algorithm.c
SRCS:= $(addprefix $(SRC_DR)/, $(SRCS))
OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lX11 -lXext -lm -I. -g3

NAME = fdf

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(CFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MINILIBX) clean
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(MINILIBX) clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
