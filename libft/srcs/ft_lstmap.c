/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 11:39:03 by vchornyi          #+#    #+#             */
/*   Updated: 2017/11/02 11:39:04 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new_list;
	t_list *el;
	t_list *next_el;

	if (lst == NULL || f == NULL)
		return (NULL);
	new_list = f(lst);
	if (new_list == NULL)
		return (NULL);
	lst = lst->next;
	el = new_list;
	while (lst)
	{
		next_el = f(lst);
		if (next_el == NULL)
		{
			ft_lstdel(&new_list, &ft_lstdeldata);
			return (NULL);
		}
		el->next = next_el;
		el = el->next;
		lst = lst->next;
	}
	return (new_list);
}
