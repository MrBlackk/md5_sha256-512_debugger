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

char	*sha256(void *mem, size_t len)
{
    (void)len; // suppress not used param warning
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
		if (i != num_digests && argc != 2) // todo: reading files from 0 fd
			ft_putendl(g_digests[i].digest(argv[2], ft_strlen(argv[2])));
		else
			error(argv[1]);
	}
	else
		ft_putendl("usage: ft_ssl command [command opts] [command args]");
	return (0);
}
