/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 20:54:55 by vchornyi          #+#    #+#             */
/*   Updated: 2018/11/24 20:54:56 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

unsigned int	right_rotate(unsigned int x, int n)
{
	return (x >> n) | (x << (32 - n));
}

size_t			right_rotate64(size_t x, int n)
{
	return (x >> n) | (x << (64 - n));
}

size_t			reverse_bytes(size_t num, int size)
{
	size_t	reverse_num;
	int		i;

	i = 0;
	reverse_num = 0;
	while (i < size)
	{
		reverse_num |= ((num >> 8 * i) & MAX_BYTE) << 8 * (size - i - 1);
		i++;
	}
	return (reverse_num);
}
