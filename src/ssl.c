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

char	*undefined(char *str)
{
	return (ft_strcat(ft_strdup("Undefined: "), str));
}

char	*md5(char *str)
{
	return (ft_strcat(ft_strdup("md5: "), str));
}

char	*sha256(char *str)
{
	return (ft_strcat(ft_strdup("sha256: "), str));
}

int		main(int argc, char **argv)
{
	int i;
	int num_digests;

	num_digests = sizeof(g_digests) / sizeof(struct s_digest);
	if (argc > 2)
	{
		i = 0;
		while (i < num_digests)
		{
			if (ft_strequ(argv[1], g_digests[i].name))
			{
				ft_putendl(g_digests[i].digest(argv[2]));
			}
			i++;
		}
	}
	return (0);
}
