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

void	check_args(int argc, char **argv, t_cmd *cmd, char **files)
{
	if (argc < 5)
		error_and_exit(ERR_ARGS);
}

int	main(int argc, char **argv)
{
	char	*files[2];
	t_cmd	cmd;


	check_args(argc, argv, &cmd, files);
	return (0);
}
