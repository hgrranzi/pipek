/* *********************************************** */
/*                                                 */
/*       by: hgrranzi <vkh.mariia@gmail.com>       */
/*                                                 */
/* *********************************************** */

#include "pipek.h"

int	index_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			break ;
		i++;
	}
	return (i);
}

char	**free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
	return (NULL);
}

void	free_cmd(t_cmd *head_cmd)
{
	t_cmd	*cmd_ptr;

	cmd_ptr = head_cmd;
	while (head_cmd)
	{
		cmd_ptr = head_cmd;
		free_arr(head_cmd->args);
		head_cmd = head_cmd->next;
		free(cmd_ptr);
	}
}

char	*aka_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	j = 0;
	new_str = malloc((strlen(s1) + strlen(s2) + 1) * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		new_str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		new_str[i] = s2[j];
		i++;
		j++;
	}
	new_str[i] = '\0';
	return (new_str);
}

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
