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
# define SHA512_BLOCK 128
# define SHA512_MESSAGE 112
# define SHA384_LENGTH 96

typedef struct s_buf64	t_buf64;

struct	s_buf64
{
	size_t			buf[8];
	unsigned char	message_length;
	size_t			len;
};

#endif