/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 20:54:55 by vchornyi          #+#    #+#             */
/*   Updated: 2018/11/24 20:54:56 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

unsigned int	get_next_char_block(char *src, char *dest, unsigned int block_size)
{
	unsigned int	len;
	char 			*ptr;

	len = 0;
	ptr = src;
	while (ptr && ptr[len] != '\0' && len < block_size)
	{
		dest[len] = ptr[len];
		len++;
	}
	return len;
}

unsigned int	get_next_stdin_block(char *dest, unsigned int block_size)
{
	char			buff[1];
	ssize_t			ret;
	unsigned int	len;

	len = 0;
	while (len < block_size && (ret = read(0, buff, 1)))
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

unsigned int	get_next_file_block(char *dest, int fd, unsigned int block_size)
{
	ssize_t	ret;

	ret = read(fd, dest, block_size);
	if (ret < 0)
	{
		ft_putendl("error"); //todo: error exit from common?
		return 0;
	}
	return (unsigned int) ret;
}

unsigned int	get_next_block(char *src, char *dest, int fd, unsigned int block_size)
{
	unsigned int	length;

	ft_bzero(dest, block_size);
	if (fd == -1)
		length = get_next_char_block(src, dest, block_size);
	else if (fd == 0)
		length = get_next_stdin_block(dest, block_size);
	else
		length = get_next_file_block(dest, fd, block_size);
	return length;
}

void	set_memory_length(char *init_mem, size_t length, char is_little_endian)
{
	int		i;
	char	byte;
	size_t	value;
	char	*mem;
	int		shift;

	i = 0;
	value = length * BITS_IN_BYTE;
	mem = init_mem;
	while (i < 8)
	{
		shift = BITS_IN_BYTE * i;
		if (!is_little_endian)
			shift = BITS_IN_BYTE * (7 - i);
		byte = (char)(value >> shift);
		ft_memset(mem, byte, 1);
		mem++;
		i++;
	}
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

void    print_blocks(void *memory, size_t len, char is_hex) {
	size_t i = 0;
	size_t j;
	size_t k;

	unsigned int *nums = (unsigned int*)memory;
	unsigned char *bytes = (unsigned char*)memory;
	j = 0;
	while (i < len) {
		if (is_hex) {
			k = 0;
			ft_printf("[%u] ", i);
			while (k < 4)
			{
				ft_printf("%.2X", bytes[j++]);
				k++;
			}
			ft_printf("\n");
		} else {
			ft_printf("[%u] %u\n", i, nums[i]);
		}
		i++;
	}
	ft_printf("\n");
}

void    debug(void *mem, size_t len, char is_hex) {
	print_memory(mem, len * 4);
	print_blocks(mem, len, is_hex);
}


unsigned int	get_hex(unsigned int num) {
	if (num > 9)
		return num + 'a' - 10;
	else
		return num + '0';
}

void	result(char *res, unsigned int num, unsigned int str_iter, char is_little_endian) {
	unsigned int	i;
	unsigned int	byte;

	i = 0;
	while(i < 32)
	{
		if (is_little_endian)
			byte = (num >> i) & 255;
		else
			byte = (num >> 24 - i) & 255;
		res[str_iter++] = (char) get_hex(byte / 16);
		res[str_iter++] = (char) get_hex(byte % 16);
		i += 8;
	}
}
