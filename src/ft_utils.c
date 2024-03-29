/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:15:22 by ttrave            #+#    #+#             */
/*   Updated: 2024/01/27 18:17:56 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

ssize_t	ft_puterr(char *error)
{
	return (write(2, error, ft_strlen(error)));
}
