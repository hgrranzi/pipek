/* *********************************************** */
/*                                                 */
/*       by: hgrranzi <vkh.mariia@gmail.com>       */
/*                                                 */
/* *********************************************** */

#include "pipek.h"

char	**take_cmd_args(char *cmd_with_args)
{
	char	**cmd_args;

	cmd_args = split_line(cmd_with_args, ' ');
	if (!cmd_args)
		error_and_exit(NULL, NULL, 1);
	return (cmd_args);
}

char	**update_path(char **env_path)
{
	int		i;
	char	*new_path;

	i = 0;
	while (env_path[i])
	{
		new_path = aka_strjoin(env_path[i], "/");
		if (!new_path)
			error_and_exit(NULL, NULL, 1);
		free(env_path[i]);
		env_path[i] = new_path;
		i++;
	}
	return (env_path);
}

char	*check_cmd_path(char *cmd_name, char **possible_path)
{
	int		i;
	char	*cmd_path;

	i = 0;
	while (possible_path[i])
	{
		cmd_path = aka_strjoin(possible_path[i], cmd_name);
		if (!cmd_path)
			error_and_exit(NULL, NULL, 1);
		if (access(cmd_path, F_OK) == 0)
			break ;
		else
			free(cmd_path);
		i++;
	}
	if (possible_path[i] == NULL)
	{
		error_and_exit(cmd_name, ERR_CMD, 0);
		cmd_path = NULL;
	}
	return (cmd_path);
}

char	*take_cmd_path(char *cmd_name, char **possible_path)
{
	char	*cmd_path;

	if (strchr(cmd_name, '/'))
		cmd_path = cmd_name;
	else
	{
		cmd_path = check_cmd_path(cmd_name, possible_path);
		free(cmd_name);
	}
	return (cmd_path);
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
			error_and_exit(NULL, NULL, 1);
		new_cmd->args = take_cmd_args(argv[i]);
		new_cmd->args[CMD_PATH] = take_cmd_path(new_cmd->args[0], possible_path);
		new_cmd->fd[0] = 0;
		new_cmd->fd[1] = 1;
		new_cmd->next = NULL;
		*tail_cmd = new_cmd;
		tail_cmd = &new_cmd->next;
	}
}

char	**take_env_path(char **envp)
{
	int		i;
	char	**env_path;

	i = 0;
	env_path = NULL;
	while (envp[i])
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
		{
			env_path = split_line(&envp[i][5], ':');
			if (!env_path)
				error_and_exit(NULL, NULL, 1);
			break ;
		}
		i++;
	}
	if (!env_path)
	{
		env_path = split_line(CURRENT_DIR, ':');
		if (!env_path)
			error_and_exit(NULL, NULL, 1);
	}
	return (update_path(env_path));
}

void	take_files(int argc, char **argv, char **files)
{
	if (argc < 5)
		error_and_exit(NULL, ERR_ARGS, 1);
	files[INFILE] = argv[1];
	files[OUTFILE] = argv[argc - 1];
}
