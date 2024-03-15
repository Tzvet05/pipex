/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 22:02:03 by ttrave            #+#    #+#             */
/*   Updated: 2024/01/27 18:19:40 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_pipex(char **argv, char ***cmds, char **envp)
{
	char	*filename;
	short	error;

	filename = argv[1];
	error = ft_start_pipes(cmds, filename, argv, envp);
	ft_free_arr_arr((void ***)cmds);
	exit(error);
}

int	main(int argc, char **argv, char **envp)
{
	char	**paths;
	char	***cmds;

	ft_check_params(argc, argv);
	paths = ft_get_paths(envp);
	if (!paths)
	{
		ft_puterr(ERROR_MALLOC);
		exit(ERRC_MALLOC);
	}
	cmds = ft_get_cmds(argc, argv);
	if (!cmds)
	{
		ft_free_arr((void **)paths);
		ft_puterr(ERROR_MALLOC);
		exit(ERRC_MALLOC);
	}
	cmds = ft_get_valid_paths(paths, cmds);
	ft_free_arr((void **)paths);
	ft_pipex(argv, cmds, envp);
	exit(0);
}
