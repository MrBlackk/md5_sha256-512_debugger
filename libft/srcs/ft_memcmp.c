/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 18:56:22 by vchornyi          #+#    #+#             */
/*   Updated: 2017/10/26 18:56:23 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_b;
	unsigned char	*s2_b;

	i = 0;
	s1_b = (unsigned char *)s1;
	s2_b = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (s1_b[i] == s2_b[i] && i < n - 1)
		i++;
	return (s1_b[i] - s2_b[i]);
}
