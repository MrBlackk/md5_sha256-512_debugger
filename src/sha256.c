/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 20:54:55 by vchornyi          #+#    #+#             */
/*   Updated: 2018/11/24 20:54:56 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"

unsigned int g_sha256_const[64] =
{
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

static void	set_initial_values_sha256(t_sha *sha)
{
	sha->a = 0x6a09e667;
	sha->b = 0xbb67ae85;
	sha->c = 0x3c6ef372;
	sha->d = 0xa54ff53a;
	sha->e = 0x510e527f;
	sha->f = 0x9b05688c;
	sha->g = 0x1f83d9ab;
	sha->h = 0x5be0cd19;
}

static void	set_initial_values_sha224(t_sha *sha)
{
	sha->a = 0xc1059ed8;
	sha->b = 0x367cd507;
	sha->c = 0x3070dd17;
	sha->d = 0xf70e5939;
	sha->e = 0xffc00b31;
	sha->f = 0x68581511;
	sha->g = 0x64f98fa7;
	sha->h = 0xbefa4fa4;
}

void	save_start_values(unsigned int start_values[8], t_sha *sha)
{
	start_values[0] = sha->a;
	start_values[1] = sha->b;
	start_values[2] = sha->c;
	start_values[3] = sha->d;
	start_values[4] = sha->e;
	start_values[5] = sha->f;
	start_values[6] = sha->g;
	start_values[7] = sha->h;
}

void	add_start_values(unsigned int start_values[8], t_sha *sha)
{
	sha->a += start_values[0];
	sha->b += start_values[1];
	sha->c += start_values[2];
	sha->d += start_values[3];
	sha->e += start_values[4];
	sha->f += start_values[5];
	sha->g += start_values[6];
	sha->h += start_values[7];
}

void	debug_vars(t_sha *sha)
{
	ft_printf("%X ", sha->a);
	ft_printf("%X ", sha->b);
	ft_printf("%X ", sha->c);
	ft_printf("%X ", sha->d);
	ft_printf("%X ", sha->e);
	ft_printf("%X ", sha->f);
	ft_printf("%X ", sha->g);
	ft_printf("%X\n", sha->h);
}

unsigned int	right_rotate(unsigned int x, int n)
{
	return (x >> n) | (x << (32 - n));
}

unsigned int	schedule_rotates(unsigned int num, int x, int y, int z)
{
	return right_rotate(num, x) ^ right_rotate(num, y) ^ (num >> z);
}


void	prepare_message_schedule(unsigned int *mem, unsigned int *schedule)
{
	unsigned char	i;
	unsigned int	sc0;
	unsigned int	sc1;

	i = 0;
	while (i < 16)
	{
		schedule[i] = (unsigned int) reverse_bytes(mem[i], 4);
		i++;
	}
	while (i < 64)
	{
		sc0 = schedule_rotates(schedule[i - 15], 7, 18, 3);
		sc1 = schedule_rotates(schedule[i - 2], 17, 19, 10);
		schedule[i] = sc1 + schedule[i - 7] + sc0 + schedule[i - 16];
		i++;
	}
}

unsigned int	sum(unsigned int num, int x, int y, int z)
{
	return right_rotate(num, x) ^ right_rotate(num, y) ^ right_rotate(num, z);
}

unsigned int	ch(unsigned int x, unsigned int y, unsigned int z)
{
	return (x & y) ^ (~x & z);
}

unsigned int	maj(unsigned int x, unsigned int y, unsigned int z)
{
	return (x & y) ^ (x & z) ^ (y & z);
}
void	perm(unsigned int *mem, t_sha *sha)
{
	unsigned char	i;
	unsigned int	start_values[8];
	unsigned int	schedule[64];
	unsigned int	temp1;
	unsigned int	temp2;

	i = 0;
	prepare_message_schedule(mem, schedule);
	save_start_values(start_values, sha);
	while (i < 64)
	{
		temp1 = sha->h + sum(sha->e, 6, 11, 25) + ch(sha->e, sha->f, sha->g) +
				+ g_sha256_const[i] + schedule[i];
		temp2 = sum(sha->a, 2, 13, 22) + maj(sha->a, sha->b, sha->c);
		sha->h = sha->g;
		sha->g = sha->f;
		sha->f = sha->e;
		sha->e = sha->d + temp1;
		sha->d = sha->c;
		sha->c = sha->b;
		sha->b = sha->a;
		sha->a = temp1 + temp2;
		i++;
	}
	add_start_values(start_values, sha);
}

char 	*get_result_sha256(t_sha *sha)
{
	char	res[SHA256_LENGTH + 1];

	ft_bzero(&res, SHA256_LENGTH + 1);
	result(res, sha->a, 0, 0, 32);
	result(res, sha->b, 8, 0, 32);
	result(res, sha->c, 16, 0, 32);
	result(res, sha->d, 24, 0, 32);
	result(res, sha->e, 32, 0, 32);
	result(res, sha->f, 40, 0, 32);
	result(res, sha->g, 48, 0, 32);
	result(res, sha->h, 56, 0, 32);
	return ft_strdup(res);
}

char 	*get_result_sha224(t_sha *sha)
{
	char	res[SHA224_LENGTH + 1];

	ft_bzero(&res, SHA224_LENGTH + 1);
	result(res, sha->a, 0, 0, 32);
	result(res, sha->b, 8, 0, 32);
	result(res, sha->c, 16, 0, 32);
	result(res, sha->d, 24, 0, 32);
	result(res, sha->e, 32, 0, 32);
	result(res, sha->f, 40, 0, 32);
	result(res, sha->g, 48, 0, 32);
	return ft_strdup(res);
}

void	sha_permutations(char *init_mem, int fd, t_sha *sha)
{
	char	mem[BLOCK_SIZE];
	size_t	len;

	sha->len = get_next_block(&init_mem[0], mem, fd, BLOCK_SIZE);
	len = sha->len;
	while (len == BLOCK_SIZE)
	{
		perm((unsigned int *) mem, sha);
		len = get_next_block(&init_mem[sha->len], mem, fd, BLOCK_SIZE);
		sha->len += len;
	}
	ft_memset(&mem[len], FIRST_BITE, 1);
	if (len >= MESSAGE_SIZE)
	{
		perm((unsigned int *) mem, sha);
		sha->len += get_next_block(&init_mem[sha->len], mem, fd, BLOCK_SIZE);
	}
	set_memory_length(&mem[MESSAGE_SIZE], sha->len, 8, 0);
	perm((unsigned int *) mem, sha);
}

char	*sha256(char *init_mem, int fd)
{
	t_sha	sha;

	set_initial_values_sha256(&sha);
	sha_permutations(init_mem, fd, &sha);
	return get_result_sha256(&sha);
}

char	*sha224(char *init_mem, int fd)
{
	t_sha	sha;

	set_initial_values_sha224(&sha);
	sha_permutations(init_mem, fd, &sha);
	return get_result_sha224(&sha);
}
