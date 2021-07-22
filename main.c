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
		write(2, reason, strlen(reason));
		write(2, ": ", 2);
	}
	if (error_message)
		write(2, error_message, strlen(error_message));
	else
		write(2, system_message, strlen(system_message));
	write(2, "\n", 1);
	if (end)
		exit(0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*files[2];
	t_cmd	*head_cmd;
	char	**possible_path;

	head_cmd = NULL;
	take_files(argc, argv, files);
	possible_path = take_env_path(envp);
	take_commands(argc, argv, &head_cmd, possible_path);
	free_arr(possible_path);
	exec_commands(&head_cmd, envp);
	free_cmd(head_cmd);
	return (0);
}
