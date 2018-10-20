/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstr_to_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 14:55:37 by vchornyi          #+#    #+#             */
/*   Updated: 2018/01/12 14:55:38 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_wstr_to_str(wchar_t *wide, t_str *el)
{
	char	*res;
	char	*temp1;
	char	*temp2;
	size_t	len;

	if (!wide)
		return (NULL);
	len = 0;
	res = ft_strnew(0);
	while (*wide)
	{
		temp1 = res;
		temp2 = ft_wchar_to_str(*wide);
		if (temp1 == NULL || temp2 == NULL)
			return (NULL);
		len += ft_strlen(temp2);
		if (el->fmt->is_precision && el->fmt->precision < len)
			break ;
		res = ft_strjoin(temp1, temp2);
		ft_strdel(&temp1);
		ft_strdel(&temp2);
		wide++;
	}
	return (res);
}
