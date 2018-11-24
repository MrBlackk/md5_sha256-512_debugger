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

static void	set_initial_values(t_sha *sha)
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

void	perm(unsigned int *mem, t_sha *sha)
{
	unsigned int	i;
	unsigned int	start_values[8];

	i = 0;
	save_start_values(start_values, sha);
	while (i < 64)
	{

		i++;
	}
	add_start_values(start_values, sha);
}

char	*sha256(char *init_mem, int fd)
{
	char	mem[BLOCK_SIZE];
	t_sha	sha;
	size_t	len;

	set_initial_values(&sha);
	sha.len = get_next_block(&init_mem[0], mem, fd, BLOCK_SIZE);
	len = sha.len;
	while (len == BLOCK_SIZE)
	{
//		permutation((unsigned int *) mem, &md);
		len = get_next_block(&init_mem[sha.len], mem, fd, BLOCK_SIZE);
		sha.len += len;
	}
	ft_memset(&mem[len], FIRST_BITE, 1);
	if (len >= MESSAGE_SIZE)
	{
//		permutation((unsigned int *) mem, &md);
		sha.len += get_next_block(&init_mem[sha.len], mem, fd, BLOCK_SIZE);
	}
	set_memory_length(&mem[MESSAGE_SIZE], sha.len, 0);
	debug(mem, 16);
//	permutation((unsigned int *) mem, &md);
	return NULL;
}
