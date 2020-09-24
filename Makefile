# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nkuipers <nkuipers@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/09/21 21:22:12 by nkuipers      #+#    #+#                  #
#    Updated: 2020/09/24 11:10:03 by nkuipers      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME            =   minishell
SRCS            =   main.c \
					ft_token.c \
					shellbuiltins.c \
					shellbuiltins_2.c \
					shellfunctions.c \
					utils.c 
CFILES          =   $(SRCS:%=src/%)
OFILES          =   $(CFILES:.c=.o)
CFLAGS          =   -Wall -Wextra -Werror
INCLUDES        =   -I includes \
                    -I lib/libft \
					-I lib/ft_printf/includes
LIBS            =   lib/libft/libft.a \
					lib/ft_printf/libftprintf.a
# LIB LOCATIONS
LIBFT_LOC       =   lib/libft
FTPRINTF_LOC	=	lib/ft_printf
# COLORS
WHITE   = \x1b[37;01m
CYAN    = \x1b[36;01m
PINK    = \x1b[35;01m
BLUE    = \x1b[34;01m
YELLOW  = \x1b[33;01m
GREEN   = \x1b[32;01m
RED     = \x1b[31;01m
BLACK   = \x1b[30;01m
RESET   = \x1b[0m

all: $(NAME)

$(NAME): $(OFILES)
	@echo "$(WHITE)/-----      Compiling libft     -----\\ $(RESET)"
	@make bonus -C $(LIBFT_LOC)
	@echo "$(WHITE)/-----      Compiling ft_printf     -----\\ $(RESET)"
	@make -C $(FTPRINTF_LOC)
	@echo "$(WHITE)/-----      Compiling minishell    -----\\ $(RESET)"
	@gcc $(CFLAGS) $(INCLUDES) $(OFILES) $(LIBS) -o $(NAME)
	@echo "$(GREEN) Compiling complete. Name of executable is 'minishell'. $(RESET)"

%.o: %.c
	@echo "$(WHITE)Compiling: $<"
	@gcc $(INCLUDES) -o $@ -c $< $(CFLAGS) 

clean:
	@echo "$(WHITE)/-----      Cleaning libft      -----\\ $(RESET)"
	@make clean -C $(LIBFT_LOC)
	@echo "$(WHITE)/-----      Cleaning ft_printf      -----\\ $(RESET)"
	@make clean -C $(FTPRINTF_LOC)
	@echo "$(WHITE)/-----      Cleaning minishell     -----\\ $(RESET)"
	@rm -f $(OFILES)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re