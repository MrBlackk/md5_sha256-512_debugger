/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 17:29:57 by vchornyi          #+#    #+#             */
/*   Updated: 2017/10/27 17:29:59 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char find_char;
	char *res;

	find_char = (char)c;
	res = NULL;
	while (*s)
	{
		if (*s == find_char)
			res = (char *)s;
		s++;
	}
	if (find_char == '\0' && find_char == *s)
		res = (char *)s;
	return (res);
}
