/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 12:41:09 by vchornyi          #+#    #+#             */
/*   Updated: 2017/10/26 12:41:11 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*src_b;
	unsigned char	*dst_b;

	src_b = (unsigned char *)src;
	dst_b = (unsigned char *)dst;
	if (len < (size_t)(dst - src))
		ft_memcpy(dst, src, len);
	else
	{
		while (len > 0)
		{
			dst_b[len - 1] = src_b[len - 1];
			len--;
		}
		dst_b[len] = src_b[len];
	}
	return (dst);
}
