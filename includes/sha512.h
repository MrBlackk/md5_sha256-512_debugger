/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 20:54:55 by vchornyi          #+#    #+#             */
/*   Updated: 2018/11/24 20:54:56 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA512_H
# define SHA512_H

# include "libft.h"
# include "common.h"

# define SHA512_LENGTH 128
# define SHA384_LENGTH 96
# define SHA512_BLOCK 128
# define SHA512_MESSAGE 120

typedef struct s_sh	t_sh;

struct	s_sh
{
	size_t	a;
	size_t	b;
	size_t	c;
	size_t	d;
	size_t	e;
	size_t	f;
	size_t	g;
	size_t	h;
	size_t	len;
};

#endif