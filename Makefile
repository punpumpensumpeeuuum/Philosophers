NAME = philo

SRCS = main.c inithelp.c setvals.c philos.c

CC = cc

CFLAGS = -Wall -Werror -Wextra

RM = rm -f

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME):
		@$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean:
		@$(RM) $(OBJ)

fclean:	clean
		@$(RM) $(NAME)
		@echo "apagou"

re:	fclean $(NAME)
		@echo "makou outra vez"
