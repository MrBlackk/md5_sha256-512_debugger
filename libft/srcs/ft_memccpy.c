/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 12:20:29 by vchornyi          #+#    #+#             */
/*   Updated: 2017/10/26 12:20:31 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
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
		if (src_b[i] == (unsigned char)c)
			return (&dst_b[++i]);
		i++;
	}
	return (NULL);
}
