/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 22:02:03 by ttrave            #+#    #+#             */
/*   Updated: 2024/02/08 19:18:55 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	ft_pipex(char **argv, char ***cmds, char **envp, short here_doc)
{
	char	*filename;
	short	error;

	if (here_doc)
	{
		error = ft_here_doc(argv[2], &filename);
		if (error)
		{
			ft_free_arr_arr((void ***)cmds);
			exit(error);
		}
	}
	else
		filename = argv[1];
	error = ft_start_pipes(cmds, filename, argv, envp);
	ft_free_arr_arr((void ***)cmds);
	if (here_doc && unlink(filename) == -1)
	{
		free(filename);
		ft_puterr(ERROR_UNLINK);
		exit(ERRC_UNLINK);
	}
	if (here_doc)
		free(filename);
	exit(error);
}

int	main(int argc, char **argv, char **envp)
{
	short	here_doc;
	char	**paths;
	char	***cmds;

	ft_check_params(argc, argv);
	here_doc = ft_strcmp(argv[1], HD);
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
	ft_pipex(argv, cmds, envp, here_doc);
	exit(0);
}
