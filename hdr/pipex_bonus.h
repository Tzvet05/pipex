/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:19:37 by ttrave            #+#    #+#             */
/*   Updated: 2024/01/09 18:54:50 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

/* ----- INCLUDES ----- */

# include "./../libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>

/* ----- MACROS ----- */

// Generic macros
# define STDIN	0
# define STDOUT	1
# define HD	"here_doc"
# define QUOTES	"\'\""
# define WS	"\t\f\n\r\v "
# define CHARS	"0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

// Warning macro for ft_puterr()
# define WARN_LIMITER	"pipex: warning: here_doc: delimited by end-of-file (wanted '\
"

// Error strings macros for ft_puterr()
# define ERROR_MALLOC	"pipex: malloc: failed memory allocation\n"
# define ERROR_FOK	"pipex: no such file or directory: "
# define ERROR_XOK	"pipex: permission denied: "
# define ERROR_QUOTES	"pipex: unclosed quotes\n"
# define ERROR_ARGS	"pipex: 4 arguments minimum\n"
# define ERROR_ARGS_HD	"pipex: here_doc: 5 arguments minimum\n"
# define ERROR_DUP	"pipex: dup(2): failed fd reassignment\n"
# define ERROR_OPEN	"pipex: open: failed to open file: "
# define ERROR_CREATE	"pipex: open: failed to create a file\n"
# define ERROR_PIPE	"pipex: pipe: failed to create a pipe\n"
# define ERROR_FORK	"pipex: fork: failed to create child process\n"
# define ERROR_EXEC	"pipex: execve: failed to run new program\n"
# define ERROR_READ	"pipex: here_doc: read: failed to read stdin\n"
# define ERROR_WRITE	"pipex: write: failed to write\n"
# define ERROR_UNLINK	"pipex: here_doc: unlink: failed to delete file\n"
# define ERROR_TMP_FILE	"pipex: here_doc: temporary file corrupted\n"
# define ERROR_NO_CMD	"pipex: permission denied: ''\n"
# define ERROR_WAIT	"pipex: wait: failed to wait for child process\n"
# define ERROR_WRNG_CMD	": command not found\n"

// Error codes macros for exit()
# define ERRC_ARGS	1
# define ERRC_ARGS_HD	2
# define ERRC_QUOTES	3
# define ERRC_MALLOC	4
# define ERRC_OPEN	5
# define ERRC_DUP	6
# define ERRC_PIPE	7
# define ERRC_FORK	8
# define ERRC_EXEC	9
# define ERRC_CREATE	10
# define ERRC_UNLINK	11
# define ERRC_WRITE	12
# define ERRC_READ	13
# define ERRC_WAIT	14

/* ----- STRUCTURE ----- */

typedef struct s_args
{
	char	**argv;
	char	**envp;
}	t_args;

/* ----- PROTOTYPES ----- */

// pipex_bonus.c
int		main(int argc, char **argv, char **envp);

// ft_check_params_bonus.c
void	ft_check_params(int argc, char **argv);

// ft_cmds1_bonus.c
char	***ft_get_cmds(int argc, char **argv);

// ft_cmds2_bonus.c
char	ft_update_quote(char c, char quote);

// ft_paths1_bonus.c
char	**ft_get_paths(char **envp);

// ft_paths2_bonus.c
char	***ft_get_valid_paths(char **paths, char ***cmds);

// ft_utils_bonus.c
ssize_t	ft_puterr(char *error);
short	ft_append(char **buff_stock, char *buff, int to_append);

// ft_here_doc_bonus.c
short	ft_here_doc(char *limiter, char **filename);

// ft_file_gen_bonus.c
char	*ft_create_filename(void);
int		ft_create_file(char *filename);

// ft_pipes1_bonus.c
short	ft_start_pipes(char ***cmds, char *filename, char **argv, char **envp);

// ft_pipes2_bonus.c
short	ft_open_of(char **cmd, char **argv, char *outfile);
size_t	ft_count_cmds(char ***cmds);
short	ft_open_pipes(char ***cmds, int *pipes, pid_t *pids);
short	ft_open_infile(char *filename, int *pipes, short *start);

// ft_pipes3_bonus.c
void	ft_close_pipes(int *pipes);
void	ft_close_pipes_std(int *pipes);
char	*ft_get_of(char **argv);
t_args	ft_init_vars(char **argv, char **envp, pid_t **pids, int **pipes);

#endif
