NAME	= apue

CC = gcc
CFLAGS	= # -Wall -Werror -Wextra
RM = rm -rf


SRCS =  cpyerr_sys.c \
		cpyexec.c \
		# cpywait.c \


OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re:
	make fclean
	make all

.PHONY: all clean fclean re