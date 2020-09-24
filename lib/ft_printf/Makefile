# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nkuipers <nkuipers@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/11/18 09:44:57 by nkuipers      #+#    #+#                  #
#    Updated: 2020/09/24 15:40:17 by nkuipers      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = 		libftprintf.a
SRCS = 		ft_parse_flags.c \
			ft_printf_char.c \
			ft_printf_hex.c \
			ft_printf_hex_2.c \
			ft_printf_int.c \
			ft_printf_int_l.c \
			ft_printf_int_ll.c \
			ft_printf.c \
			ft_printf_un.c \
			ft_printf_string.c \
			ft_printf_ptr.c
CFILES		=	$(SRCS:%=srcs/%)
OFILES		=	$(CFILES:.c=.o)
INCLUDES	= ./includes
FLAGS = 	-Wall -Werror -Wextra

# COLOURS
GREEN	= \x1b[32;01m
WHITE	= \x1b[29;01m

all: $(NAME)

%.o: %.c
	@echo "$(WHITE)Compiling: $<"
	@gcc -o $@ -c $< $(FLAGS)

$(NAME): $(OFILES)
	@echo "$(GREEN)Creating"
	@ar rc $(NAME) $(OFILES)
	@ranlib $(NAME)
	@echo "$(GREEN)Done"

clean: clean_b
	@echo "$(WHITE) Cleaning..."

fclean: clean_b
	@echo "$(WHITE) Cleaning all..."
	@rm -f $(NAME)

clean_b:
	@rm -f $(OFILES)

re: fclean all

bonus: $(NAME)

.PHONY: all clean fclean re bonus
