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

static void	error_command(char *command)
{
	int	i;
	int	num_digests;

	error_message("Invalid command", command);
	ft_putendl("\nMessage Digest commands:");
	i = 0;
	num_digests = sizeof(g_digests) / sizeof(struct s_digest);
	while (i < num_digests)
	{
		ft_putendl(g_digests[i].name);
		i++;
	}
}

static void	parse(int argc, char **argv)
{
	int	i;
	int	num_digests;

	num_digests = sizeof(g_digests) / sizeof(t_digest);
	i = 0;
	while (i < num_digests)
	{
		if (ft_strequ(argv[1], g_digests[i].name))
			break ;
		i++;
	}
	if (i != num_digests)
		parse_args(argc, argv, &g_digests[i]);
	else
		error_command(argv[1]);
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
		while (1)
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
