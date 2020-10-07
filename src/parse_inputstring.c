/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_inputstring.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/07 14:18:35 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/10/07 16:02:58 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	parse_quotes(t_shell *shell, char *input, int *i, char c)
{
	int		j;
	// t_ops	operation;

	(void)shell;
	j = *i + 1;
	while (input[j] != c && input[j])
		j++;
	if (input[j] != c)
		return (ft_printf("error: syntax\n"));
	// shell->operations[0 = ft_substr(input, *i, j);
	// while (*i != j)
	// 	j++;
	return (0);
}

static void	parse_tokens(t_shell *shell, char *input, int *i)
{
	(void)i;
	shell->operations = ft_split(input, ';');
}

void		parse_inputstring(t_shell *shell, char *input)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			if (parse_quotes(shell, input, &i, (input[i] ==
				'"' ? '"' : '\'')) > 1)
				return ;
		}
		else
			parse_tokens(shell, input, &i);
		i++;
	}
	free(input);
	i = 0;
	while (shell->operations[i])
	{
		shell->args = ft_token(shell->operations[i], ' ', '\t');
		if (shell->args[0] != NULL)
			shell->rv = shell_execute(shell);
		free_args(shell->args);
		i++;
	}
}
