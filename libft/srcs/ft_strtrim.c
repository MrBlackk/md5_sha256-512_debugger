/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 17:03:14 by vchornyi          #+#    #+#             */
/*   Updated: 2017/10/30 17:03:16 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	start;
	size_t	end;
	size_t	len;
	char	*res;

	if (s == NULL)
		return (NULL);
	start = 0;
	end = ft_strlen(s);
	while (s[start] == 32 || s[start] == '\n' || s[start] == '\t')
		start++;
	while (s[end - 1] == 32 || s[end - 1] == '\n' || s[end - 1] == '\t')
		end--;
	len = end - start;
	if (end < start)
		len = 0;
	res = ft_strnew(len);
	if (res == NULL)
		return (NULL);
	ft_strncpy(res, &s[start], len);
	return (res);
}
