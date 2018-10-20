/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_format_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 12:02:53 by vchornyi          #+#    #+#             */
/*   Updated: 2018/01/18 12:02:54 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	str_to_non_printable(t_str *el, char *arg, char **res)
{
	char	*temp1;
	char	*temp2;
	size_t	i;

	i = 0;
	while (i < el->fmt->width)
	{
		if (ft_isprint(arg[i]))
			temp2 = ft_char_to_str((unsigned char)arg[i]);
		else
		{
			if (!(temp1 = ft_ltoa((int)arg[i])))
				exit(1);
			temp2 = ft_strjoin("\\", temp1);
			ft_strdel(&temp1);
		}
		if (!temp2)
			exit(1);
		temp1 = *res;
		if (!(*res = ft_strjoin(*res, temp2)))
			exit(1);
		ft_strdel(&temp1);
		ft_strdel(&temp2);
		i++;
	}
}

void		pf_format_non_printable(t_str *el)
{
	char	*arg;
	char	*res;

	if (!(arg = ft_strnew(el->fmt->width)))
		exit(1);
	if (el->fmt->arg != NULL)
		ft_memcpy(arg, (char *)el->fmt->arg, el->fmt->width);
	if (!(res = ft_strnew(0)))
		exit(1);
	str_to_non_printable(el, arg, &res);
	el->len = 0;
	pf_replace_format_str(el, res, arg);
}

static char	*rotate_str(char *str, size_t rot)
{
	int		num;
	char	*res;
	size_t	i;

	res = ft_strdup(str);
	if (!res)
		exit(1);
	i = 0;
	while (res[i])
	{
		if (ft_isalpha(res[i]))
		{
			if (res[i] >= 'a' && res[i] <= 'z')
				num = 'a';
			else
				num = 'A';
			res[i] = (char)((res[i] - num + rot) % 26 + num);
		}
		i++;
	}
	return (res);
}

void		pf_format_caesar(t_str *el)
{
	char	*arg;
	char	*res;

	if (el->fmt->arg == NULL)
		arg = ft_strdup("(null)");
	else
		arg = ft_strdup((char *)el->fmt->arg);
	if (!arg)
		exit(1);
	res = rotate_str(arg, el->fmt->width);
	el->len = 0;
	pf_replace_format_str(el, res, arg);
}
