/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 15:29:52 by vchornyi          #+#    #+#             */
/*   Updated: 2018/10/20 15:29:53 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_H
# define SSL_H

# include "md5.h"

# define UNDEFINED 0
# define MD5 1
# define SHA256 2

typedef char *t_function(char *var);
typedef struct s_digest	t_digest;

struct			s_digest
{
	char		*name;
	int			type;
	t_function	*digest;
};

char	*undefined(char *str);
char	*md5(char *str);
char	*sha256(char *str);

t_digest g_digests[] =
{
	{"undefined", UNDEFINED, undefined},
	{"md5", MD5, md5},
	{"sha256", SHA256, sha256}
};

#endif
