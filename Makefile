# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nkuipers <nkuipers@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/09/21 21:22:12 by nkuipers      #+#    #+#                  #
#    Updated: 2021/11/04 13:26:11 by bmans         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME            =   minishell
SRCS            =   main.c \
					arrange_tokens.c \
					create_tokens.c \
					create_tokens_2.c \
					create_tokens_utils.c \
					create_tokens_utils_2.c \
					env_replace.c \
					fds.c \
					init_shell.c \
					pipes_redirs.c \
					signal.c \
					shell_builtins.c \
					shell_cd.c \
					shell_exec_bin.c \
					shell_export.c \
					shell_export_utils.c \
					shell_unset.c \
					utils.c \
					utils_2.c

BREW_DIR		=	.brew
CFILES          =   $(SRCS:%=src/%)
OFILES          =   $(CFILES:.c=.o)
CFLAGS          =   -Wall -Wextra -Werror -g
INCLUDES        =   -I includes \
                    -I lib/libft \
					-I ~/$(BREW_DIR)/opt/readline/include
LIBS            =   lib/libft/libft.a -lreadline \
					-L ~/$(BREW_DIR)/opt/readline/lib
# LIB LOCATIONS
LIBFT_LOC       =   lib/libft
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
	@echo "$(WHITE)/-----      Putting minishell together..\
	.    -----\\ $(RESET)"
	@gcc $(CFLAGS) $(INCLUDES) $(OFILES) $(LIBS) -o $(NAME)
	@echo "$(GREEN) Compiling complete. Name of executable is \
	'minishell'. $(RESET)"

%.o: %.c
	@echo "$(WHITE)Compiling: $<"
	@gcc $(INCLUDES) -o $@ -c $< $(CFLAGS)

clean:
	@echo "$(WHITE)/-----      Cleaning libft      -----\\ $(RESET)"
	@make fclean -C $(LIBFT_LOC)
	@echo "$(WHITE)/-----      Cleaning minishell     -----\\ $(RESET)"
	@echo "$(WHITE) Cleaning..."
	@rm -f $(OFILES)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
