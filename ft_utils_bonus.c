/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:15:22 by ttrave            #+#    #+#             */
/*   Updated: 2024/01/16 14:18:00 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

ssize_t	ft_puterr(char *error)
{
	return (write(2, error, ft_strlen(error)));
}

short	ft_append(char **buff_stock, char *buff, int to_append)
{
	char	*new;
	size_t	len_stock;

	len_stock = 0;
	if (*buff_stock)
		len_stock = ft_strlen(*buff_stock);
	new = malloc((len_stock + to_append + 1) * sizeof(char));
	if (!new)
	{
		free(*buff_stock);
		ft_puterr(ERROR_MALLOC);
		return (ERRC_MALLOC);
	}
	new[len_stock + to_append] = '\0';
	ft_memcpy(new, *buff_stock, len_stock);
	ft_memcpy(&new[len_stock], buff, to_append);
	free(*buff_stock);
	*buff_stock = new;
	return (0);
}
