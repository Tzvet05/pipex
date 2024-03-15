/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 19:08:21 by ttrave            #+#    #+#             */
/*   Updated: 2024/01/27 18:16:59 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	ft_update_quote(char c, char quote)
{
	if (!quote && ft_in(c, QUOTES))
		quote = c;
	else if (quote == c)
		quote = 0;
	return (quote);
}
