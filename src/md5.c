/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 20:54:44 by vchornyi          #+#    #+#             */
/*   Updated: 2018/10/22 20:54:45 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

static unsigned int block_i = 0;

static unsigned int g_md5_const[64] =
{
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

static unsigned int g_md5_left_rotation[64] =
{
	7, 12, 17, 22, 7, 12, 17, 22,
	7, 12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20,
	5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23,
	4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21,
	6, 10, 15, 21, 6, 10, 15, 21
};

static unsigned int	md5_round(t_round f, unsigned int mem, t_buf32 *md, int i)
{
	return (md->bf[1] + left_rotate(f(md->bf[1], md->bf[2], md->bf[3]) +
				md->bf[0] + g_md5_const[i] + mem, g_md5_left_rotation[i]));
}

void    print_memory(void *memory, size_t len) {
	size_t i = 0;
	unsigned char *bytes = (unsigned char*)memory;
	while (i < len) {
		ft_printf("%08b ", bytes[i]);
		i++;
		if (i % 8 == 0) {
			ft_printf("\n");
		}
	}
	ft_printf("\n");
}

static void			permutation_md5(unsigned int *mem, t_buf32 *md)
{
	unsigned int	i;
	unsigned int	temp;
	unsigned int	start_values[4];

	save_start_values(start_values, md);
	if (DEBUG) {
		ft_printf("Block binary %u:\n", block_i);
		print_memory(mem, BLOCK_SIZE);
		ft_printf("Block decimal %u:\n", block_i);
		for (int j = 0; j < 16; j++) {
			ft_printf("[%2d] %zu\n", j, mem[j]);
		}
		block_i++;
		if (DEBUG) {
			ft_printf("\nStart words values A=%-11zu B=%-11zu C=%-11zu D=%-11zu\n", md->bf[0], md->bf[1], md->bf[2], md->bf[3]);
		}
		ft_printf("Words on each permutation step: \n");
	}
	i = 0;
	while (i < 64)
	{
		if (i < 16)
			temp = md5_round(first_round, mem[i], md, i);
		else if (i >= 16 && i < 32)
			temp = md5_round(second_round, mem[(5 * i + 1) % 16], md, i);
		else if (i >= 32 && i < 48)
			temp = md5_round(third_round, mem[(3 * i + 5) % 16], md, i);
		else
			temp = md5_round(fourth_round, mem[(7 * i) % 16], md, i);
		md->bf[0] = md->bf[3];
		md->bf[3] = md->bf[2];
		md->bf[2] = md->bf[1];
		md->bf[1] = temp;
		if (DEBUG) {
			ft_printf("[%2d] A=%-11zu B=%-11zu C=%-11zu D=%-11zu\n", i, md->bf[(i+1) % 4], md->bf[(i+2) % 4], md->bf[(i+3) % 4], md->bf[(i+4) % 4]);
		}
		i++;
	}
	add_start_values(start_values, md);
	if (DEBUG) {
		ft_printf("Processed A=%-11zu B=%-11zu C=%-11zu D=%-11zu\n\n", md->bf[0], md->bf[1], md->bf[2], md->bf[3]);
	}
}

static void			set_initial_values_md5(t_buf32 *md)
{
	md->bf[0] = 0x67452301;
	md->bf[1] = 0xefcdab89;
	md->bf[2] = 0x98badcfe;
	md->bf[3] = 0x10325476;
	md->max_buf = MD5_BUF;
	md->is_little_endian = TRUE;
	md->message_length = MD5_LENGTH;
	md->len = 0;
}

char				*md5(char *init_mem, int fd)
{
	t_buf32	md;

	if (DEBUG) {
		print_table(g_md5_const, 64, "constants", "%-11zu  ", "K");
		print_table(g_md5_left_rotation, 64, "per-round shift amounts", "%-2d  ", "s");
	}
	set_initial_values_md5(&md);
	permutations(init_mem, fd, &md, &permutation_md5);
	return (get_result(&md));
}
