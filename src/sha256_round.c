/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_round.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 17:07:56 by vchornyi          #+#    #+#             */
/*   Updated: 2018/12/01 17:07:57 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"

static unsigned int	schedule_rotates(unsigned int num, int x, int y, int z)
{
	return (right_rotate(num, x) ^ right_rotate(num, y) ^ (num >> z));
}

void				prepare_msg_schedule(unsigned int *mem, unsigned int *scd)
{
	unsigned char	i;
	unsigned int	sc0;
	unsigned int	sc1;

	i = 0;
	while (i < 16)
	{
		scd[i] = (unsigned int)reverse_bytes(mem[i], 4);
		i++;
	}
	while (i < 64)
	{
		sc0 = schedule_rotates(scd[i - 15], 7, 18, 3);
		sc1 = schedule_rotates(scd[i - 2], 17, 19, 10);
		scd[i] = sc1 + scd[i - 7] + sc0 + scd[i - 16];
		i++;
	}
}

unsigned int		sum(unsigned int num, int x, int y, int z)
{
	return (right_rotate(num, x) ^ right_rotate(num, y) ^ right_rotate(num, z));
}

unsigned int		ch(unsigned int x, unsigned int y, unsigned int z)
{
	return (x & y) ^ (~x & z);
}

unsigned int		maj(unsigned int x, unsigned int y, unsigned int z)
{
	return (x & y) ^ (x & z) ^ (y & z);
}
