/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 18:01:13 by ttrave            #+#    #+#             */
/*   Updated: 2024/01/27 18:17:40 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

short	ft_open_pipes(char ***cmds, int *pipes)
{
	size_t	i_pipe;
	size_t	i_cmd;

	i_pipe = 0;
	i_cmd = 0;
	while (cmds[i_cmd])
	{
		if (pipe(&pipes[i_pipe]) == -1)
		{
			pipes[i_pipe] = -1;
			ft_close_pipes(pipes);
			ft_puterr(ERROR_PIPE);
			return (-1);
		}
		i_pipe += 2;
		i_cmd++;
	}
	pipes[i_pipe] = -1;
	return (0);
}

size_t	ft_count_cmds(char ***cmds)
{
	size_t	i;

	i = 0;
	while (cmds[i])
		i++;
	return (i);
}

short	ft_skip_infile(int *pipes, short *start)
{
	if (dup2(pipes[0], STDIN) == -1)
	{
		ft_puterr(ERROR_DUP);
		return (ERRC_DUP);
	}
	close(pipes[0]);
	close(pipes[1]);
	*start = 1;
	return (0);
}

short	ft_open_infile(char *filename, int *pipes, short *start)
{
	int	fd;

	if (access(filename, R_OK) == -1)
	{
		ft_puterr(ERROR_FOK);
		ft_puterr(filename);
		ft_puterr("\n");
		return (ft_skip_infile(pipes, start));
	}
	*start = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_puterr(ERROR_OPEN);
		return (ERRC_OPEN);
	}
	if (dup2(fd, STDIN) == -1)
	{
		close(fd);
		ft_puterr(ERROR_DUP);
		return (ERRC_DUP);
	}
	close(fd);
	return (0);
}

short	ft_open_of(char **cmd, char *outfile)
{
	int	fd;

	if (cmd)
		return (0);
	fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_puterr(ERROR_OPEN);
		return (ERRC_OPEN);
	}
	if (dup2(fd, STDOUT) == -1)
	{
		ft_puterr(ERROR_DUP);
		return (ERRC_DUP);
	}
	close(fd);
	return (0);
}
