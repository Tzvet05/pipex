/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_params.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 19:05:06 by ttrave            #+#    #+#             */
/*   Updated: 2024/01/27 18:16:32 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static short	ft_count_quotes(char *arg)
{
	char	quote;
	size_t	nbr_quotes;
	size_t	i;
	char	c;

	quote = 0;
	nbr_quotes = 0;
	i = 0;
	c = arg[0];
	while (c)
	{
		if ((!quote && ft_in(c, QUOTES)) || c == quote)
			nbr_quotes++;
		if (!quote && ft_in(c, QUOTES))
			quote = c;
		else if (c == quote)
			quote = 0;
		i++;
		c = arg[i];
	}
	return (nbr_quotes);
}

static void	ft_check_quotes(int argc, char **argv)
{
	char	*arg;
	size_t	i_argv;

	i_argv = 2;
	arg = argv[i_argv];
	while (i_argv < (size_t)argc - 1)
	{
		if (ft_count_quotes(arg) % 2 != 0)
		{
			ft_puterr(ERROR_QUOTES);
			exit(ERRC_QUOTES);
		}
		i_argv++;
		arg = argv[i_argv];
	}
}

void	ft_check_params(int argc, char **argv)
{
	if (argc < 5)
	{
		ft_puterr(ERROR_ARGS);
		exit(ERRC_ARGS);
	}
	if (argc > 5)
	{
		ft_puterr(ERROR_NB_PIPES);
		exit(ERRC_NB_PIPES);
	}
	ft_check_quotes(argc, argv);
}
