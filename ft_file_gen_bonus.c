/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_gen_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 20:37:23 by ttrave            #+#    #+#             */
/*   Updated: 2024/01/25 20:38:49 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*ft_init_filename(void)
{
	char	*filename;
	short	i;

	filename = malloc(22 * sizeof(char));
	if (!filename)
	{
		ft_puterr(ERROR_MALLOC);
		return (NULL);
	}
	filename[21] = '\0';
	filename[0] = '.';
	i = 1;
	while (i < 21)
	{
		filename[i] = CHARS[0];
		i++;
	}
	return (filename);
}

static size_t	ft_get_index(char c, char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

char	*ft_create_filename(void)
{
	char	*filename;
	short	i;

	filename = ft_init_filename();
	if (!filename)
		return (NULL);
	while (!access(filename, F_OK))
	{
		i = 1;
		if (filename[i] != CHARS[61])
			filename[i] = CHARS[ft_get_index(filename[i], CHARS) + 1];
		else
		{
			while (filename[i] == CHARS[61])
			{
				filename[i] = CHARS[0];
				i++;
			}
			filename[i] = CHARS[ft_get_index(filename[i], CHARS) + 1];
		}
	}
	return (filename);
}

int	ft_create_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDWR | O_CREAT, 0644);
	if (fd == -1)
	{
		free(filename);
		ft_puterr(ERROR_CREATE);
	}
	return (fd);
}
