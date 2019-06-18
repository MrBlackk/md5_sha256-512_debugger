/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_permutations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 17:50:23 by vchornyi          #+#    #+#             */
/*   Updated: 2018/12/01 17:50:27 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	set_memory_length(char *init_mem, size_t length, int size,
											char is_little_endian)
{
	int		i;
	char	byte;
	size_t	value;
	char	*mem;
	int		shift;

	i = 0;
	value = length * BITS_IN_BYTE;
	mem = init_mem;
	while (i < size)
	{
		shift = BITS_IN_BYTE * i;
		if (!is_little_endian)
			shift = BITS_IN_BYTE * (size - 1 - i);
		byte = (char)(value >> shift);
		ft_memset(mem, byte, 1);
		mem++;
		i++;
	}
}

void	permutations(char *init_mem, int fd, t_buf32 *buf, t_perm *permutation)
{
	char	mem[BLOCK_SIZE];
	size_t	len;

	if (DEBUG) {
		ft_printf("Initial words values:\n");
		for (int i = 0; i < buf->max_buf; i++) {
			ft_printf("%c: %x\n", i + 'A', buf->bf[i]);
		}
	}
	buf->len = get_next_block(&init_mem[0], mem, fd, BLOCK_SIZE);
	len = buf->len;
	while (len == BLOCK_SIZE)
	{
		permutation((unsigned int *)mem, buf);
		len = get_next_block(&init_mem[buf->len], mem, fd, BLOCK_SIZE);
		buf->len += len;
	}
	ft_memset(&mem[len], FIRST_BITE, 1);
	if (len >= MESSAGE_SIZE)
	{
		permutation((unsigned int *)mem, buf);
		buf->len += get_next_block(&init_mem[buf->len], mem, fd, BLOCK_SIZE);
	}
	set_memory_length(&mem[MESSAGE_SIZE], buf->len, 8, buf->is_little_endian);
	permutation((unsigned int *)mem, buf);
}

void	save_start_values(unsigned int *start_values, t_buf32 *buf)
{
	unsigned char	i;

	i = 0;
	while (i < buf->max_buf)
	{
		start_values[i] = buf->bf[i];
		i++;
	}
}

void	add_start_values(unsigned int *start_values, t_buf32 *buf)
{
	unsigned char	i;

	i = 0;
	while (i < buf->max_buf)
	{
		buf->bf[i] += start_values[i];
		i++;
	}
}
