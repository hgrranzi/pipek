/* *********************************************** */
/*                                                 */
/*       by: hgrranzi <vkh.mariia@gmail.com>       */
/*                                                 */
/* *********************************************** */

#include "pipek.h"

int	exec_commands(t_cmd **head_cmd, char **envp)
{
	t_cmd	*head_cmd_p;
	pid_t	pid;

	head_cmd_p = *head_cmd;
	while (head_cmd_p)
	{
		pid = fork();
		if (pid == IS_CHILD)
		{
			if (head_cmd_p->args[CMD_PATH])
			{
				execve(head_cmd_p->args[CMD_PATH], head_cmd_p->args, envp);
				error_and_exit(head_cmd_p->args[CMD_PATH], NULL, 1);
			}
			return (0);
		}
		else
			head_cmd_p = head_cmd_p->next;
	}
	if (pid != IS_CHILD)
		wait(NULL);
	return (0);
}
