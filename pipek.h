/* *********************************************** */
/*                                                 */
/*       by: hgrranzi <vkh.mariia@gmail.com>       */
/*                                                 */
/* *********************************************** */

#ifndef PIPEK_H
# define PIPEK_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>

# define ERR_ARGS "Too few arguments\n"
# define INFILE 0
# define OUTFILE 1

typedef struct	s_cmd
{
	char			*name;
	char			**args;
	int				fd[2];
	struct s_cmd	*next;

}				t_cmd;

void	check_args(int argc, char **argv, t_cmd **head_cmd, char **files);
void	error_and_exit(char *error_message);

#endif
