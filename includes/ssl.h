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
# include "sha256.h"
# include "sha512.h"

typedef char *t_function(char *mem, int fd);
typedef struct s_digest	t_digest;
typedef struct s_option	t_option;

struct 			s_option
{
	char 		is_quiet;
	char 		is_reverse;
	char 		is_stdin;
};

struct			s_digest
{
	char		*name;
	t_function	*digest;
};

char	*md5(char *mem, int fd);
char	*sha256(char *mem, int fd);
char	*sha224(char *mem, int fd);
char	*sha512(char *mem, int fd);
char	*sha384(char *mem, int fd);

t_digest g_digests[] =
{
	{"md5", md5},
	{"sha256", sha256},
	{"sha224", sha224},
	{"sha512", sha512},
	{"sha384", sha384}
};

#endif
