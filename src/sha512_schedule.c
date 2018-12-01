/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_schedule.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 17:34:25 by vchornyi          #+#    #+#             */
/*   Updated: 2018/12/01 17:34:26 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha512.h"

static size_t	schedule_rotates64(size_t num, int x, int y, int z)
{
	return (right_rotate64(num, x) ^ right_rotate64(num, y) ^ (num >> z));
}

void			prepare_message_schedule64(size_t *mem, size_t *schedule)
{
	unsigned char	i;
	size_t			sc0;
	size_t			sc1;

	i = 0;
	while (i < 16)
	{
		schedule[i] = reverse_bytes(mem[i], 8);
		i++;
	}
	while (i < 80)
	{
		sc0 = schedule_rotates64(schedule[i - 15], 1, 8, 7);
		sc1 = schedule_rotates64(schedule[i - 2], 19, 61, 6);
		schedule[i] = sc1 + schedule[i - 7] + sc0 + schedule[i - 16];
		i++;
	}
}

void			save_start_values64(size_t *start_values, t_buf64 *sh)
{
	unsigned char	i;

	i = 0;
	while (i < 8)
	{
		start_values[i] = sh->bf[i];
		i++;
	}
}

void			add_start_values512(size_t *start_values, t_buf64 *sh)
{
	unsigned char	i;

	i = 0;
	while (i < 8)
	{
		sh->bf[i] += start_values[i];
		i++;
	}
}
