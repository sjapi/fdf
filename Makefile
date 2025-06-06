# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: azolotar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/06 18:24:27 by azolotar          #+#    #+#              #
#    Updated: 2025/04/17 18:05:42 by azolotar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=fdf

# SOURCE
FILES=main.c file.c parse.c \
		draw.c menu.c ft_atoi_base.c \
		gradient.c utils1.c utils2.c

SRCS_DIR=./srcs/

SRCS=$(addprefix $(SRCS_DIR), $(FILES))

OBJS_DIR=./obj/

OBJS=$(addprefix $(OBJS_DIR), $(FILES:.c=.o))

INCLUDES_DIR=./includes/

# MINILIBX
MLX_DIR=./minilibx-linux/

MLX_LIB=$(addprefix $(MLX_DIR), libmlx_Linux.a)

# LIBFT
LIBFT_DIR=./libft/

LIBFT_LIB=$(addprefix $(LIBFT_DIR), libft.a)

# OTHER
CC=cc

CFLAGS=-Wall -Wextra -Werror

MLXFLAGS=-lX11 -lXext -lm
# RULES
all: ./obj $(LIBFT_LIB) $(MLX_LIB) $(NAME)

./obj:
	mkdir -p $(OBJS_DIR)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	$(CC) $(CFLAGS) -I $(MLX_DIR) -I $(LIBFT_DIR) -I $(INCLUDES_DIR) -o $@ -c $<

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_LIB) $(LIBFT_LIB) $(MLXFLAGS) -o $(NAME)

$(MLX_LIB):
	make -C $(MLX_DIR)

$(LIBFT_LIB):
	make -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJS_DIR)
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all 

.PHONY: all clean fclean re
