/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 17:18:26 by vchornyi          #+#    #+#             */
/*   Updated: 2017/10/26 17:18:28 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s_ptr;

	i = 0;
	s_ptr = (unsigned char *)s;
	while (i < n)
	{
		if (s_ptr[i] == (unsigned char)c)
			return (&s_ptr[i]);
		i++;
	}
	return (NULL);
}
