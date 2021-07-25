/* *********************************************** */
/*                                                 */
/*       by: hgrranzi <vkh.mariia@gmail.com>       */
/*                                                 */
/* *********************************************** */

#include "pipek.h"

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
	open_files(files, &head_cmd);
	exec_commands(&head_cmd);
	free_cmd(head_cmd);
	return (0);
}
