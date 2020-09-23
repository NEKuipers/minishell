/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/02 10:51:13 by nkuipers       #+#    #+#                */
/*   Updated: 2019/12/02 16:02:58 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	split_line(char **line, char **store, char *temp, int fd)
{
	int	len;

	len = temp - store[fd];
	*line = ft_substr(store[fd], 0, len);
	if (*line == NULL)
	{
		free(store[fd]);
		return (-1);
	}
	temp = store[fd];
	store[fd] = ft_strdup(store[fd] + len + 1);
	free(temp);
	if (store[fd] == NULL)
	{
		free(store[fd]);
		return (-1);
	}
	return (1);
}

static char	*read_line(int fd, char *store)
{
	int		bytes;
	char	*buf;
	char	*temp;

	if (store == NULL)
		store = ft_strdup("");
	buf = (char*)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buf || store == NULL)
		return (0);
	while (ft_strchr(store, '\n') == 0)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes < 0)
			return (0);
		buf[bytes] = '\0';
		temp = store;
		store = ft_strjoin(store, buf);
		free(temp);
		if (bytes == 0 || store[0] == '\0')
			break ;
	}
	free(buf);
	return (store);
}

int			get_next_line(int fd, char **line)
{
	static char	*store[FD_SIZE];
	char		*temp;

	if (line == 0 || fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
		return (-1);
	store[fd] = read_line(fd, store[fd]);
	if (store[fd] == NULL)
	{
		free(store[fd]);
		return (-1);
	}
	temp = ft_strchr(store[fd], '\n');
	if (temp > 0)
		return (split_line(line, store, temp, fd));
	*line = ft_strdup(store[fd]);
	free(store[fd]);
	store[fd] = NULL;
	if (*line == NULL)
		return (-1);
	return (0);
}
