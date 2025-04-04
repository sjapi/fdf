NAME=fdf

SRCS=main.c file.c utils.c landscape.c get_next_line.c get_next_line_utils.c

CC=cc

CFLAGS=-Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean:

fclean:
	clear
	rm -f $(NAME)

re: fclean all 
