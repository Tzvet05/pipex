/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:19:37 by ttrave            #+#    #+#             */
/*   Updated: 2024/01/27 18:19:46 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/* ----- INCLUDES ----- */

# include "./libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>

/* ----- MACROS ----- */

// Generic macros
# define STDIN	0
# define STDOUT	1
# define QUOTES	"\'\""
# define WS	"\t\f\n\r\v "

// Error strings macros for ft_puterr()
# define ERROR_MALLOC	"pipex: malloc: failed memory allocation\n"
# define ERROR_FOK	"pipex: no such file or directory: "
# define ERROR_XOK	"pipex: permission denied: "
# define ERROR_QUOTES	"pipex: unclosed quotes\n"
# define ERROR_ARGS	"pipex: 4 arguments minimum\n"
# define ERROR_DUP	"pipex: dup(2): failed fd reassignment\n"
# define ERROR_OPEN	"pipex: open: failed to open file: "
# define ERROR_PIPE	"pipex: pipe: failed to create a pipe\n"
# define ERROR_FORK	"pipex: fork: failed to create child process\n"
# define ERROR_EXEC	"pipex: execve: failed to run new program\n"
# define ERROR_NB_PIPES	"pipex: cannot pipe more than 2 commands\n"
# define ERROR_NO_CMD	"pipex: permission denied: ''\n"
# define ERROR_WAIT	"pipex: wait: failed to wait for child process\n"

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
# define ERRC_WAIT	14
# define ERRC_NB_PIPES	15

/* ----- STRUCTURE ----- */

typedef struct s_args
{
	char	**argv;
	char	**envp;
}	t_args;

/* ----- PROTOTYPES ----- */

// pipex.c
int		main(int argc, char **argv, char **envp);

// ft_check_params.c
void	ft_check_params(int argc, char **argv);

// ft_cmds1.c
char	***ft_get_cmds(int argc, char **argv);

// ft_cmds2.c
char	ft_update_quote(char c, char quote);

// ft_paths1.c
char	**ft_get_paths(char **envp);

// ft_paths2.c
char	***ft_get_valid_paths(char **paths, char ***cmds);

// ft_utils.c
ssize_t	ft_puterr(char *error);

// ft_pipes1.c
short	ft_start_pipes(char ***cmds, char *filename, char **argv, char **envp);

// ft_pipes2.c
short	ft_open_of(char **cmd, char *outfile);
size_t	ft_count_cmds(char ***cmds);
short	ft_open_pipes(char ***cmds, int *pipes);
short	ft_open_infile(char *filename, int *pipes, short *start);

// ft_pipes3.c
void	ft_close_pipes(int *pipes);
char	*ft_get_of(char **argv);
void	ft_init_args(t_args *args, char **argv, char **envp);

#endif
