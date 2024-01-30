/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paths2_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:23:58 by ttrave            #+#    #+#             */
/*   Updated: 2024/01/28 16:17:17 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static short	ft_access_path(char *path_cmd, short *file_exists)
{
	if (!access(path_cmd, F_OK))
	{
		if (!access(path_cmd, X_OK))
			return (0);
		*file_exists = 1;
	}
	return (1);
}

static char	*ft_path_join(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	l_s1;
	size_t	l_s2;

	l_s1 = ft_strlen(s1);
	l_s2 = ft_strlen(s2);
	new_str = malloc((l_s1 + l_s2 + 2) * sizeof(char));
	if (!new_str)
		return (NULL);
	new_str[l_s1 + l_s2 + 1] = '\0';
	ft_memcpy(new_str, s1, l_s1);
	new_str[l_s1] = '/';
	ft_memcpy(&new_str[l_s1 + 1], s2, l_s2);
	return (new_str);
}

static char	*ft_no_cmd(char **cmd_options, short file_exists)
{
	size_t	i;

	i = 0;
	if (file_exists)
	{
		ft_puterr(ERROR_XOK);
		ft_puterr(cmd_options[0]);
		ft_puterr("\n");
	}
	else
	{
		ft_puterr(ERROR_FOK);
		ft_puterr(cmd_options[0]);
		ft_puterr("\n");
	}
	while (cmd_options[i])
	{
		free(cmd_options[i]);
		i++;
	}
	return (NULL);
}

static short	ft_find_valid_path(char **paths, char ***cmd_options)
{
	short	file_exists;
	char	*path_cmd;
	size_t	i;

	i = 0;
	file_exists = 0;
	if (!ft_access_path((*cmd_options)[0], &file_exists))
		return (0);
	while (paths[i])
	{
		path_cmd = ft_path_join(paths[i], (*cmd_options)[0]);
		if (!path_cmd)
			return (1);
		if (!ft_access_path(path_cmd, &file_exists))
		{
			free((*cmd_options[0]));
			(*cmd_options[0]) = path_cmd;
			return (0);
		}
		free(path_cmd);
		i++;
	}
	(*cmd_options)[0] = ft_no_cmd((*cmd_options), file_exists);
	return (0);
}

char	***ft_get_valid_paths(char **paths, char ***cmds)
{
	size_t	i;

	i = 0;
	while (cmds[i])
	{
		if (!cmds[i][0] || !cmds[i][0][0])
			ft_puterr(ERROR_NO_CMD);
		else if (ft_find_valid_path(paths, &cmds[i]))
		{
			ft_free_arr_arr((void ***)cmds);
			ft_free_arr((void **)paths);
			ft_puterr(ERROR_MALLOC);
			exit(ERRC_MALLOC);
		}
		i++;
	}
	return (cmds);
}
