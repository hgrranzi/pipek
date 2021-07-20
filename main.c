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

 void	take_commands(int argc, char **argv, t_cmd **head_cmd, char **envp)
{
	int		i;
	t_cmd	*current_cmd;

	i = 1;
	current_cmd = *head_cmd;
	while (++i < argc - 1)
	{
		current_cmd = malloc(sizeof(t_cmd));
		if (!current_cmd)
			error_and_exit(NULL);

	}
}

void	take_files(int argc, char **argv, char **files)
{
	if (argc < 5)
		error_and_exit(ERR_ARGS);
	files[INFILE] = argv[1];
	files[OUTFILE] = argv[argc - 1];
}

int	main(int argc, char **argv, char **envp)
{
	char	*files[2];
	t_cmd	*head_cmd;

	head_cmd = NULL;
	take_files(argc, argv, files);
	take_commands(argc, argv, &head_cmd, envp);
	return (0);
}
