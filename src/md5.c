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

unsigned int g_a = A;
unsigned int g_b = B;
unsigned int g_c = C;
unsigned int g_d = D;

unsigned int g_table[64] =
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

unsigned int g_left_rotation[64] =
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

void    print_blocks(void *memory, size_t len) {
    size_t i = 0;
    unsigned int *nums = (unsigned int*)memory;
    while (i < len) {
        ft_printf("[%u] %u\n", i, nums[i]);
        i++;
    }
    ft_printf("\n");
}

void    debug(void *mem, size_t len) {
    print_memory(mem, len * 4);
    print_blocks(mem, len);
}

size_t calculate_new_length(size_t init_len) {
    size_t last_block;
    size_t len;
    size_t num_blocks;

    len = init_len + 1;
    last_block = len % BLOCK_SIZE;
    num_blocks = len / BLOCK_SIZE + 1;
    if (last_block > MESSAGE_SIZE)
        num_blocks++;
    return num_blocks * BLOCK_SIZE;
}

unsigned int first_round(unsigned int x, unsigned int y, unsigned int z)
{
    return (x & y) | ((~x) & z);
}

unsigned int second_round(unsigned int x, unsigned int y, unsigned int z)
{
    return (x & z) | ((~z) & y);
}

unsigned int third_round(unsigned int x, unsigned int y, unsigned int z)
{
    return x ^ y ^ z;
}

unsigned int fourth_round(unsigned int x, unsigned int y, unsigned int z)
{
    return y ^ ((~z) | x);
}

void	debug_abcd() {
	ft_printf("----------\n");
	ft_printf("%u\n", g_a);
	ft_printf("%u\n", g_b);
	ft_printf("%u\n", g_c);
	ft_printf("%u\n", g_d);
	ft_printf("---------------\n");
}

unsigned int left_rotate(unsigned int x, int n)
{
	return (x << n) | (x >> (32 - n));
}

unsigned int	get_hex(int num) {
	if (num > 9) {
		return num + 'a' - 10;
	} else {
		return num + '0';
	}
}

void	result(char *res, unsigned int a, unsigned int j) {
	unsigned int i = 0;
	unsigned int r;
	while(i <= 32) {
		r = (a & (255 << i)) >> i;
		res[j++] = get_hex(r / 16);
		res[j++] = get_hex(r % 16);
		i += 8;
	}
}

void	first(unsigned int *mem, char *res) {
	int i = 0;
	int j = 0;
	unsigned  int f;
	while (i < 64) {
		if (i < 16) {
			f = g_b + left_rotate(first_round(g_b, g_c, g_d) + g_a + g_table[i] + mem[j],g_left_rotation[i]);
		} else if (i >= 16 && i < 32) {
			f = g_b + left_rotate(second_round(g_b, g_c, g_d) + g_a + g_table[i] + mem[(5 * i + 1) % 16],g_left_rotation[i]);
		} else if (i >= 32 && i < 48) {
			f = g_b + left_rotate(third_round(g_b, g_c, g_d) + g_a + g_table[i] + mem[(3 * i + 5) % 16],g_left_rotation[i]);
		} else {
			f = g_b + left_rotate(fourth_round(g_b, g_c, g_d) + g_a + g_table[i] + mem[(7 * i) % 16],g_left_rotation[i]);
		}
		g_a = g_d;
		g_d = g_c;
		g_c = g_b;
		g_b = f;
		ft_printf("%d/%d:", i, (5 * i + 1) % 16);
		debug_abcd();
		i++;
		j = (j + 1) % 16;
	}
	g_a += A;
	g_b += B;
	g_c += C;
	g_d += D;
	debug_abcd();
	result(res, g_a, 0);
	result(res, g_b, 8);
	result(res, g_c, 16);
	result(res, g_d, 24);
	res[32] = '\0'; //todo: check bzero
}

char	*md5(void *init_mem, size_t init_len)
{
    char mem[BLOCK_SIZE];
    char res[MD5_LENGTH + 1];
    size_t len;

    len = calculate_new_length(init_len);
    ft_bzero(mem, BLOCK_SIZE);
    ft_memcpy(mem, init_mem, init_len);
    ft_memset(&mem[init_len], FIRST_BITE, 1);
    ft_memset(&mem[MESSAGE_SIZE], (int) (BYTE * init_len), 1); //todo: could be 8 bytes for message size
    debug(mem, 16);

	ft_bzero(res, MD5_LENGTH + 1);
	first((unsigned int *)mem, res);

	return ft_strdup(res);
}
