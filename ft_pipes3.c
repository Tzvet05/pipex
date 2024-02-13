/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 18:01:20 by ttrave            #+#    #+#             */
/*   Updated: 2024/01/27 18:17:48 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	ft_init_args(t_args *args, char **argv, char **envp)
{
	args->argv = argv;
	args->envp = envp;
}
