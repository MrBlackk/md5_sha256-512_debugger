/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 15:56:43 by vchornyi          #+#    #+#             */
/*   Updated: 2018/12/01 15:56:44 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	error_message(char *reason, char *arg)
{
	ft_putstr("ft_ssl: ");
	ft_putstr(reason);
	ft_putstr(" '");
	ft_putstr(arg);
	ft_putendl("'");
}

int		error_return(char *reason, char *arg)
{
	error_message(reason, arg);
	return (-1);
}

void	error_exit(char *reason, char *arg)
{
	error_message(reason, arg);
	exit(1);
}

void	cmd_exit(void)
{
	exit(0);
}
