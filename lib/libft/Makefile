# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nkuipers <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2019/10/28 13:56:44 by nkuipers      #+#    #+#                  #
#    Updated: 2021/07/01 12:03:00 by nkuipers      ########   odam.nl          #
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
			ft_nbrlen.o

BONUS =		ft_lstadd_back_bonus.o ft_lstadd_front_bonus.o \
			ft_lstclear_bonus.o ft_lstclear_bonus.o ft_lstdelone_bonus.o \
			ft_lstiter_bonus.o ft_lstlast_bonus.o ft_lstmap_bonus.o \
			ft_lstnew_bonus.o ft_lstsize_bonus.o
FLAGS = 	-Wall -Werror -Wextra
INCLUDES = 	.

# COLORS
ifeq ($(WSL_DISTRO_NAME), Ubuntu)
	WHITE   = \e[37;01m
	CYAN    = \e[36;01m
	PINK    = \e[35;01m
	BLUE    = \e[34;01m
	YELLOW  = \e[33;01m
	GREEN   = \e[32;01m
	RED     = \e[31;01m
	BLACK   = \e[30;01m
	RESET   = \e[0m
else
	WHITE   = \x1b[37;01m
	CYAN    = \x1b[36;01m
	PINK    = \x1b[35;01m
	BLUE    = \x1b[34;01m
	YELLOW  = \x1b[33;01m
	GREEN   = \x1b[32;01m
	RED     = \x1b[31;01m
	BLACK   = \x1b[30;01m
	RESET   = \x1b[0m
endif

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
