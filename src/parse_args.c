/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 15:48:02 by vchornyi          #+#    #+#             */
/*   Updated: 2018/12/08 15:48:04 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "digest.h"

static void	format_output(char *hash, t_option *opt, char *dg_name, char *name)
{
	unsigned int	i;

	if (!opt->is_reverse && !opt->is_quiet)
	{
		i = 0;
		while (i < ft_strlen(dg_name))
			ft_putchar((char)ft_toupper(dg_name[i++]));
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

static void	handle_string(char *str, t_option *opt, t_digest *digest)
{
	char	*hash;
	char	*formatted_name;
	size_t	length;

	hash = digest->digest(str, -1);
	length = ft_strlen(str);
	formatted_name = ft_strnew(length + 2);
	formatted_name[0] = '"';
	ft_strcpy(&formatted_name[1], str);
	formatted_name[length + 1] = '"';
	format_output(hash, opt, digest->name, formatted_name);
	ft_strdel(&formatted_name);
	opt->is_stdin = 0;
}

static void	handle_stdin(t_digest *digest, t_option *opt)
{
	char	*stdin;
	char	*hash;

	stdin = ft_readfile(0, 100);
	ft_putstr(stdin);
	hash = digest->digest(stdin, -1);
	ft_putendl(hash);
	ft_strdel(&stdin);
	ft_strdel(&hash);
	opt->is_stdin = 0;
}

static int	parse_options(int argc, char **argv, t_option *opt, t_digest *dgst)
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
			return (error_return("Wrong option used", argv[i]));
		option = argv[i][1];
		if (option == 'p')
			handle_stdin(dgst, opt);
		else if (option == 'q')
			opt->is_quiet = 1;
		else if (option == 'r')
			opt->is_reverse = 1;
		else if (option == 's' && i + 1 < argc)
			handle_string(argv[++i], opt, dgst);
		else
			return (error_return("Wrong option used", argv[i]));
		i++;
	}
	return (i);
}

void		parse_args(int argc, char **argv, t_digest *digest)
{
	int			i;
	t_option	opt;
	char		*hash;
	int			fd;

	i = parse_options(argc, argv, &opt, digest);
	if (i == argc && opt.is_stdin)
	{
		hash = digest->digest(argv[i], 0);
		ft_putendl(hash);
		ft_strdel(&hash);
	}
	while (i != -1 && i < argc)
	{
		fd = open(argv[i], O_RDONLY);
		if (fd < 0)
			error_message("No such file", argv[i]);
		else
		{
			hash = digest->digest(argv[i], fd);
			format_output(hash, &opt, digest->name, argv[i]);
			close(fd);
		}
		i++;
	}
}
