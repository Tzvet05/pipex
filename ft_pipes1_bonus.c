/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes1_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:23:03 by ttrave            #+#    #+#             */
/*   Updated: 2024/01/27 18:01:36 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	ft_child(char ***cmds, int *pipes, size_t i, char **envp)
{
	if ((i > 0 && dup2(pipes[i * 2 - 2], STDIN) == -1)
		|| (cmds[i + 1] && dup2(pipes[i * 2 + 1], STDOUT) == -1))
	{
		ft_close_pipes(pipes);
		ft_free_arr_arr((void ***)cmds);
		ft_puterr(ERROR_DUP);
		exit(ERRC_DUP);
	}
	ft_close_pipes(pipes);
	execve(cmds[i][0], cmds[i], envp);
	ft_free_arr_arr((void ***)cmds);
	free(pipes);
	close(0);
	close(1);
	close(2);
	ft_puterr(ERROR_EXEC);
	exit(ERRC_EXEC);
}

static void	ft_close_pipe(size_t i, int *pipes, size_t n_cmds)
{
	if (i >= 1)
		close(pipes[i * 2 - 2]);
	if (i < n_cmds - 1)
		close(pipes[i * 2 + 1]);
}

static short	ft_start_processes(char ***cmds, int *pipes, pid_t *pids,
		t_args args)
{
	size_t	i;
	short	error;

	i = 0;
	while (cmds[i])
	{
		pids[i] = -1;
		error = ft_open_of(cmds[i + 1], args.argv, ft_get_of(args.argv));
		if (error)
			return (error);
		if (cmds[i][0] && cmds[i][0][0])
		{
			pids[i] = fork();
			if (pids[i] == -1)
				return (ERRC_FORK + (0 & ft_puterr(ERROR_FORK)));
			if (!pids[i])
			{
				free(pids);
				ft_child(cmds, pipes, i, args.envp);
			}
		}
		ft_close_pipe(i, pipes, ft_count_cmds(cmds));
		i++;
	}
	return (0);
}

static short	ft_wait_pids(short error, pid_t *pids, int *pipes, char ***cmds)
{
	size_t	i;

	free(pipes);
	if (error)
	{
		free(pids);
		ft_close_pipes_std(pipes);
		return (error);
	}
	i = 0;
	while (cmds[i])
	{
		if (pids[i] != -1 && waitpid(pids[i], 0, 0) == -1)
		{
			ft_puterr(ERROR_WAIT);
			free(pids);
			return (ERRC_WAIT);
		}
		i++;
	}
	close(0);
	close(1);
	close(2);
	free(pids);
	return (0);
}

short	ft_start_pipes(char ***cmds, char *infile, char **argv, char **envp)
{
	pid_t	*pids;
	int		*pipes;
	short	error;
	short	start;
	t_args	args;

	args = ft_init_vars(argv, envp, &pids, &pipes);
	if (!args.argv)
		return (ERRC_MALLOC);
	if (ft_open_pipes(cmds, pipes, pids))
		return (ERRC_PIPE);
	error = ft_open_infile(infile, pipes, &start);
	if (error)
	{
		free(pids);
		free(pipes);
		ft_close_pipes(pipes);
		return (error);
	}
	error = ft_start_processes(&cmds[start], &pipes[2 * start], pids, args);
	close(pipes[(ft_count_cmds(cmds) - 1) * 2]);
	close(pipes[(ft_count_cmds(cmds) - 1) * 2 + 1]);
	error = ft_wait_pids(error, pids, pipes, &cmds[start]);
	return (error);
}
