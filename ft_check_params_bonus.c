/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_params_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 19:05:06 by ttrave            #+#    #+#             */
/*   Updated: 2024/01/27 18:16:16 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

static void	ft_check_quotes(int argc, char **argv, short here_doc)
{
	char	*arg;
	size_t	i_argv;

	i_argv = 2 + here_doc;
	arg = argv[i_argv];
	while (i_argv < (size_t)argc - (size_t)here_doc - 1)
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
	short	here_doc;

	if (argc < 5)
	{
		ft_puterr(ERROR_ARGS);
		exit(ERRC_ARGS);
	}
	here_doc = ft_strcmp(argv[1], HD);
	if (here_doc && argc < 6)
	{
		ft_puterr(ERROR_ARGS_HD);
		exit(ERRC_ARGS_HD);
	}
	ft_check_quotes(argc, argv, here_doc);
}
