/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 17:16:58 by vchornyi          #+#    #+#             */
/*   Updated: 2017/11/02 17:17:00 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstat(t_list *lst, size_t el_at)
{
	size_t n;

	n = 0;
	while (lst)
	{
		if (n == el_at)
			return (lst);
		n++;
		lst = lst->next;
	}
	return (NULL);
}
