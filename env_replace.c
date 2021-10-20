#include "libft.h"

char	*glue(char **temp)
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

char	*change(char *in, int *i, char **env)
{
	char	*temp[3];
	int		j;
	int		k;

	j = 0;
	while (env[j])
	{
		k = 0;
		while (env[j][k] != '=')
			k++;
		if (!ft_strncmp(env[j], in + (*i) + 1, k))
		{
			temp[1] = env[j] + k + 1;
			break ;
		}
		j++;
		if (env[j] == NULL)
			return (NULL);
	}
	temp[2] = in + *i + 1 + k;
	temp[0] = ft_substr(in, 0, *i);
	if (!temp[0])
		return (NULL);
	*i += ft_strlen(temp[1]);
	return (glue(temp));
}

char	*process(char *in, char **env)
{
	int		i;
	char	*out;

	i = 0;
	while (in[i])
	{
		if (in[i] == '$')
		{
			out = change(in, &i, env);
			if (!out)
				return (NULL);
			free(in);
			in = out;
		}
		i++;
	}
	return (out);
}

int	main(int ac, char **av, char **env)
{
	char	*in;
	char	*out;

	if (ac == 2)
	{
		in = ft_strdup(av[1]);
		ft_printf_fd(1, "in: %s\n", in);
		out = process(in, env);
		ft_printf_fd(1, "out: %s\n", out);
	}
	system("leaks a.out");
	return (0);
}
