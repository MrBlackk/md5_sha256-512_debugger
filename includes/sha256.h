/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 20:54:55 by vchornyi          #+#    #+#             */
/*   Updated: 2018/11/24 20:54:56 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA256_H
# define SHA256_H

# include "libft.h"
# include "common.h"

# define SHA256_LENGTH 64
# define SHA256_BUF 8
# define SHA224_LENGTH 56
# define SHA224_BUF 8

void			prepare_msg_schedule(unsigned int *mem, unsigned int *scd);
unsigned int	sum(unsigned int num, int x, int y, int z);
unsigned int	ch(unsigned int x, unsigned int y, unsigned int z);
unsigned int	maj(unsigned int x, unsigned int y, unsigned int z);

#endif
