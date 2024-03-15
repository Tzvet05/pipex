/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paths_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 23:31:14 by ttrave            #+#    #+#             */
/*   Updated: 2024/01/16 15:57:25 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	**ft_empty_arr(void)
{
	char	**arr;

	arr = malloc(2 * sizeof(char *));
	if (!arr)
		return (NULL);
	arr[0] = malloc(sizeof(char));
	if (!arr[0])
	{
		free(arr);
		return (NULL);
	}
	arr[0][0] = '\0';
	arr[1] = NULL;
	return (arr);
}

char	**ft_get_paths(char **envp)
{
	char	**paths;
	char	*variable;
	size_t	i;

	i = 0;
	variable = envp[0];
	while (variable && !ft_strncmp(variable, "PATH=", 5))
	{
		i++;
		variable = envp[i];
	}
	if (!variable || !variable[5])
		paths = ft_empty_arr();
	else
		paths = ft_split(&variable[5], ':');
	if (!paths)
	{
		ft_puterr(ERROR_MALLOC);
		exit(ERRC_MALLOC);
	}
	return (paths);
}
