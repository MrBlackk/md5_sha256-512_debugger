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

unsigned int g_md5_const[64] =
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

unsigned int g_md5_left_rotation[64] =
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

unsigned int	first_round(unsigned int x, unsigned int y, unsigned int z)
{
    return (x & y) | ((~x) & z);
}

unsigned int	second_round(unsigned int x, unsigned int y, unsigned int z)
{
    return (x & z) | ((~z) & y);
}

unsigned int	third_round(unsigned int x, unsigned int y, unsigned int z)
{
    return x ^ y ^ z;
}

unsigned int	fourth_round(unsigned int x, unsigned int y, unsigned int z)
{
    return y ^ ((~z) | x);
}

unsigned int	left_rotate(unsigned int x, int n)
{
	return (x << n) | (x >> (32 - n));
}

unsigned int	md5_round(t_round round_func, unsigned int mem, t_md *md, int i)
{
	return md->b + left_rotate(round_func(md->b, md->c, md->d) +
			+ md->a + g_md5_const[i] + mem, g_md5_left_rotation[i]);
}

unsigned int	round_result(unsigned int *mem, t_md *md, int i)
{
	if (i < 16)
		return md5_round(first_round, mem[i], md, i);
	else if (i >= 16 && i < 32)
		return md5_round(second_round, mem[(5 * i + 1) % 16], md, i);
	else if (i >= 32 && i < 48)
		return md5_round(third_round, mem[(3 * i + 5) % 16], md, i);
	else
		return md5_round(fourth_round, mem[(7 * i) % 16], md, i);
}

void	permutation(unsigned int *mem, t_md *md)
{
	unsigned int	i;
	unsigned int	temp;
	unsigned int	start_values[4];

	start_values[0] = md->a;
	start_values[1] = md->b;
	start_values[2] = md->c;
	start_values[3] = md->d;
	i = 0;
	while (i < 64)
	{
		temp = round_result(mem, md, i);
		md->a = md->d;
		md->d = md->c;
		md->c = md->b;
		md->b = temp;
		i++;
	}
	md->a += start_values[0];
	md->b += start_values[1];
	md->c += start_values[2];
	md->d += start_values[3];
}

static void	set_initial_values(t_md *md)
{
	md->a = 0x67452301;
	md->b = 0xefcdab89;
	md->c = 0x98badcfe;
	md->d = 0x10325476;
}

char 	*get_result(t_md *md)
{
	char	res[MD5_LENGTH + 1];

	ft_bzero(&res, MD5_LENGTH + 1);
	result(res, md->a, 0, 1);
	result(res, md->b, 8, 1);
	result(res, md->c, 16, 1);
	result(res, md->d, 24, 1);
	return ft_strdup(res);
}

char	*md5(char *init_mem, int fd)
{
    char	mem[BLOCK_SIZE];
    t_md	md;
	size_t	len;

	set_initial_values(&md);
	md.len = get_next_block(&init_mem[0], mem, fd, BLOCK_SIZE);
	len = md.len;
	while (len == BLOCK_SIZE)
	{
		permutation((unsigned int *) mem, &md);
		len = get_next_block(&init_mem[md.len], mem, fd, BLOCK_SIZE);
		md.len += len;
	}
	ft_memset(&mem[len], FIRST_BITE, 1);
	if (len >= MESSAGE_SIZE)
	{
		permutation((unsigned int *) mem, &md);
		md.len += get_next_block(&init_mem[md.len], mem, fd, BLOCK_SIZE);
	}
	set_memory_length(&mem[MESSAGE_SIZE], md.len, 1);
	permutation((unsigned int *) mem, &md);
	return get_result(&md);
}
