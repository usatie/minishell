SRC = 

####### commands #######
CC = gcc
WWW = -Wall -Wextra -Werror

RM = rm -f
OBJS = $(SRCS:.c=.o)

####### subject #######
all: $(NAME)

$(NAME): $(OBJS)
    $(CC) $(WWWF)  $^ -o $@
    # ar rcs $(NAME) $(SL_OBJS)

%.o:%.c
    $(CC) $(WWW) -c $< -o $@

clean:
    $(RM) $(OBJS)

fclean: clean
    $(RM) $(NAME)

re:
    make fclean
    make all

.PHONY: all clean fclean re%
