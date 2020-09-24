/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/21 21:22:15 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/09/24 15:04:51 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*g_shell_bnames[] =
{
	"cat",
	"cd",
	"echo",
	"env",
	"help",
	"pwd",
	"exit"
};

int		(*g_shell_builtins[]) (char **, char **) =
{
	&shell_cat,
	&shell_cd,
	&shell_echo,
	&shell_env,
	&shell_help,
	&shell_pwd,
	&shell_exit
};

/*
This function simply looks up the first argument in the name table above, and
then enters the corresponding function in the function table if it exists.
Otherwise, it will check if the first argument is an existing program it can
find in the PATH, and attempt to execute it in shell_execpath.
*/

int		shell_execute(char **args, char **evs)
{
	unsigned long i;

	i = 0;
	while (i < (sizeof(g_shell_bnames) / sizeof(char *)))
	{
		if (ft_strncmp(args[0], g_shell_bnames[i], ft_strlen(args[0])) == 0)
			return (g_shell_builtins[i](args, evs));
		i++;
	}
	if (shell_execpath(args, evs) == 0)
		return (0);
	return (0);
}

/*
The main loop. Here, we print the prompt; we read the standard input
for instructions; we cut them up into arguments by splitting the
spaces/tabs, and then we free the input. Then it's time to execute whatever
the input wants.

The signal(SIGINT) catches the interruption signal caused by ctrl-c and,
instead of exiting the program, calls the function ctrlchandler.
That function prints a new prompt.
*/

void	shell_loop(char **evs)
{
	char *input;
	char **args;

	input = "";
	while (ft_strncmp(input, "exit", 5) != 0)
	{
		signal(SIGINT, ctrlchandler);
		ft_printf("=> ");
		if (get_next_line(0, &input) == 0)
		{
			free_args(evs);
			exit(0);
		}
		args = ft_token(input, ' ', '\t');
		free(input);
		if (args[0] != NULL)
			shell_execute(args, evs);
		free_args(args);
	}
}

char	**copy_evs(char **inputs)
{
	int		i;
	char	**ret;

	i = 0;
	while (inputs[i])
		i++;
	ret = malloc((i + 1) * (sizeof(char *)));
	if (!ret)
		return (NULL);
	i = 0;
	while (inputs[i])
	{
		ret[i] = ft_strdup(inputs[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

/*
The main is called with a third argument: envp, which are the
environment variables. Since they are inmutable, we copy them
to a new string array using copy_evs. After that, we enter the main shell loop.
*/

int		main(int argc, char **argv, char **envp)
{
	char **evs;

	evs = copy_evs(envp);
	if (evs == NULL)
		shell_exit(evs, evs);
	(void)argv;
	if (argc == 1)
	{
		ft_printf("Hi %s! Welcome to ~~minishell~~. ", getenv("USER"));
		ft_printf("Enter 'exit' at any time to leave.\n");
		ft_printf("_______________________________________________________\n");
		shell_loop(evs);
	}
	return (0);
}
