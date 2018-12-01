/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 20:54:55 by vchornyi          #+#    #+#             */
/*   Updated: 2018/11/24 20:54:56 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha512.h"

void	set_initial_values_sha512(t_buf64 *sh)
{
	sh->bf[0] = 0x6a09e667f3bcc908;
	sh->bf[1] = 0xbb67ae8584caa73b;
	sh->bf[2] = 0x3c6ef372fe94f82b;
	sh->bf[3] = 0xa54ff53a5f1d36f1;
	sh->bf[4] = 0x510e527fade682d1;
	sh->bf[5] = 0x9b05688c2b3e6c1f;
	sh->bf[6] = 0x1f83d9abfb41bd6b;
	sh->bf[7] = 0x5be0cd19137e2179;
	sh->message_length = SHA512_LENGTH;
	sh->len = 0;
}

void	set_initial_values_sha384(t_buf64 *sh)
{
	sh->bf[0] = 0xcbbb9d5dc1059ed8;
	sh->bf[1] = 0x629a292a367cd507;
	sh->bf[2] = 0x9159015a3070dd17;
	sh->bf[3] = 0x152fecd8f70e5939;
	sh->bf[4] = 0x67332667ffc00b31;
	sh->bf[5] = 0x8eb44a8768581511;
	sh->bf[6] = 0xdb0c2e0d64f98fa7;
	sh->bf[7] = 0x47b5481dbefa4fa4;
	sh->message_length = SHA384_LENGTH;
	sh->len = 0;
}

void	permutations_sha512(char *init_mem, int fd, t_buf64 *sh)
{
	char	mem[SHA512_BLOCK];
	size_t	len;

	sh->len = get_next_block(&init_mem[0], mem, fd, SHA512_BLOCK);
	len = sh->len;
	while (len == SHA512_BLOCK)
	{
		permutation512((size_t *)mem, sh);
		len = get_next_block(&init_mem[sh->len], mem, fd, SHA512_BLOCK);
		sh->len += len;
	}
	ft_memset(&mem[len], FIRST_BITE, 1);
	if (len >= SHA512_MESSAGE)
	{
		permutation512((size_t *)mem, sh);
		sh->len += get_next_block(&init_mem[sh->len], mem, fd, SHA512_BLOCK);
	}
	set_memory_length(&mem[SHA512_MESSAGE + 8], sh->len, 8, 0);
	permutation512((size_t *)mem, sh);
}

char	*sha512(char *mem, int fd)
{
	t_buf64	sh;

	set_initial_values_sha512(&sh);
	permutations_sha512(mem, fd, &sh);
	return (get_result64(&sh));
}

char	*sha384(char *mem, int fd)
{
	t_buf64	sh;

	set_initial_values_sha384(&sh);
	permutations_sha512(mem, fd, &sh);
	return (get_result64(&sh));
}
