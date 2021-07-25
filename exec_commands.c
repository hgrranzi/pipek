/* *********************************************** */
/*                                                 */
/*       by: hgrranzi <vkh.mariia@gmail.com>       */
/*                                                 */
/* *********************************************** */

#include "pipek.h"

int	count_cmd(t_cmd **head_cmd)
{
	int		i;
	t_cmd	*head_cmd_p;

	head_cmd_p = *head_cmd;
	while (head_cmd_p)
	{
		i++;
		head_cmd_p = head_cmd_p->next;
	}
	return (i);
}

void	init_pids_and_pipes(int cmd_count, pid_t *pid, int **fd)
{
	int		i;

	pid = malloc(cmd_count * sizeof(int));
	if (!pid)
		error_and_exit(NULL, NULL, 1);
	i = 0;
	while (i < cmd_count)
	{
		pid[i] = 1;
		i++;
	}
	fd = malloc(cmd_count * sizeof(int *));
	if (!fd)
		error_and_exit(NULL, NULL, 1);
	i = 0;
	while (i < cmd_count - 1)
	{
		fd[i] = malloc(2 * sizeof(int));
		if (!fd[i])
			error_and_exit(NULL, NULL, 1);
		if (pipe(fd[i]) == -1)
			error_and_exit(NULL, NULL, 1);
		i++;
	}
}

void	kill_the_others()
{
	return ;
}

void	close_unused_pipes(int **pipe_fd, int i, int cmd_count)
{
	int	j;

	j = 0;
	while (j < cmd_count - 1)
	{
		if (j != i - 1)
			close(pipe_fd[j][IN]);
		if (j != i)
			close(pipe_fd[j][OUT]);
		j++;
	}
}

void	duplicate_fd(int *fd, int **pipe_fd, int i)
{
	return ;
}

int	create_processes(t_cmd *head_cmd_p, int cmd_count, pid_t *pid, int **pipe_fd)
{
	int	i;

	i = 0;
	while (head_cmd_p)
	{
		pid[i] = fork();
		if (pid[i] == -1)
		{
			kill_the_others();
			error_and_exit(NULL, NULL, 1);
		}
		if (pid == IS_CHILD)
		{
			close_unused_pipes(pipe_fd, i, cmd_count);
			duplicate_fd(head_cmd_p->fd, pipe_fd, i);
			if (head_cmd_p->args[CMD_PATH])
			{
				execve(head_cmd_p->args[CMD_PATH], head_cmd_p->args, NULL);
				error_and_exit(head_cmd_p->args[CMD_PATH], NULL, 1); // not here
			}
			return (0);
		}
		head_cmd_p = head_cmd_p->next;
		close(pipe_fd[i][0]);
		close(pipe_fd[i][1]);
		i++;
	}
	return (0);
}

void	distribute_fd(t_cmd **head_cmd, int **pipe_fd)
{
	t_cmd	*head_cmd_p;
	int		i;

	head_cmd_p = *head_cmd;
	i = 0;
	while (head_cmd_p)
	{
		if (i > 0)
		{
			if (head_cmd_p->fd[IN] == STDIN_FILENO)
				head_cmd_p->fd[IN] = pipe_fd[i - 1][IN];
		}
		if (head_cmd_p->next != NULL)
		{
			if (head_cmd_p->fd[OUT] == STDOUT_FILENO)
				head_cmd_p->fd[OUT] = pipe_fd[i][OUT];
		}
		head_cmd_p = head_cmd_p->next;
		i++;
	}
}

int	exec_commands(t_cmd **head_cmd)
{
	t_cmd	*head_cmd_p;
	pid_t	*pid;
	int		**pipe_fd;
	int		cmd_count;

	head_cmd_p = *head_cmd;
	pid = NULL;
	pipe_fd = NULL;
	cmd_count = count_cmd(head_cmd);
	init_pids_and_pipes(cmd_count, pid, pipe_fd); // probably better split in 2 diff functions
	distribute_fd(head_cmd_p, pipe_fd);
	create_processes(head_cmd_p, cmd_count, pid, pipe_fd);
	return (0);
}
