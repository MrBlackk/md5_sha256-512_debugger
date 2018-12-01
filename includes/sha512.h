/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 20:54:55 by vchornyi          #+#    #+#             */
/*   Updated: 2018/11/24 20:54:56 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA512_H
# define SHA512_H

# include "libft.h"
# include "common.h"

# define SHA512_LENGTH 128
# define SHA512_BLOCK 128
# define SHA512_MESSAGE 112
# define SHA384_LENGTH 96

void	prepare_message_schedule64(size_t *mem, size_t *schedule);
void	save_start_values64(size_t *start_values, t_buf64 *sh);
void	add_start_values512(size_t *start_values, t_buf64 *sh);
void	permutation512(size_t *mem, t_buf64 *s);

#endif