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

static unsigned int block_i = 0;

unsigned int	right_rotate(unsigned int x, int n)
{
	return (x >> n) | (x << (32 - n));
}

size_t			right_rotate64(size_t x, int n)
{
	return (x >> n) | (x << (64 - n));
}

size_t			reverse_bytes(size_t num, int size)
{
	size_t	reverse_num;
	int		i;

	i = 0;
	reverse_num = 0;
	while (i < size)
	{
		reverse_num |= ((num >> 8 * i) & MAX_BYTE) << 8 * (size - i - 1);
		i++;
	}
	return (reverse_num);
}

void print_table(unsigned int *table, unsigned int size, char *name, char *format, char *arrName) {
	char str[20];

	ft_strcpy(str, arrName);
	ft_strcat(str, "[%2d]=");
	ft_strcat(str, format);
	ft_printf("Table of %s:\n", name);
	for (int i = 0; i < size; i++) {
		ft_printf(str, i, table[i]);
		if ((i + 1) % 8 == 0) {
			ft_printf("\n");
		}
	}
	ft_printf("\n");
}

void    print_binary_memory(void *memory, size_t len) {
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

void print_memory(unsigned int *mem, unsigned int *bf, unsigned int buf_size, unsigned int block_size) {
    if (DEBUG) {
        ft_printf("#%u memory block binary /byte by byte/:\n", block_i);
        print_binary_memory(mem, block_size);
        ft_printf("#%u memory block decimal /unsigned ints/:\n", block_i);
        for (int j = 0; j < 16; j++) {
            ft_printf("[%2d] %zu\n", j, mem[j]);
        }
        block_i++;
        ft_printf("\nStart words values ");
        for (int i = 0; i < buf_size; ++i) {
            ft_printf("%c=%-11zu ", i + 'A', bf[i]);
        }
        ft_printf("\nWords on each permutation step: \n");
    }
}

void print_words_iteration(unsigned int *bf, unsigned int buf_size, unsigned int i) {
    if (DEBUG) {
        ft_printf("[%2d] ", i);
        for (int j = 0; j < buf_size; ++j) {
            ft_printf("%c=%-11zu ", j + 'A', bf[(i + j + 1) % buf_size]);
        }
        ft_printf("\n");
    }
}

void print_words_processed(unsigned int *bf, unsigned int buf_size) {
    if (DEBUG) {
        ft_printf("Processed ");
        for (int j = 0; j < buf_size; ++j) {
            ft_printf("%c=%-11zu ", j + 'A', bf[j]);
        }
        ft_printf("\n\n");
    }
}