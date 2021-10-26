/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_replace.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/21 17:09:46 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/10/26 15:42:06 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/*
static char	*repl_glue(char **temp)
{
	char	*out[2];

	out[0] = ft_strjoin(temp[0], temp[1]);
	free(temp[0]);
	if (!out[0])
		return (NULL);
	out[1] = ft_strjoin(out[0], temp[2]);
	free(out[0]);
	return (out[1]);
}

static char	*repl_change(char *in, char *search, int *i, char **env)
{
	char	*temp[3];
	int		j;
	int		k;

	j = 0;
	temp[1] = "";
	while (env[j])
	{
		k = ft_strnstr(env[j], "=", ft_strlen(env[j])) - env[j];
		if (!ft_strncmp(env[j], search, ft_strlen(search)))
		{
			temp[1] = env[j] + k + 1;
			break ;
		}
		j++;
		if (env[j] == NULL)
			k = ft_strlen(search);
	}
	temp[2] = in + *i + 1 + k;
	temp[0] = ft_substr(in, 0, *i);
	if (!temp[0])
		return (NULL);
	*i += ft_strlen(temp[1]) - 1;
	return (repl_glue(temp));
}
*/

static char	*repl_change(char *in, int i, int len, char *val)
{
	char	*out;

	if (val)
	{
		//ft_printf_fd(1, "%i\n", ft_strlen(in) - len + ft_strlen(val));
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
		//ft_printf_fd(1, "%i\n", ft_strlen(in) - len);
		out = malloc(ft_strlen(in) - len);
		if (!out)
			return (NULL);
		ft_strlcpy(out, in, i + 1);
		ft_strlcpy(out + i, in + i + len, ft_strlen(in) - i - len + 1);
	}
	//ft_printf_fd(1, "%s\n", out);
	free(val);
	return (out);
}

static char	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

static int	repl_env_name(char *in, int i, char **env, char **val)
{
	int		clip;
	int		j;
	int		k;
	char	*tkn;

	clip = 0;
	while (in[i + 1 + clip] && !ft_strchr(" \t$\"\'", in[i + 1 + clip]))
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
		len = 1;
		val = ft_itoa(shell->rv);
	}
	else
	{
		len = repl_env_name(*in, i, shell->evs, &val) + 1;
		*in = repl_change(*in, i, len, val);
		return (len);
	}
}

char	*repl_process(char *in, t_shell *shell)
{
	int		i;

	i = 0;
	while (in && in[i])
	{
		ft_printf_fd(1, "%c\n", in[i]);
		if (in[i] == '\'' && (i == 0 || (i > 0 && in[i - 1] != '\\')))
		{
			i++;
			while (!(in[i] == '\'' && in[i - 1] != '\\'))
				i++;
		}
		if (in[i] == '\\' && in[i + 1] == '$')
			in = repl_change(in, i, 2, ft_strdup("$"));
		else if (in[i] == '$' && in[i + 1] && in[i + 1] != '$')
			i += repl_env(i, &in, shell);
		else
			i++;
	}
	return (in);
}
