/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 14:12:41 by vchornyi          #+#    #+#             */
/*   Updated: 2017/11/01 14:12:42 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_putnbr_rec(long long n)
{
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
	}
	if (n == 0)
		return ;
	ft_putnbr_rec(n / 10);
	ft_putchar(n % 10 + '0');
}

void			ft_putnbr(int n)
{
	if (n == 0)
		ft_putchar('0');
	else
		ft_putnbr_rec(n);
}
