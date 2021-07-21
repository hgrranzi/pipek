NAME = pipek

COMPILE = gcc # -Wall -Wextra -Werror

SRCS = main.c take_data.c utils.c

OBJS =	$(SRCS:.c=.o)

all: $(NAME)

$(NAME): pipek.h $(OBJS)
	$(COMPILE) $(OBJS) -o $(NAME)

%.o: %.c pipek.h
	$(COMPILE) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
