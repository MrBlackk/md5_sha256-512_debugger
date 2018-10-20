/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 17:05:53 by vchornyi          #+#    #+#             */
/*   Updated: 2017/10/27 17:05:55 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char find_char;

	find_char = (char)c;
	while (*s)
	{
		if (*s == find_char)
			return ((char *)s);
		s++;
	}
	if (find_char == '\0' && find_char == *s)
		return ((char *)s);
	return (NULL);
}
