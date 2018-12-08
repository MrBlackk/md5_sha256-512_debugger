/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 15:28:24 by vchornyi          #+#    #+#             */
/*   Updated: 2018/10/20 15:28:26 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

void		cmd_help(void)
{
	int	i;
	int	num;

	ft_putendl("\nUsage:  ft_ssl command [command opts] [command args]");
	ft_putendl("opts:  -p -q -r -s");
	ft_putendl("\nMessage Digest commands:");
	i = 0;
	num = sizeof(g_digests) / sizeof(t_digest);
	while (i < num)
	{
		ft_putendl(g_digests[i].name);
		i++;
	}
	ft_putendl("\nft_ssl commands:");
	i = 0;
	num = sizeof(g_cmds) / sizeof(t_cmd);
	while (i < num)
	{
		ft_putendl(g_cmds[i].name);
		i++;
	}
}

static void	error_command(char *command)
{
	error_message("Invalid command", command);
	cmd_help();
}

static void	parse(int argc, char **argv)
{
	int	i;
	int	num;

	num = sizeof(g_digests) / sizeof(t_digest);
	i = 0;
	while (i < num)
	{
		if (ft_strequ(argv[1], g_digests[i].name))
			break ;
		i++;
	}
	if (i == num)
	{
		i = sizeof(g_cmds) / sizeof(t_cmd);
		while (--i >= 0)
			if (ft_strequ(argv[1], g_cmds[i].name))
				break ;
		if (i == -1)
			error_command(argv[1]);
		else
			g_cmds[i].cmd();
	}
	else
		parse_args(argc, argv, &g_digests[i]);
}

static void	free_args(char **args, int num)
{
	int	i;

	i = 0;
	while (i < num)
		free(args[i++]);
	free(args);
}

int			main(int argc, char **argv)
{
	char	*line;
	int		ret;
	char	**args;
	int		num;

	if (argc >= 2)
		parse(argc, argv);
	else
	{
		while (TRUE)
		{
			ft_putstr("ft_ssl> ");
			ret = get_next_line(0, &line);
			if (ret <= 0)
				break ;
			args = split_arg_line(line);
			num = 0;
			while (args[num] != NULL)
				num++;
			parse(num, args);
			ft_strdel(&line);
			free_args(args, num);
		}
	}
	return (0);
}
