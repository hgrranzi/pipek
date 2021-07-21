/* *********************************************** */
/*                                                 */
/*       by: hgrranzi <vkh.mariia@gmail.com>       */
/*                                                 */
/* *********************************************** */

#include "pipek.h"

void	error_and_exit(char *error_message)
{
	char	*system_message;

	system_message = strerror(errno);
	if (error_message)
		write(2, error_message, strlen(error_message));
	else
		write(2, system_message, strlen(system_message));
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
	take_commands(argc, argv, &head_cmd, possible_path); // instead of envp need a function that takes the PATH and split it
	return (0);
}
