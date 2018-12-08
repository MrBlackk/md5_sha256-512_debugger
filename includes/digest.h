/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digest.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 16:07:00 by vchornyi          #+#    #+#             */
/*   Updated: 2018/12/08 16:07:01 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIGEST_H
# define DIGEST_H

# include "libft.h"
# include "common.h"

typedef char	*t_function(char *mem, int fd);
typedef struct s_digest	t_digest;
typedef struct s_option	t_option;

struct			s_option
{
	char	is_quiet;
	char	is_reverse;
	char	is_stdin;
};

struct			s_digest
{
	char		*name;
	t_function	*digest;
};

#endif
