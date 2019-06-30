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

void print_table(void *generic, unsigned int size, char *name, char *format, char *table_name, char is_int) {
	if (DEBUG) {
		char str[20];
		unsigned int columns = is_int ? 8  : 4;

		ft_strcpy(str, table_name);
		ft_strcat(str, "[%2d]=");
		ft_strcat(str, format);
		ft_printf("Table of %s:\n", name);
		for (unsigned int i = 0; i < size; i++) {
			ft_printf(str, i, is_int ? ((unsigned int *) generic)[i] : ((size_t *) generic)[i]);
			if ((i + 1) % columns == 0) {
				ft_printf("\n");
			}
		}
		ft_printf("\n");
	}
}

void    print_binary_memory(void *memory, size_t len) {
    size_t i = 0;
    unsigned char *bytes = (unsigned char *) memory;
    while (i < len) {
        ft_printf("%08b ", bytes[i]);
        i++;
        if (i % 8 == 0) {
            ft_printf("\n");
        }
    }
    ft_printf("\n");
}

void print_memory(void *mem, void *bf, unsigned int buf_size, unsigned int block_size, char is_int) {
    if (DEBUG) {
        ft_printf("#%u memory block binary /byte by byte/:\n", block_i);
        print_binary_memory(mem, block_size);
        ft_printf("#%u memory block decimal /unsigned ints/:\n", block_i);
		unsigned int *memu = (unsigned int *) mem;
		unsigned int blocks = is_int ? 16 : 32;
        for (unsigned int j = 0; j < blocks; j++) {
            ft_printf("[%2d] %zu\n", j, memu[j]);
        }
        block_i++;
        ft_printf("\nStart words values ");
        for (unsigned int i = 0; i < buf_size; ++i) {
            ft_printf("%c=%zu ", i + 'A', is_int ? ((unsigned int *) bf)[i] : ((size_t *) bf)[i]);
        }
        ft_printf("\nWords on each permutation step: \n");
    }
}

void print_words_iteration(void *bf, unsigned int buf_size, unsigned int i, char is_int) {
    if (DEBUG) {
		unsigned int idx;
		char *format = is_int ? "%c=%-11zu " : "%c=%-21zu ";

        ft_printf("[%2d] ", i);
        for (unsigned int j = 0; j < buf_size; ++j) {
			idx = (i + j + 1) % buf_size;
            ft_printf(format, j + 'A', is_int ? ((unsigned int *) bf)[idx] : ((size_t *) bf)[idx]);
        }
        ft_printf("\n");
    }
}

void print_words_processed(void *bf, unsigned int buf_size, char is_int) {
    if (DEBUG) {
        ft_printf("Processed ");
        for (unsigned int i = 0; i < buf_size; i++) {
            ft_printf("%c=%zu ", i + 'A', is_int ? ((unsigned int *) bf)[i] : ((size_t *) bf)[i]);
        }
        ft_printf("\n\n");
    }
}

void print_initial_words_values(void * bf, unsigned int max_buf, char is_int) {
	if (DEBUG) {
		ft_printf("Initial words values:\n");
		for (unsigned int i = 0; i < max_buf; i++) {
			ft_printf("%c: %zu\n", i + 'A', is_int ? ((unsigned int *) bf)[i] : ((size_t *) bf)[i]);
		}
		ft_printf("\n");
	}
}

void print_memory_end(size_t len) {
	if (DEBUG) {
		ft_printf("-- Set memory end .../ 10000000 /... at %zu byte --\n", len + 1);
	}
}

void print_set_len(size_t len, unsigned char is_little_endian, unsigned int message_size) {
	if (DEBUG) {
		ft_printf("-- Set memory length=%zu starting from %zu byte in %s\n", len, message_size + 1,
				  is_little_endian
				  ? "little endian(least-significant element in the lowest-enumerated "
						  "(\"smallest numbered\" or \"first\") position)"
				  : "big endian(least-significant element in the largest-enumerated "
						  "(\"largest numbered\" or \"last\") position)");
	}
}