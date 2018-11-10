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

typedef char *t_function(void *mem, size_t len);
typedef struct s_digest	t_digest;

struct			s_digest
{
	char		*name;
	t_function	*digest;
};

char	*md5(void *mem, size_t len);
char	*sha256(void *mem, size_t len);

t_digest g_digests[] =
{
	{"md5", md5},
	{"sha256", sha256}
};

#endif
