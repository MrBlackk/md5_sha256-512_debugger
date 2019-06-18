/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 20:54:55 by vchornyi          #+#    #+#             */
/*   Updated: 2018/11/24 20:54:56 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

#ifndef DEBUG
# define DEBUG 1
#endif

# include "libft.h"

# define TRUE 1
# define FALSE 0
# define BITS_IN_BYTE 8
# define BLOCK_SIZE 64
# define MESSAGE_SIZE 56
# define FIRST_BITE 128
# define MAX_BYTE 255

typedef struct s_buf32	t_buf32;
typedef struct s_buf64	t_buf64;
typedef void	t_perm(unsigned int *mem, t_buf32 *buf);

struct			s_buf32
{
	unsigned int	bf[8];
	unsigned char	max_buf;
	unsigned char	message_length;
	unsigned char	is_little_endian;
	size_t			len;
};

struct			s_buf64
{
	size_t			bf[8];
	unsigned char	message_length;
	size_t			len;
};

unsigned int	get_next_block(char *src, char *dst, int fd,
										unsigned int block_size);
void			set_memory_length(char *init_mem, size_t length, int size,
										char is_little_endian);
size_t			reverse_bytes(size_t num, int size);
void			permutations(char *init_mem, int fd, t_buf32 *buf,
										t_perm *permutation);
char			*get_result(t_buf32 *buf);
void			save_start_values(unsigned int *start_values, t_buf32 *buf);
void			add_start_values(unsigned int *start_values, t_buf32 *buf);
void			error_exit(char *reason, char *arg);
int				error_return(char *reason, char *arg);
void			error_message(char *reason, char *arg);
unsigned int	right_rotate(unsigned int x, int n);
size_t			right_rotate64(size_t x, int n);
char			*get_result64(t_buf64 *buf);

#endif
