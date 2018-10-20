/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 16:19:10 by vchornyi          #+#    #+#             */
/*   Updated: 2017/11/02 16:19:12 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	char	*rev;
	size_t	len;
	size_t	i;

	if (str == NULL)
		return (NULL);
	len = ft_strlen(str);
	rev = ft_strnew(len);
	if (rev == NULL)
		return (NULL);
	i = 0;
	while (len > 0)
	{
		rev[i++] = str[len-- - 1];
	}
	rev[i] = '\0';
	return (rev);
}
