/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 11:25:13 by vchornyi          #+#    #+#             */
/*   Updated: 2017/10/26 11:25:17 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*src_b;
	unsigned char	*dst_b;

	i = 0;
	src_b = (unsigned char *)src;
	dst_b = (unsigned char *)dst;
	while (i < n)
	{
		dst_b[i] = src_b[i];
		i++;
	}
	return (dst);
}
