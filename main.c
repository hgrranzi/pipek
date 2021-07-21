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

char	*take_cmd_path(char *cmd_with_args, char **possible_path)
{
	int		i;
	int		cmd_len;
	char	*cmd_name;
	char	*cmd_path;

	i = 0;
	while (cmd_with_args[i])
	{
		i++;
		if (cmd_with_args[i] == ' ')
			break ;
	}
	cmd_name = strndup(cmd_with_args, i);
	if (!cmd_name)
		error_and_exit(NULL);
	i = 0;
	while (possible_path[i])
	{
		cmd_path = aka_strjoin(possible_path[i], cmd_name);
		if (!cmd_path)
			error_and_exit(NULL);
		if (access(cmd_path, F_OK))
			break ;
		else
			free(cmd_path); // no need to verify and the last one
		i++;
	}
	free(cmd_name);
	return (cmd_path);
}

char	**take_cmd_args(char *cmd_with_args)
{
	return (NULL);
}

 void	take_commands(int argc, char **argv, t_cmd **head_cmd, char **possible_path)
{
	int		i;
	t_cmd	*new_cmd;
	t_cmd	**tail_cmd;

	i = 1;
	new_cmd = NULL;
	tail_cmd = head_cmd;
	while (++i < argc - 1)
	{
		new_cmd = malloc(sizeof(t_cmd));
		if (!new_cmd)
			error_and_exit(NULL);
		new_cmd->path = take_cmd_path(argv[i], possible_path);
		new_cmd->args = take_cmd_args(argv[i]);
		new_cmd->fd[0] = 0;
		new_cmd->fd[1] = 1;
		new_cmd->next = NULL;
		*tail_cmd = new_cmd;
		tail_cmd = &new_cmd->next;
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
	take_commands(argc, argv, &head_cmd, envp); // instead of envp need a function that takes the PATH and split it
	return (0);
}
