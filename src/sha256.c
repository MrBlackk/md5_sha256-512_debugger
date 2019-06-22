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

static unsigned int g_sha256_const[64] =
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

static void	set_initial_values_sha256(t_buf32 *sh)
{
	sh->bf[0] = 0x6a09e667;
	sh->bf[1] = 0xbb67ae85;
	sh->bf[2] = 0x3c6ef372;
	sh->bf[3] = 0xa54ff53a;
	sh->bf[4] = 0x510e527f;
	sh->bf[5] = 0x9b05688c;
	sh->bf[6] = 0x1f83d9ab;
	sh->bf[7] = 0x5be0cd19;
	sh->max_buf = SHA256_BUF;
	sh->is_little_endian = FALSE;
	sh->message_length = SHA256_LENGTH;
	sh->len = 0;
}

static void	set_initial_values_sha224(t_buf32 *sh)
{
	sh->bf[0] = 0xc1059ed8;
	sh->bf[1] = 0x367cd507;
	sh->bf[2] = 0x3070dd17;
	sh->bf[3] = 0xf70e5939;
	sh->bf[4] = 0xffc00b31;
	sh->bf[5] = 0x68581511;
	sh->bf[6] = 0x64f98fa7;
	sh->bf[7] = 0xbefa4fa4;
	sh->max_buf = SHA224_BUF;
	sh->is_little_endian = FALSE;
	sh->message_length = SHA224_LENGTH;
	sh->len = 0;
}

static void	permutations_sha256(unsigned int *mem, t_buf32 *s)
{
	unsigned char	i;
	unsigned int	start_values[8];
	unsigned int	schedule[64];
	unsigned int	t1;
	unsigned int	t2;

	i = 0;
	prepare_msg_schedule(mem, schedule);
	save_start_values(start_values, s);
    print_memory(mem, s->bf, s->max_buf, BLOCK_SIZE);
	while (i < 64)
	{
		t1 = s->bf[7] + sum(s->bf[4], 6, 11, 25) + ch(s->bf[4], s->bf[5],
				s->bf[6]) + g_sha256_const[i] + schedule[i];
		t2 = sum(s->bf[0], 2, 13, 22) + maj(s->bf[0], s->bf[1], s->bf[2]);
		s->bf[7] = s->bf[6];
		s->bf[6] = s->bf[5];
		s->bf[5] = s->bf[4];
		s->bf[4] = s->bf[3] + t1;
		s->bf[3] = s->bf[2];
		s->bf[2] = s->bf[1];
		s->bf[1] = s->bf[0];
		s->bf[0] = t1 + t2;
        print_words_iteration(s->bf, s->max_buf, i);
		i++;
	}
	add_start_values(start_values, s);
    print_words_processed(s->bf, s->max_buf);
}

char		*sha256(char *init_mem, int fd)
{
	t_buf32	sh;

	set_initial_values_sha256(&sh);
	permutations(init_mem, fd, &sh, &permutations_sha256);
	return (get_result(&sh));
}

char		*sha224(char *init_mem, int fd)
{
	t_buf32	sh;

	set_initial_values_sha224(&sh);
	permutations(init_mem, fd, &sh, &permutations_sha256);
	return (get_result(&sh));
}
