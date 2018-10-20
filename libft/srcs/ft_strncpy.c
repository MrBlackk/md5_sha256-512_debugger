/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 11:54:57 by vchornyi          #+#    #+#             */
/*   Updated: 2017/10/27 11:54:58 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (i < len)
	{
		if (src[j] != '\0')
		{
			dst[i] = src[j];
			j++;
		}
		else
			dst[i] = '\0';
		i++;
	}
	return (dst);
}
