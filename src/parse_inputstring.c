/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_inputstring.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/07 14:18:35 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/10/07 14:32:04 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		parse_inputstring(t_shell *shell, char *input)
{
	int		i;

	shell->operations = ft_split(input, ';');
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
	free_args(shell->operations);
}
