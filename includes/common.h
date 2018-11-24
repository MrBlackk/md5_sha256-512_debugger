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

# include "libft.h"

# define BITS_IN_BYTE 8
# define BLOCK_SIZE 64
# define MESSAGE_SIZE 56
# define FIRST_BITE 128

unsigned int	get_next_block(char *src, char *dest, int fd, unsigned int block_size);
void	set_memory_length(char *init_mem, size_t length, char is_little_endian);
void    debug(void *mem, size_t len);

#endif