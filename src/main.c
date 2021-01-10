/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/21 21:22:15 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/01/10 13:06:58 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** TO DO:
**   - unset command is still not perfect, especially when used several times
**   - make redirects work
**   - make pipes work
**   - make sure the shell->rv is always given the correct rv
*/

char	*g_shell_bnames[] =
{
	"cd",
	"echo",
	"env",
	"exit",
	"help",
	"pwd",
};

int		(*g_shell_builtins[]) (t_shell *) =
{
	&shell_cd,
	&shell_echo,
	&shell_env,
	&shell_exit,
	&shell_help,
	&shell_pwd,
};

/*
** This function simply looks up the first argument in the name table above, and
** then enters the corresponding function in the function table if it exists.
** Otherwise, it will check if the first argument is an existing program it can
** find in the PATH, and attempt to execute it in shell_execpath.
*/

//static void	clear_ops(void *ops)
//{
//	free(((t_ops *)ops)->operation);
//	free_args(((t_ops *)ops)->args);
//	free(ops);
//}

int		shell_execute(t_shell *shell, char **args)
{
	unsigned long i;

	i = 0;
	args = transl_env(shell, args);
	if (args == NULL)
		return (0);
	while (i < (sizeof(g_shell_bnames) / sizeof(char *)))
	{
		if (ft_strncmp(args[0], g_shell_bnames[i],
			ft_strlen(args[0])) == 0)
			return (g_shell_builtins[i](shell));
		i++;
	}
	if (ft_strncmp(args[0], "export", 7) == 0)
		return (shell_export(shell));
	if (ft_strncmp(args[0], "unset", 5) == 0)
		return (shell_unset(shell));
	return (shell_execpath(shell));
}

/*
** The main loop. Here, we print the prompt; we read the standard input
** for instructions; we cut them up into arguments by splitting the
** spaces/tabs, and then we free the input. Then it's time to execute whatever
** the input wants.
**
** The signal(SIGINT) catches the interruption signal caused by ctrl-c and,
** instead of exiting the program, calls the function ctrlchandler.
** That function prints a new prompt.
**
** The signal(SIGTERM) catches the quit signal caused by ctrl-\, which
** would normally cause a core dump and force the minishell to exit.
** Instead it does nothing, like in bash.
*/

void	shell_loop(t_shell *shell)
{
	char	*input;

	input = NULL;
	while (1)
	{
		signal(SIGINT, ctrlchandler);
		signal(SIGQUIT, ctrlbshandler);
		ft_printf("<$ ");
		if (get_next_line(0, &input) == 0)
		{
			free_args(shell->evs);
			exit(0);
		}
		parse_inputstring(shell, input);
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
** The main is called with a third argument: envp, which are the
** environment variables. Since they are inmutable, we copy them
** to a new string array using copy_evs. After that, we enter the main
** shell loop.
*/

int		main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	shell.rv = 0;
	reset_std_fds(&shell);
	shell.evs = copy_evs(envp);
	if (shell.evs == NULL)
		shell_exit(&shell);
	(void)argv;
	if (argc == 1)
	{
		ft_printf("Hi %s! Welcome to ~~minishell~~. ", getenv("USER"));
		ft_printf("Enter 'exit' at any time to leave.\n");
		ft_printf("_______________________________________________________\n");
		shell_loop(&shell);
	}
	return (0);
}
