# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nkuipers <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2019/10/28 13:56:44 by nkuipers      #+#    #+#                  #
#    Updated: 2021/09/30 16:02:19 by nkuipers      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = 		libft.a
OBJECTS = 	ft_atoi.o ft_bzero.o ft_calloc.o ft_isalnum.o ft_isalpha.o \
			ft_isascii.o ft_isdigit.o ft_isprint.o ft_itoa.o ft_memccpy.o \
			ft_memchr.o ft_memcmp.o ft_memcpy.o ft_memmove.o ft_memset.o \
			ft_putchar_fd.o ft_putendl_fd.o ft_putnbr_fd.o ft_putstr_fd.o \
			ft_split.o ft_strchr.o ft_strdup.o ft_strjoin.o ft_strlcat.o \
			ft_strlcpy.o ft_strlen.o ft_strmapi.o ft_strncmp.o ft_strnstr.o \
			ft_strrchr.o ft_strtrim.o ft_substr.o ft_tolower.o ft_toupper.o \
			get_next_line.o \
			ft_itoa_prec.o \
			ft_itoa_base_prec.o \
			ft_print_char.o \
			ft_print_flags.o \
			ft_print_int.o \
			ft_print_ptr.o \
			ft_print_resize.o \
			ft_print_string.o \
			ft_print_uint.o \
			ft_printf.o \
			ft_putnchar_fd.o \
			ft_nbrlen.o \
			ft_memdel.o \
			ft_strcmp.o \
			ft_strisnum.o

BONUS =		ft_lstadd_back_bonus.o ft_lstadd_front_bonus.o \
			ft_lstclear_bonus.o ft_lstclear_bonus.o ft_lstdelone_bonus.o \
			ft_lstiter_bonus.o ft_lstlast_bonus.o ft_lstmap_bonus.o \
			ft_lstnew_bonus.o ft_lstsize_bonus.o
FLAGS = 	-Wall -Werror -Wextra
INCLUDES = 	.

# COLOURS
GREEN	= \x1b[32;01m
WHITE	= \x1b[29;01m
RESET	= \x1b[0m

all: $(NAME)

%.o: %.c
	@echo "$(WHITE)Compiling: $<"
	@gcc -o $@ -c $< $(FLAGS) -I$(INCLUDES)

$(NAME): $(OBJECTS)
	@echo "$(GREEN)Linking the library"
	@ar rc $(NAME) $(OBJECTS)
	@echo "$(GREEN)Done"

clean: clean_b
	@echo "$(WHITE) Cleaning..."

fclean: clean_b
	@echo "$(WHITE) Cleaning all..."
	@rm -f $(NAME)

clean_b:
	@rm -f $(BONUS)
	@rm -f $(OBJECTS)

re: fclean all

bonus: $(OBJECTS) $(BONUS) $(NAME)
	@ar rc $(NAME) $(OBJECTS) $(BONUS)
	@ranlib $(NAME)

.PHONY: all clean fclean re bonus
