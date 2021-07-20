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

t_cmd	*init_cmd(char *str)
{
	return (NULL);
}

void	check_args(int argc, char **argv, t_cmd **head_cmd, char **files)
{
	int		i;
	t_cmd	*current_cmd;

	if (argc < 5)
		error_and_exit(ERR_ARGS);
	i = 1;
	current_cmd = *head_cmd;
	files[INFILE] = argv[i];
	while (++i < argc - 1)
		current_cmd = init_cmd(argv[i]);
	files[OUTFILE] = argv[i];
}

int	main(int argc, char **argv)
{
	char	*files[2];
	t_cmd	*head_cmd;

	head_cmd = NULL;
	check_args(argc, argv, &head_cmd, files);
	return (0);
}
