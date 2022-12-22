# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/06 07:33:20 by susami            #+#    #+#              #
#    Updated: 2022/12/22 18:41:23 by susami           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -MMD -MP
INCLUDE	=	-I include
M_SRCS	=	ft_isalpha.c	\
			ft_isdigit.c	\
			ft_isalnum.c	\
			ft_isascii.c	\
			ft_isprint.c	\
			ft_strlen.c		\
			ft_memset.c		\
			ft_bzero.c		\
			ft_memcpy.c		\
			ft_memmove.c	\
			ft_strlcpy.c	\
			ft_strlcat.c	\
			ft_toupper.c	\
			ft_tolower.c	\
			ft_strchr.c		\
			ft_strrchr.c	\
			ft_strncmp.c	\
			ft_memchr.c		\
			ft_memcmp.c		\
			ft_strnstr.c	\
			ft_atoi.c		\
			ft_calloc.c		\
			ft_strdup.c		\
			ft_substr.c		\
			ft_strjoin.c	\
			ft_strtrim.c	\
			ft_split.c		\
			ft_itoa.c		\
			ft_strmapi.c	\
			ft_striteri.c	\
			ft_putchar_fd.c	\
			ft_putstr_fd.c	\
			ft_putendl_fd.c	\
			ft_putnbr_fd.c	\

B_SRCS	=	ft_lstnew.c			\
			ft_lstadd_front.c	\
			ft_lstsize.c		\
			ft_lstlast.c		\
			ft_lstadd_back.c	\
			ft_lstdelone.c		\
			ft_lstclear.c		\
			ft_lstiter.c		\
			ft_lstmap.c			\

EXTRA_SRCS	=	ft_isspace.c			\
				ft_strtol.c				\
				ft_strcmp.c				\
				ft_strncat.c			\
				ft_realloc.c			\
				ft_reallocf.c			\
				ft_strndup.c			\

GNL_SRCS	=	get_next_line/get_next_line.c	\

PRINTF_SRCS	=	ft_printf/ft_printf.c			\
				ft_printf/ft_vdprintf.c			\
				ft_printf/ft_vprintf.c			\
				ft_printf/ft_dprintf.c			\
				ft_printf/ft_sprintf.c			\
				ft_printf/ft_printf_cs.c		\
				ft_printf/ft_printf_diu.c		\
				ft_printf/ft_printf_fmt.c		\
				ft_printf/ft_printf_hex.c		\
				ft_printf/ft_printf_parser.c	\
				ft_printf/ft_printf_percent.c	\
				ft_printf/ft_printf_px.c		\
				ft_printf/ft_printf_f.c			\
				ft_printf/ft_decimal.c			\
				ft_printf/ft_decimal_to_str.c	\
				ft_printf/ft_ieee754_float.c	\
				ft_printf/ft_ieee754_double.c	\
				ft_printf/ft_ftoa.c				\
				ft_printf/ft_dtoa.c				\

ARGPARSE_SRCS	=	ft_argparse/ft_argparse_num.c	\

ERROR_FUNCTIONS_SRCS	=	ft_error_functions/ft_error_functions.c	\

OBJDIR		=	objs
SRCS		=	$(M_SRCS) $(B_SRCS) $(EXTRA_SRCS) $(GNL_SRCS) $(PRINTF_SRCS) $(ARGPARSE_SRCS) $(ERROR_FUNCTIONS_SRCS)
OBJS		=	$(SRCS:%.c=$(OBJDIR)/%.o)
DEPS		=	$(OBJS:%.o=%.d)

all: $(NAME)

$(NAME): $(OBJS) $(INC)
	ar -r $(NAME) $(OBJS) 

clean:
	@$(RM) -r $(OBJDIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

$(OBJDIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE)

bonus: all

# x86 mac
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
debug: CFLAGS += -Weverything -Wno-padded -Wno-strict-prototypes -Wno-packed -Wno-reserved-id-macro
endif

# ARM mac
UNAME_P := $(shell uname -p)
ifneq ($(filter arm%, $(UNAME_P)),)
debug: CFLAGS += -Weverything -Wno-padded -Wno-strict-prototypes -Wno-packed -Wno-poison-system-directories -Wno-cast-qual
endif
debug: re
	norminette include ft_*.c ft_error_functions ft_argparse ft_printf

test:
	./test.sh

.PHONY: all clean fclean re bonus debug
-include $(DEPS)
