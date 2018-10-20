/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_format_digit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 14:25:21 by vchornyi          #+#    #+#             */
/*   Updated: 2018/01/15 14:25:22 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_num_str(t_str *el)
{
	if (el->fmt->length == 'H')
		return (ft_ltoa(*(signed char *)el->fmt->arg));
	else if (el->fmt->length == 'h')
		return (ft_ltoa(*(short int *)el->fmt->arg));
	else if (el->fmt->length == 'l')
		return (ft_ltoa(*(long int *)el->fmt->arg));
	else if (el->fmt->length == 'L')
		return (ft_ltoa(*(long long int *)el->fmt->arg));
	else if (el->fmt->length == 'j')
		return (ft_ltoa(*(intmax_t *)el->fmt->arg));
	else if (el->fmt->length == 'z')
		return (ft_ltoa(*(ssize_t *)el->fmt->arg));
	return (ft_ltoa(*(int *)el->fmt->arg));
}

static char	*add_zeros(char *num_str, size_t num_zeros, char sign)
{
	size_t	len;
	char	*res;

	if (sign != '\0')
	{
		len = ft_strlen(num_str);
		res = ft_strnew(len + num_zeros + 1);
		if (!res)
			exit(1);
		res[0] = sign;
		ft_memset(&res[1], '0', num_zeros);
		ft_strncpy(&res[num_zeros + 1], num_str, len);
	}
	else
	{
		len = ft_strlen(num_str);
		res = ft_strnew(len + num_zeros);
		if (!res)
			exit(1);
		ft_memset(res, '0', num_zeros);
		ft_strncpy(&res[num_zeros], num_str, len);
	}
	ft_strdel(&num_str);
	return (res);
}

static void	remove_sign(char **num_str)
{
	char *temp;

	temp = *num_str;
	*num_str = ft_strdup(&temp[1]);
	if (!(*num_str))
		exit(1);
	ft_strdel(&temp);
}

static char	get_sign(t_str *el, char **num_str)
{
	char	sign;

	sign = '\0';
	if ((*num_str)[0] == '-')
	{
		sign = '-';
		remove_sign(num_str);
	}
	else if (el->fmt->is_plus)
		sign = '+';
	else if (el->fmt->is_space)
		sign = ' ';
	return (sign);
}

void		pf_format_digit(t_str *el)
{
	char	*num_str;
	size_t	arg_len;
	char	*res;
	int		is_sgn;
	char	sign;

	is_sgn = 0;
	if ((num_str = get_num_str(el)) == NULL)
		exit(1);
	if ((sign = get_sign(el, &num_str)) != '\0')
		is_sgn = 1;
	arg_len = ft_strlen(num_str);
	if (arg_len < el->fmt->precision)
		num_str = add_zeros(num_str, el->fmt->precision - arg_len, sign);
	else if (el->fmt->is_zero && !el->fmt->is_minus
		&& el->fmt->width > arg_len + is_sgn && !el->fmt->is_precision)
		num_str = add_zeros(num_str, el->fmt->width - arg_len - is_sgn, sign);
	else
		num_str = add_zeros(num_str, 0, sign);
	arg_len = ft_strlen(num_str);
	if (el->fmt->precision == 0 && num_str[0] == '0')
		arg_len = 0;
	el->len = (arg_len < el->fmt->width) ? el->fmt->width : arg_len;
	res = pf_apply_width(el, num_str, ' ', arg_len);
	pf_replace_format_str(el, res, num_str);
}
