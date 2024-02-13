/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes3_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 18:01:20 by ttrave            #+#    #+#             */
/*   Updated: 2024/01/27 18:01:21 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_close_pipes(int *pipes)
{
	size_t	i;

	i = 0;
	while (pipes[i] != -1)
	{
		close(pipes[i]);
		i++;
	}
}

void	ft_close_pipes_std(int *pipes)
{
	size_t	i;

	i = 0;
	while (pipes[i] != -1)
	{
		close(pipes[i]);
		i++;
	}
	close(0);
	close(1);
	close(2);
}

char	*ft_get_of(char **argv)
{
	size_t	i;

	i = 0;
	while (argv[i])
		i++;
	return (argv[i - 1]);
}

t_args	ft_init_vars(char **argv, char **envp, pid_t **pids, int **pipes)
{
	t_args	args;
	size_t	i;

	args.argv = argv;
	args.envp = envp;
	i = 0;
	while (argv[i])
		i++;
	i -= 3 + ft_strcmp(argv[1], HD);
	*pids = malloc(i * sizeof(pid_t));
	if (!*pids)
	{
		args.argv = NULL;
		return (args);
	}
	*pipes = malloc((2 * i + 1) * sizeof(int));
	if (!*pipes)
	{
		free(*pids);
		args.argv = NULL;
		return (args);
	}
	return (args);
}
