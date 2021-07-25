/* *********************************************** */
/*                                                 */
/*       by: hgrranzi <vkh.mariia@gmail.com>       */
/*                                                 */
/* *********************************************** */

#include "pipek.h"

int	count_cmd(t_cmd **head_cmd)
{
	t_cmd	*head_cmd_p;
	int		i;

	head_cmd_p = *head_cmd;
	i = 0;
	while (head_cmd_p)
	{
		i++;
		head_cmd_p = head_cmd_p->next;
	}
	return (i);
}

pid_t	*init_pids(int cmd_count)
{
	int		i;
	pid_t	*pid;

	pid = malloc(cmd_count * sizeof(int));
	if (!pid)
		error_and_exit(NULL, NULL, 1);
	i = 0;
	while (i < cmd_count)
	{
		pid[i] = 1;
		i++;
	}
	return (pid);
}

int	**init_pipes(int cmd_count)
{
	int		i;
	int		**pipe_fd;

	pipe_fd = malloc((cmd_count - 1) * sizeof(int *));
	if (!pipe_fd)
		error_and_exit(NULL, NULL, 1);
	i = 0;
	while (i < cmd_count - 1)
	{
		pipe_fd[i] = malloc(2 * sizeof(int));
		if (!pipe_fd[i])
			error_and_exit(NULL, NULL, 1);
		if (pipe(pipe_fd[i]) == -1)
			error_and_exit(NULL, NULL, 1);
		i++;
	}
	return (pipe_fd);
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

void	duplicate_fd(int *fd, int i)
{
	dup2(fd[IN], STDIN_FILENO);
	dup2(fd[OUT], STDOUT_FILENO);
	return ;
}

void	wait_and_close(pid_t *pid, int **pipe_fd, int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		waitpid(pid[i], NULL, 0);
		if (i > 0)
			close(pipe_fd[i - 1][IN]);
		if (i < cmd_count - 1)
			close(pipe_fd[i][OUT]);
		i++;
	}

}

int	create_processes(t_cmd **head_cmd, int cmd_count, pid_t *pid, int **pipe_fd)
{
	t_cmd	*head_cmd_p;
	int	i;

	head_cmd_p = *head_cmd;
	i = 0;
	while (i < cmd_count)
	{
		if (pid[i] != IS_CHILD)
			pid[i] = fork();
		if (pid[i] == -1)
		{
			kill_the_others();
			error_and_exit(NULL, NULL, 1);
		}
		if (pid[i] == IS_CHILD)
		{
			close_unused_pipes(pipe_fd, i, cmd_count);
			duplicate_fd(head_cmd_p->fd, i);
			if (head_cmd_p->args[CMD_PATH])
			{
				execve(head_cmd_p->args[CMD_PATH], head_cmd_p->args, NULL);
				error_and_exit(head_cmd_p->args[CMD_PATH], NULL, 1); // not here
			}
			return (0);
		}
		head_cmd_p = head_cmd_p->next;
		i++;
	}
	wait_and_close(pid, pipe_fd, cmd_count);
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
	pid_t	*pid;
	int		**pipe_fd;
	int		cmd_count;

	cmd_count = count_cmd(head_cmd);
	pid = init_pids(cmd_count);
	pipe_fd = init_pipes(cmd_count);
	distribute_fd(head_cmd, pipe_fd);
	create_processes(head_cmd, cmd_count, pid, pipe_fd);
	return (0);
}
