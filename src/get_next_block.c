/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_block.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 15:52:54 by vchornyi          #+#    #+#             */
/*   Updated: 2018/12/01 15:52:56 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static unsigned int	get_char_block(char *src, char *dst, unsigned int block)
{
	unsigned int	len;
	char			*ptr;

	len = 0;
	ptr = src;
	while (ptr && ptr[len] != '\0' && len < block)
	{
		dst[len] = ptr[len];
		len++;
	}
	return (len);
}

static unsigned int	get_stdin_block(char *dst, unsigned int block)
{
	char			buff[1];
	ssize_t			ret;
	unsigned int	len;

	len = 0;
	while (len < block && (ret = read(0, buff, 1)))
	{
		dst[len] = buff[0];
		len++;
	}
	if (ret < 0)
		error_exit("Read error", "stdin");
	return (len);
}

static unsigned int	get_file_block(char *dst, int fd, unsigned int block)
{
	ssize_t	ret;

	ret = read(fd, dst, block);
	if (ret < 0)
		error_exit("Read error", "file");
	return ((unsigned int)ret);
}

unsigned int		get_next_block(char *src, char *dst,
								int fd, unsigned int block_size)
{
	unsigned int	length;

	ft_bzero(dst, block_size);
	if (fd == -1)
		length = get_char_block(src, dst, block_size);
	else if (fd == 0)
		length = get_stdin_block(dst, block_size);
	else
		length = get_file_block(dst, fd, block_size);
	return (length);
}
