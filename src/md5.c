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

unsigned int	get_hex(unsigned int num) {
	if (num > 9)
		return num + 'a' - 10;
	else
		return num + '0';
}

void	result(char *res, unsigned int num, unsigned int str_iter) {
	unsigned int	i;
	unsigned int	byte;

	i = 0;
	while(i < 32)
	{
		byte = (num & (255 << i)) >> i;
		res[str_iter++] = (char) get_hex(byte / 16);
		res[str_iter++] = (char) get_hex(byte % 16);
		i += 8;
	}
}

unsigned int	round(t_round round_func, unsigned int mem, t_md *md, int i)
{
	return md->b0 + left_rotate(round_func(md->b0, md->c0, md->d0) +
			+ md->a0 + g_table[i] + mem, g_left_rotation[i]);
}

unsigned int	round_result(unsigned int *mem, t_md *md, int i)
{
	if (i < 16)
		return round(first_round, mem[i], md, i);
	else if (i >= 16 && i < 32)
		return round(second_round, mem[(5 * i + 1) % 16], md, i);
	else if (i >= 32 && i < 48)
		return round(third_round, mem[(3 * i + 5) % 16], md, i);
	else
		return round(fourth_round, mem[(7 * i) % 16], md, i);
}

void	permutation(unsigned int *mem, t_md *md)
{
	int				i;
	unsigned int	temp;

	md->a0 = md->a;
	md->b0 = md->b;
	md->c0 = md->c;
	md->d0 = md->d;
	i = 0;
	while (i < 64)
	{
		temp = round_result(mem, md, i);
		md->a0 = md->d0;
		md->d0 = md->c0;
		md->c0 = md->b0;
		md->b0 = temp;
		i++;
	}
	md->a += md->a0;
	md->b += md->b0;
	md->c += md->c0;
	md->d += md->d0;
}

void	set_memory_length(char *full_mem, size_t length) {
	int		i;
	char	byte;
	size_t	value;
	char	*mem;

	i = 0;
	value = length * BYTE;
	mem = &full_mem[MESSAGE_SIZE];
	while (i < 8)
	{
		byte = (char)(value >> BYTE * i);
		ft_memset(mem, byte, 1);
		mem++;
		i++;
	}
}

unsigned int	get_next_char_block(char *src, char *dest)
{
	unsigned int	len;
	char 			*ptr;

	len = 0;
	ptr = src;
	while (ptr && ptr[len] != '\0' && len < BLOCK_SIZE)
	{
		dest[len] = ptr[len];
		len++;
	}
	return len;
}

unsigned int	get_next_stdin_block(char *dest)
{
	char			buff[1];
	ssize_t			ret;
	unsigned int	len;

	len = 0;
	while (len < BLOCK_SIZE && (ret = read(0, buff, 1)))
	{
		dest[len] = buff[0];
		len++;
	}
	if (ret < 0)
	{
		ft_putendl("error"); //todo: error exit from common?
		return 0;
	}
	return len;
}

unsigned int	get_next_file_block(char *dest, int fd)
{
	ssize_t	ret;

	ret = read(fd, dest, BLOCK_SIZE);
	if (ret < 0)
	{
		ft_putendl("error"); //todo: error exit from common?
		return 0;
	}
	return (unsigned int) ret;
}

unsigned int	get_next_block(char *src, unsigned int from, char *dest, int fd)
{
	unsigned int	length;

	ft_bzero(dest, BLOCK_SIZE);
	if (fd == -1)
		length = get_next_char_block(&src[from], dest);
	else if (fd == 0)
		length = get_next_stdin_block(dest);
	else
		length = get_next_file_block(dest, fd);
	return length;
}

void	init_md_vars(t_md *md)
{
	md->a = A;
	md->b = B;
	md->c = C;
	md->d = D;
}

char 	*get_result(t_md *md)
{
	char	res[MD5_LENGTH + 1];

	ft_bzero(&res, MD5_LENGTH + 1);
	result(res, md->a, 0);
	result(res, md->b, 8);
	result(res, md->c, 16);
	result(res, md->d, 24);
	return ft_strdup(res);
}

char	*md5(char *init_mem, int fd)
{
    char	mem[BLOCK_SIZE];
    t_md	md;
	size_t	len;

	init_md_vars(&md);
	md.len = get_next_block(init_mem, 0, mem, fd);
	len = md.len;
	while (len == BLOCK_SIZE)
	{
		permutation((unsigned int *) mem, &md);
		len = get_next_block(init_mem, md.len, mem, fd);
		md.len += len;
	}
	ft_memset(&mem[len], FIRST_BITE, 1);
	if (len >= MESSAGE_SIZE)
	{
		permutation((unsigned int *) mem, &md);
		md.len += get_next_block(init_mem, md.len, mem, fd);
	}
	set_memory_length(mem, md.len);
	permutation((unsigned int *) mem, &md);
	return get_result(&md);
}
