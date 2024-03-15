/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:47:57 by ttrave            #+#    #+#             */
/*   Updated: 2024/01/27 18:16:48 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	ft_len_option(char *cmd)
{
	size_t	i;
	size_t	len;
	char	quote;
	char	c;

	i = 0;
	len = 0;
	quote = 0;
	c = cmd[0];
	while (c && (!ft_in(c, WS) || quote))
	{
		if (!quote && ft_in(c, QUOTES))
			quote = c;
		else if (c == quote)
			quote = 0;
		else
			len++;
		i++;
		c = cmd[i];
	}
	return (len);
}

static char	*ft_get_option(char *cmd)
{
	char	*option;
	size_t	i_cmd;
	size_t	i_option;
	size_t	len;
	char	quote;

	len = ft_len_option(cmd);
	option = malloc((len + 1) * sizeof(char));
	if (!option)
		return (NULL);
	option[len] = '\0';
	i_cmd = 0;
	i_option = 0;
	quote = 0;
	while (cmd[i_cmd] && (!ft_in(cmd[i_cmd], WS) || quote))
	{
		if (!quote && ft_in(cmd[i_cmd], QUOTES))
			quote = cmd[i_cmd];
		else if (cmd[i_cmd] == quote)
			quote = 0;
		else
			option[i_option++] = cmd[i_cmd];
		i_cmd++;
	}
	return (option);
}

static size_t	ft_count_options(char *cmd)
{
	size_t	nbr_options;
	size_t	i;
	char	c;
	char	quote;

	nbr_options = 0;
	i = 0;
	quote = 0;
	c = cmd[0];
	while (c)
	{
		if (!quote && !ft_in(c, WS) && (!i || ft_in(cmd[i - 1], WS)))
			nbr_options++;
		if (!quote && ft_in(c, QUOTES))
			quote = c;
		else if (c == quote)
			quote = 0;
		i++;
		c = cmd[i];
	}
	return (nbr_options);
}

static char	**ft_get_cmd_options(char *cmd)
{
	char	**cmd_options;
	size_t	i;
	size_t	i_cmd;
	char	quote;

	i = 0;
	i_cmd = 0;
	quote = 0;
	cmd_options = malloc((ft_count_options(cmd) + 1) * sizeof(char *));
	if (!cmd_options)
		return (NULL);
	cmd_options[ft_count_options(cmd)] = NULL;
	while (cmd[i])
	{
		if (!quote && !ft_in(cmd[i], WS) && (!i || ft_in(cmd[i - 1], WS)))
		{
			cmd_options[i_cmd] = ft_get_option(&cmd[i]);
			if (!cmd_options[i_cmd])
				return ((char **)ft_free_arr((void **)cmd_options));
			i_cmd++;
		}
		quote = ft_update_quote(cmd[i], quote);
		i++;
	}
	return (cmd_options);
}

char	***ft_get_cmds(int argc, char **argv)
{
	char	***cmds;
	size_t	i_cmd;
	size_t	i_argv;

	cmds = malloc((argc - 2) * sizeof(char **));
	if (!cmds)
		return (NULL);
	cmds[argc - 3] = NULL;
	i_argv = 2;
	i_cmd = 0;
	while (i_cmd < (size_t)argc - 3)
	{
		cmds[i_cmd] = ft_get_cmd_options(argv[i_argv]);
		if (!cmds[i_cmd])
		{
			ft_free_arr_arr((void ***)cmds);
			return (NULL);
		}
		i_cmd++;
		i_argv++;
	}
	return (cmds);
}
