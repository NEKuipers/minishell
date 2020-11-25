#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

void	scan_fds(void)
{
	//fprintf(stderr, "\n");
	for (int i = 0; i < 20; i++)
	{
		if (write(i, NULL, 0) != -1)
			fprintf(stderr, "%d ", i);
	}
}

int		g_fd[2] = {-1, -1};

void	backup_fd(void)
{
	g_fd[0] = dup(0);
	g_fd[1] = dup(1);
}

void	reset_fd(void)
{
	dup2(g_fd[0], 0);
	dup2(g_fd[1], 1);
	close(g_fd[0]);
	close(g_fd[1]);
	g_fd[0] = -1;
	g_fd[1] = -1;
}

int		piper(int *fdes)
{
	pid_t	pid;

	pipe(fdes);
	pid = fork();
	if (!pid)	//child
	{
		close(fdes[0]);
		dup2(fdes[1], 1);
		//write(1, "abcde", 6);
		system("echo rrrrr");
		//close(1);
		return (2);
	}
	else	//parent
	{
		close(fdes[1]);
		dup2(fdes[0], 0);
		wait(0);
		return (1);
	}
}

int		main(void)
{
	char	buf[6];
	int		fdes[2];

	backup_fd();
	if (piper(fdes) == 1)
	{
		//read(0, buf, 6);
		system("grep -n r");
		//buf[2] = 'q';
		//write(2, buf, 6);
		reset_fd();
		//write(1, buf, 6);
		scan_fds();
	}
	return (0);
}
