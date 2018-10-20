/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 15:06:41 by vchornyi          #+#    #+#             */
/*   Updated: 2018/01/15 15:06:43 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	pf_save_num(t_str *el)
{
	size_t	*num;
	char	*temp;

	num = (size_t *)el->fmt->arg;
	*num = (unsigned int)g_len;
	if (el->fmt->length == 'H')
		*num = (unsigned char)g_len;
	else if (el->fmt->length == 'h')
		*num = (unsigned short int)g_len;
	else if (el->fmt->length == 'l')
		*num = (unsigned long int)g_len;
	else if (el->fmt->length == 'L')
		*num = (unsigned long long int)g_len;
	else if (el->fmt->length == 'j')
		*num = (uintmax_t)g_len;
	else if (el->fmt->length == 'z')
		*num = (size_t)g_len;
	if (!(temp = ft_strnew(0)))
		exit(1);
	el->len = 0;
	pf_replace_format_str(el, temp, NULL);
}

static void	check_and_format(t_str *head)
{
	if (head->fmt)
	{
		if (head->fmt->type == 'c' || head->fmt->type == 'C')
			pf_format_char(head);
		else if (head->fmt->type == 'd' || head->fmt->type == 'i')
			pf_format_digit(head);
		else if (head->fmt->type == 'D')
		{
			head->fmt->length = 'L';
			pf_format_digit(head);
		}
		else if (head->fmt->type == 's' || head->fmt->type == 'S')
			pf_format_string(head);
		else if (head->fmt->type == 'n')
			pf_save_num(head);
		else if (head->fmt->type == 'r')
			pf_format_non_printable(head);
		else if (head->fmt->type == 'b')
			pf_format_octal_binary(head, 2);
		else if (head->fmt->type == 't')
			pf_format_caesar(head);
	}
}

static void	check_and_format_unsigned(t_str *head)
{
	if (head->fmt)
	{
		if (head->fmt->type == 'o')
			pf_format_octal_binary(head, 8);
		else if (head->fmt->type == 'O')
		{
			head->fmt->length = 'L';
			pf_format_octal_binary(head, 8);
		}
		else if (head->fmt->type == 'x' || head->fmt->type == 'X')
			pf_format_hex(head);
		else if (head->fmt->type == 'u')
			pf_format_unsigned(head);
		else if (head->fmt->type == 'U')
		{
			head->fmt->length = 'L';
			pf_format_unsigned(head);
		}
		else if (head->fmt->type == 'p')
		{
			head->fmt->length = 'z';
			head->fmt->is_sharp = 1;
			pf_format_hex(head);
		}
	}
}

void		pf_format_elements(t_str **head)
{
	t_str	*iter;
	t_str	*next_iter;

	iter = *head;
	while (iter)
	{
		check_and_format(iter);
		check_and_format_unsigned(iter);
		if (iter->len != 0)
			g_len += iter->len;
		else
			g_len += ft_strlen(iter->str);
		if (iter->len != 0)
			ft_putstr_len(iter->str, iter->len);
		else
			ft_putstr(iter->str);
		ft_strdel(&iter->str);
		next_iter = iter->next;
		iter->next = NULL;
		ft_memdel((void **)&iter);
		iter = next_iter;
	}
	*head = NULL;
}
