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

void	error_message(char *reason, char *arg)
{
	ft_putstr("ft_ssl: ");
	ft_putstr(reason);
	ft_putstr(" '");
	ft_putstr(arg);
	ft_putendl("'");
}

void	error_exit(char *reason, char *arg)
{
	error_message(reason, arg);
	exit(1);
}

void	error_command(char *command)
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

void	format_output(char *hash, t_option *opt, char *digest_name, char *name)
{
	unsigned int	i;

	if (!opt->is_reverse && !opt->is_quiet)
	{
		i = 0;
		while (i < ft_strlen(digest_name))
			ft_putchar((char) ft_toupper(digest_name[i++]));
		ft_putstr(" (");
		ft_putstr(name);
		ft_putstr(") = ");
	}
	ft_putstr(hash);
	if (opt->is_reverse && !opt->is_quiet)
	{
		ft_putchar(' ');
		ft_putstr(name);
	}
	ft_putchar('\n');
	ft_strdel(&hash);
}

void	handle_string(char *str, t_option *opt, t_digest *digest)
{
	char	*hash;
	char	*formatted_name;
	size_t	length;

	hash = digest->digest(str,-1);
	length = ft_strlen(str);
	formatted_name = ft_strnew(length + 2);
	formatted_name[0] = '"';
	ft_strcpy(&formatted_name[1], str);
	formatted_name[length + 1] = '"';
	format_output(hash, opt, digest->name, formatted_name);
	ft_strdel(&formatted_name);
	opt->is_stdin = 0;
}

void	handle_stdin(t_digest *digest, t_option *opt)
{
	char	*stdin;
	char	*hash;

	stdin = ft_readfile(0, 100);
	ft_putstr(stdin);
	hash = digest->digest(stdin,-1);
	ft_putendl(hash);
	ft_strdel(&stdin);
	ft_strdel(&hash);
	opt->is_stdin = 0;
}

int		parse_options(int argc, char **argv, t_option *opt, t_digest *digest)
{
	int		i;
	char	option;

	opt->is_quiet = 0;
	opt->is_reverse = 0;
	opt->is_stdin = 1;
	i = 2;
	while (i < argc && argv[i][0] == '-')
	{
		if (ft_strlen(argv[i]) != 2)
			error_exit("Wrong option used", argv[i]);
		option = argv[i][1];
		if (option == 'p')
			handle_stdin(digest, opt);
		else if (option == 'q')
			opt->is_quiet = 1;
		else if (option == 'r')
			opt->is_reverse = 1;
		else if (option == 's' && i + 1 < argc)
			handle_string(argv[++i], opt, digest);
		else
			error_exit("Wrong option used", argv[i]);
		i++;
	}
	return i;
}

void	parse_args(int argc, char **argv, t_digest *digest)
{
	int			i;
	t_option	opt;
	char 		*hash;
	int			fd;

	i = parse_options(argc, argv, &opt, digest);
	if (i == argc && opt.is_stdin)
	{
		hash = digest->digest(argv[i], 0);
		ft_putendl(hash);
		ft_strdel(&hash);
	}
	while (i < argc)
	{
		fd = open(argv[i], O_RDONLY);
		if (fd < 0)
			error_message("No such file", argv[i]);
		else
		{
			hash = digest->digest(argv[i],fd);
			format_output(hash, &opt, digest->name, argv[i]);
			close(fd);
		}
		i++;
	}
}

int		main(int argc, char **argv)
{
	int	i;
	int	num_digests;

	num_digests = sizeof(g_digests) / sizeof(t_digest);
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
			error_command(argv[1]);
	}
	else
		ft_putendl("usage: ft_ssl command [command opts] [command args]");
	return (0);
}
