/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 11:03:32 by vchornyi          #+#    #+#             */
/*   Updated: 2017/11/02 11:03:34 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *iter;
	t_list *iter_next;

	if (alst == NULL || del == NULL)
		return ;
	iter = *alst;
	while (iter)
	{
		del(iter->content, iter->content_size);
		iter_next = iter->next;
		iter->next = NULL;
		free(iter);
		iter = iter_next;
	}
	*alst = NULL;
}
