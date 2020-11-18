#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int	piper(int *fdes)
{
	pid_t	pid;

	pipe(fdes);
	pid = fork();
	if (!pid)
	{
		close(fdes[0]);
		dup2(fdes[1], 1);
		write(1, "abcde", 6);
		return (2);
	}
	else
	{
		close(fdes[1]);
		dup2(fdes[0], 0);
		wait(0);
		return (1);
	}
}

int	main(void)
{
	char	buf[6];
	int		fdes[2];

	if (piper(fdes) == 1)
	{
		read(0, buf, 6);
		buf[2] = 'q';
		write(2, buf, 6);
		close(fdes[0]);
		close(fdes[1]);
		read(0, buf, 6);
		write(1, buf, 6);
	}
	return (0);
}
