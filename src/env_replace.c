/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_replace.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/21 17:09:46 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/11/19 15:33:02 by brendan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static char	*repl_change(char *in, int i, int len, char *val)
{
	char	*out;

	if (val)
	{
		out = malloc(ft_strlen(in) - len + ft_strlen(val) + 1);
		if (!out)
			return (NULL);
		ft_strlcpy(out, in, i + 1);
		ft_strlcpy(out + i, val, ft_strlen(val) + 1);
		ft_strlcpy(out + i + ft_strlen(val), in + i + len, \
			ft_strlen(in) - len - i + 1);
	}
	else
	{
		out = malloc(ft_strlen(in) - len);
		if (!out)
			return (NULL);
		ft_strlcpy(out, in, i + 1);
		ft_strlcpy(out + i, in + i + len, ft_strlen(in) - i - len + 1);
	}
	free(val);
	free(in);
	return (out);
}

static int	repl_env_name(char *in, int i, char **env, char **val)
{
	int		clip;
	int		j;
	int		k;
	char	*tkn;

	clip = 0;
	while (in[i + 1 + clip] && (ft_isalpha(in[i + 1 + clip]) \
		|| ft_isdigit(in[i + 1 + clip]) || in[i + 1 + clip] == '_'))
		clip++;
	tkn = in + i + 1;
	j = 0;
	while (env[j])
	{
		k = ft_strnstr(env[j], "=", ft_strlen(env[j])) - env[j];
		if (!ft_strncmp(env[j], tkn, max(clip, k)))
		{
			*val = ft_strdup(env[j] + k + 1);
			break ;
		}
		j++;
	}
	return (clip);
}

int	repl_env(int i, char **in, t_shell *shell)
{
	char	*val;
	int		len;

	val = NULL;
	if ((*in)[i + 1] == '?')
	{
		*in = repl_change(*in, i, 2, ft_itoa(shell->rv));
		return (1);
	}
	else
	{
		len = repl_env_name(*in, i, shell->evs, &val) + 1;
		*in = repl_change(*in, i, len, val);
		if (!val)
			return (0);
		return (len);
	}
}

static char	*repl_homedir(char *in, t_shell *shell)
{
	char	*out;
	char	*val;
	int		index;

	index = find_ev(shell->evs, "HOME");
	if (index < 0)
		out = repl_change(in, 0, 1, ft_strdup(""));
	else
	{
		val = ft_strchr(shell->evs[index], '=') + 1;
		out = repl_change(in, 0, 1, ft_strdup(val));
	}
	return (out);
}

char	*repl_process(char *in, t_shell *shell)
{
	int		i;
	char	inquotes;

	i = 0;
	inquotes = 0;
	if (in && (!ft_strcmp(in, "~") || !ft_strncmp(in, "~/", 2)))
		in = repl_homedir(in, shell);
	while (in && in[i])
	{
		if (in[i] == '\"' && (i == 0 || (i > 0 && in[i - 1] != '\\')))
			inquotes = (inquotes + 1) % 2;
		if (in[i] == '\'' && (i == 0 || (i > 0 && in[i - 1] != '\\')) \
			&& !inquotes)
		{
			i++;
			while (!(in[i] == '\'' && in[i - 1] != '\\'))
				i++;
		}
		if (in[i] == '\\' && in[i + 1] == '$')
			in = repl_change(in, i, 2, ft_strdup("$"));
		else if (in[i] == '$' && in[i + 1] && in[i + 1] != '$')
			i += repl_env(i, &in, shell) - 1;
		i++;
	}
	return (in);
}
