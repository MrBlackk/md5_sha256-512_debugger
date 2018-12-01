/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_round.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 16:43:18 by vchornyi          #+#    #+#             */
/*   Updated: 2018/12/01 16:43:19 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

unsigned int	first_round(unsigned int x, unsigned int y, unsigned int z)
{
	return (x & y) | ((~x) & z);
}

unsigned int	second_round(unsigned int x, unsigned int y, unsigned int z)
{
	return (x & z) | ((~z) & y);
}

unsigned int	third_round(unsigned int x, unsigned int y, unsigned int z)
{
	return (x ^ y ^ z);
}

unsigned int	fourth_round(unsigned int x, unsigned int y, unsigned int z)
{
	return (y ^ ((~z) | x));
}

unsigned int	left_rotate(unsigned int x, int n)
{
	return (x << n) | (x >> (32 - n));
}
