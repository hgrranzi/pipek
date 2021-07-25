/* *********************************************** */
/*                                                 */
/*       by: hgrranzi <vkh.mariia@gmail.com>       */
/*                                                 */
/* *********************************************** */

#include "pipek.h"

void	error_and_exit(char *reason, char *error_message, int end)
{
	char	*system_message;

	system_message = strerror(errno);
	if (reason)
	{
		write(STDERR_FILENO, reason, strlen(reason));
		write(STDERR_FILENO, ": ", 2);
	}
	if (error_message)
		write(STDERR_FILENO, error_message, strlen(error_message));
	else
		write(STDERR_FILENO, system_message, strlen(system_message));
	write(STDERR_FILENO, "\n", 1);
	if (end)
		exit(0);
}

void	open_files(char **files, t_cmd **head_cmd)
{
	t_cmd	*cmd_p;

	cmd_p = *head_cmd;
	cmd_p->fd[INFILE] = open(files[INFILE], O_RDONLY);
	if (cmd_p->fd[INFILE] == -1)
		error_and_exit(files[INFILE], NULL, 0);
	while (cmd_p->next)
		cmd_p = cmd_p->next;
	cmd_p->fd[OUTFILE] = open(files[OUTFILE], O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (cmd_p->fd[OUTFILE] == -1)
		error_and_exit(files[OUTFILE], NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*files[2];
	t_cmd	*head_cmd;
	char	**possible_path;

	head_cmd = NULL; // init?
	take_files(argc, argv, files);
	possible_path = take_env_path(envp);
	take_commands(argc, argv, &head_cmd, possible_path);
	free_arr(possible_path);
	open_files(files, &head_cmd);
	exec_commands(&head_cmd);
	free_cmd(head_cmd);
	return (0);
}
