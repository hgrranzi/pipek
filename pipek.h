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

# define ERR_ARGS "Too few arguments"
# define ERR_CMD "command not found"
# define INFILE 0
# define OUTFILE 1
# define IN 0
# define OUT 1
# define CURRENT_DIR "."
# define CMD_PATH 0
# define IS_CHILD 0

typedef struct s_cmd
{
	char			**args;
	int				fd[2];
	struct s_cmd	*next;

}				t_cmd;

void	error_and_exit(char *reason, char *error_message, int end);

void	take_files(int argc, char **argv, char **files);
char	**take_env_path(char **envp);
char	**update_path(char **env_path);
void	take_commands(int argc, char **argv, t_cmd **head_cmd, char **possible_path);
char	*take_cmd_path(char *cmd_with_args, char **possible_path);
char	*check_cmd_path(char *cmd_name, char **possible_path);
char	**take_cmd_args(char *cmd_with_args);

int		exec_commands(t_cmd **head_cmd);

char	**split_line(char *s, char c);
char	*trim_line(char *s, char c);
int		words_count(const char *s, char delimiter);

char	*aka_strjoin(char const *s1, char const *s2);
char	**free_arr(char **arr);
void	free_cmd(t_cmd *head_cmd);
int		index_char(char *str, char c);

#endif
