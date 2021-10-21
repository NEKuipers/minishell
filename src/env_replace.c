#include "libft.h"

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

static char	*repl_env_name(char *in, int i)
{
	int		clip;

	clip = 0;
	while (in[i + 1 + clip] && !ft_strchr(" \t$", in[i + 1 + clip]))
		clip++;
	return (ft_substr(in, i + 1, clip));
}

char	*repl_process(char *in, char **env)
{
	int		i;
	char	*out;
	char	*search;

	i = 0;
	out = in;
	while (in[i])
	{
		if (in[i] == '$' && in[i + 1] && in[i + 1] != '$')
		{
			search = repl_env_name(in, i);
			if (!search)
				return (NULL);
			out = repl_change(in, search, &i, env);
			free(search);
			if (!out)
				return (NULL);
			free(in);
			in = out;
		}
		i++;
	}
	return (out);
}

/* int	main(int ac, char **av, char **env)
{
	char	*in;
	char	*out;

	if (ac == 2)
	{
		in = ft_strdup(av[1]);
		ft_printf_fd(1, "in: %s\n", in);
		out = repl_process(in, env);
		ft_printf_fd(1, "out: %s\n", out);
	}
	system("leaks a.out");
	return (0);
}
*/