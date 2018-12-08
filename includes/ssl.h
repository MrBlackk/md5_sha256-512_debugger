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
# include "digest.h"

typedef void	t_cmd_fun();
typedef struct s_cmd	t_cmd;

struct			s_cmd
{
	char		*name;
	t_cmd_fun	*cmd;
};

char			*md5(char *mem, int fd);
char			*sha256(char *mem, int fd);
char			*sha224(char *mem, int fd);
char			*sha512(char *mem, int fd);
char			*sha384(char *mem, int fd);

void			cmd_exit();
void			cmd_help();

char			**split_arg_line(char *line);
void			parse_args(int argc, char **argv, t_digest *digest);

t_digest		g_digests[] =
{
	{"md5", md5},
	{"sha256", sha256},
	{"sha224", sha224},
	{"sha512", sha512},
	{"sha384", sha384}
};

t_cmd			g_cmds[] =
{
	{"exit", cmd_exit},
	{"help", cmd_help}
};

#endif
