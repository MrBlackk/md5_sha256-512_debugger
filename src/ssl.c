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

char	*sha256(char *mem, int fd)
{
    (void)fd; // suppress not used param warning
	return (ft_strcat(ft_strdup("sha256: "), mem));
}

void	error(char *command)
{
	int i;
	int num_digests;

	ft_putstr("ft_ssl: Error: '");
	ft_putstr(command);
	ft_putendl("' is an invalid command.\n\nMessage Digest commands:");
	i = 0;
	num_digests = sizeof(g_digests) / sizeof(struct s_digest);
	while (i < num_digests)
	{
		ft_putendl(g_digests[i].name);
		i++;
	}
}

void	error_message(char *opt)
{
	ft_putstr("ft_ssl: Unknown option '"); // todo: add param to have possibility to change error message
	ft_putstr(opt);
	ft_putendl("'");
}

void	error_exit(char *error)
{
	error_message(error);
	exit(1);
}

void	enter_name(char *name, char is_str)
{
	if (is_str)
		ft_putchar('"');
	ft_putstr(name);
	if (is_str)
		ft_putchar('"');
}

void	format_output(char *hash, t_option *opt, char *digest_name, char *name, char is_str)
{
	if (!opt->is_reverse && !opt->is_quiet)
	{
		ft_putstr(digest_name);
		ft_putstr(" (");
		enter_name(name, is_str);
		ft_putstr(") = ");
	}
	ft_putstr(hash);
	if (opt->is_reverse && !opt->is_quiet)
	{
		ft_putchar(' ');
		enter_name(name, is_str);
	}
	ft_putchar('\n');
}

void	handle_string(char *str, t_option *opt, t_digest *digest)
{
	char *hash;

	hash = digest->digest(str,-1);
	format_output(hash, opt, digest->name, str, 1);
}

int		parse_options(int argc, char **argv, t_option *opt, t_digest *digest)
{
	int		i;
	char	option;

	opt->is_print = 0;
	opt->is_quiet = 0;
	opt->is_reverse = 0;
	i = 2;
	while (i < argc && argv[i][0] == '-')
	{
		if (ft_strlen(argv[i]) != 2)
			error_exit(argv[i]);
		option = argv[i][1];
		if (option == 'p')
			opt->is_print = 1;
		else if (option == 'q')
			opt->is_quiet = 1;
		else if (option == 'r')
			opt->is_reverse = 1;
		else if (option == 's' && i + 1 < argc)
			handle_string(argv[++i], opt, digest); // todo: order, -p should be first if present ?
		else
			error_exit(argv[i]);
		i++;
	}
	return i;
}

void	parse_args(int argc, char **argv, t_digest *digest)
{
	int			i;
	t_option	opt;
	char 		*hash;

	i = parse_options(argc, argv, &opt, digest);
	if (i == argc || opt.is_print) // todo: issue with last string -s "test" will be waiting for input
		ft_putendl(digest->digest(argv[i], 0));
	while (i < argc)
	{
		int fd = open(argv[i], O_RDONLY);
		if (fd < 0)
			error_message(argv[i]);
		else
		{
			hash = digest->digest(argv[i],fd);
			format_output(hash, &opt, digest->name, argv[i], 0);
			close(fd);
		}
		i++;
	}
}

int		main(int argc, char **argv)
{
	int i;
	int num_digests;

	num_digests = sizeof(g_digests) / sizeof(struct s_digest);
	if (argc >= 2)
	{
		i = 0;
		while (i < num_digests)
		{
			if (ft_strequ(argv[1], g_digests[i].name))
				break;
			i++;
		}
		if (i != num_digests)
			parse_args(argc, argv, &g_digests[i]);
		else
			error(argv[1]);
	}
	else
		ft_putendl("usage: ft_ssl command [command opts] [command args]");
	return (0);
}
