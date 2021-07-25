/* *********************************************** */
/*                                                 */
/*       by: hgrranzi <vkh.mariia@gmail.com>       */
/*                                                 */
/* *********************************************** */

#include "pipek.h"

void	take_files(int argc, char **argv, char **files)
{
	if (argc < 5)
		error_and_exit(NULL, ERR_ARGS, 1);
	files[INFILE] = argv[1];
	files[OUTFILE] = argv[argc - 1];
}

void	open_files(char **files, t_cmd **head_cmd)
{
	t_cmd	*head_cmd_p;

	head_cmd_p = *head_cmd;
	head_cmd_p->fd[INFILE] = open(files[INFILE], O_RDONLY);
	if (head_cmd_p->fd[INFILE] == -1)
		error_and_exit(files[INFILE], NULL, 0);
	while (head_cmd_p->next)
		head_cmd_p = head_cmd_p->next;
	head_cmd_p->fd[OUTFILE] = open(files[OUTFILE], O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (head_cmd_p->fd[OUTFILE] == -1)
		error_and_exit(files[OUTFILE], NULL, 0);
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

void	close_unused_pipe_fd(int **pipe_fd, int i, int cmd_count)
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
