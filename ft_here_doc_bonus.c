/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:15:05 by ttrave            #+#    #+#             */
/*   Updated: 2024/01/27 16:37:33 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static short	ft_cmp_limiter(char *buffer, char *limiter)
{
	size_t	i;

	i = 0;
	while (limiter[i])
	{
		if (buffer[i] != limiter[i])
			return (0);
		i++;
	}
	if (buffer[i] == '\n' && buffer[i + 1] == '\0')
	{
		free(buffer);
		return (1);
	}
	return (0);
}

static short	ft_write_to_file(int fd, char **buffer, char *filename)
{
	size_t	i;

	i = 0;
	if (access(filename, W_OK) == -1)
	{
		free(*buffer);
		ft_puterr(ERROR_TMP_FILE);
		return (1);
	}
	while ((*buffer)[i] != '\n')
	{
		if (!(*buffer)[i])
			return (0);
		i++;
	}
	if (write(fd, *buffer, i + 1) == -1)
	{
		free(*buffer);
		ft_puterr(ERROR_WRITE);
		return (1);
	}
	free(*buffer);
	*buffer = NULL;
	return (0);
}

static short	ft_read_stdin(char *buffer_write, char *buffer, int *nbr_read,
		char *limiter)
{
	if (!buffer_write && write(STDOUT, ">", 1) == -1)
	{
		ft_puterr(ERROR_WRITE);
		return (ERRC_WRITE);
	}
	*nbr_read = read(STDIN, buffer, 10);
	if (*nbr_read == -1)
	{
		ft_puterr(ERROR_READ);
		return (ERRC_READ);
	}
	if (!*nbr_read && !buffer_write)
	{
		ft_puterr(WARN_LIMITER);
		ft_puterr(limiter);
		ft_puterr("')\n");
		return (0);
	}
	return (-1);
}

static short	ft_manage_stdin(int fd, char *limiter, char *filename)
{
	char	buffer[10];
	char	*buffer_write;
	int		nbr_read;
	short	error;

	buffer_write = NULL;
	while (1)
	{
		error = ft_read_stdin(buffer_write, buffer, &nbr_read, limiter);
		if (error >= 0)
		{
			free(buffer_write);
			return (error);
		}
		if (ft_append(&buffer_write, buffer, nbr_read))
		{
			ft_puterr(ERROR_MALLOC);
			return (ERRC_MALLOC);
		}
		if (buffer_write && ft_cmp_limiter(buffer_write, limiter))
			return (0);
		if (buffer_write && ft_write_to_file(fd, &buffer_write, filename))
			return (ERRC_WRITE);
	}
}

short	ft_here_doc(char *limiter, char **filename)
{
	short	error;
	int		fd;

	*filename = ft_create_filename();
	if (!filename)
		return (ERRC_MALLOC);
	fd = ft_create_file(*filename);
	if (fd == -1)
		return (ERRC_CREATE);
	error = ft_manage_stdin(fd, limiter, *filename);
	close(fd);
	if (error)
	{
		free(*filename);
		return (error);
	}
	return (0);
}
