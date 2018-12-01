/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 20:54:55 by vchornyi          #+#    #+#             */
/*   Updated: 2018/10/22 20:54:56 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H

# include "libft.h"
# include "common.h"

# define MD5_LENGTH 32
# define MD5_BUF 4

typedef unsigned int t_round(unsigned int x, unsigned int y, unsigned int z);

#endif
