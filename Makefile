NAME=fdf

SRCS=main.c file.c utils.c landscape.c

CC=cc

CFLAGS=-Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean:

fclean:
	rm -f $(NAME)

re: fclean all 
