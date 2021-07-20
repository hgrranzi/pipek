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

typedef struct	s_cmd
{
	char	*name;
	char	**args;
	int		fd[2];

}				t_cmd;

#endif
