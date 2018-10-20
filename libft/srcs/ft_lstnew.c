/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 16:39:59 by vchornyi          #+#    #+#             */
/*   Updated: 2017/11/01 16:40:00 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *new_el;

	new_el = (t_list *)malloc(sizeof(t_list));
	if (new_el == NULL)
		return (NULL);
	if (content == NULL)
	{
		new_el->content = NULL;
		new_el->content_size = 0;
	}
	else
	{
		new_el->content = malloc(sizeof(content_size));
		if (new_el->content == NULL)
		{
			ft_lstdelone(&new_el, &ft_lstdeldata);
			return (NULL);
		}
		ft_memcpy(new_el->content, content, content_size);
		new_el->content_size = content_size;
	}
	new_el->next = NULL;
	return (new_el);
}
