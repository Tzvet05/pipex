/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_ws.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:35:34 by ttrave            #+#    #+#             */
/*   Updated: 2024/01/13 17:35:48 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_skip_ws(size_t i, char *str)
{
	char	c;

	c = str[i];
	while (c && ft_in(c, "\t\r\v\n\f "))
	{
		i++;
		c = str[i];
	}
	return (i);
}
