/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   result.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 17:19:01 by vchornyi          #+#    #+#             */
/*   Updated: 2018/12/01 17:19:02 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static size_t	get_hex(size_t num)
{
	if (num > 9)
		return (num + 'a' - 10);
	else
		return (num + '0');
}

static void		result(char *res, size_t num, char is_little_endian,
												unsigned int size)
{
	unsigned int	i;
	unsigned int	str_iter;
	size_t			byte;

	i = 0;
	str_iter = 0;
	while (i < size)
	{
		if (is_little_endian)
			byte = (num >> i) & MAX_BYTE;
		else
			byte = (num >> (size - 8 - i)) & MAX_BYTE;
		res[str_iter++] = (char)get_hex(byte / 16);
		res[str_iter++] = (char)get_hex(byte % 16);
		i += 8;
	}
	if (DEBUG)
		ft_printf(": %s\n", res);
}

char			*get_result(t_buf32 *buf)
{
	char			*res;
	unsigned char	i;

	res = ft_strnew(buf->message_length + 1);
	if (res == NULL)
		exit(1);
	if (DEBUG)
		ft_printf("\nResults:\n");
	i = 0;
	while (i * 8 < buf->message_length)
	{
		if (DEBUG)
			ft_printf("%c", i + 'A');
		result(&res[i * 8], buf->bf[i], buf->is_little_endian, 32);
		i++;
	}
	return (res);
}

char			*get_result64(t_buf64 *buf)
{
	char			*res;
	unsigned char	i;

	res = ft_strnew(buf->message_length + 1);
	if (res == NULL)
		exit(1);
	i = 0;
	while (i * 16 < buf->message_length)
	{
		result(&res[i * 16], buf->bf[i], 0, 64);
		i++;
	}
	return (res);
}
