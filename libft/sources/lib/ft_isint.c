/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 20:28:54 by user              #+#    #+#             */
/*   Updated: 2020/10/15 01:38:40 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

/*
**	Functions to check string for the content of
**		the valid int value
*/

/*
**	Check if	0 <= int_value <= MAX_INT
*/

int			ft_isposint_str(char *str)
{
	int		i;

	i = 0;
	if (str[0] == '-')
		return (0);
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (0);
	if (ft_strlen(str) > MAXINT_LEN ||
		(ft_strlen(str) == MAXINT_LEN && str[MAXINT_LEN - 1] + '0' > 7))
		return (0);
	return (1);
}

/*
**	Check if	MIN_INT <= int_value <= MAX_INT
*/

int			ft_isint_str(char *str)
{
	int		i;
	int		is_sign;

	is_sign = (str[0] == '-') ? 1 : 0;
	i = is_sign ? 1 : 0;
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (0);
	if (is_sign)
	{
		if (ft_strlen(str) > MININT_LEN ||
		(ft_strlen(str) == MININT_LEN && str[MININT_LEN - 1] > '8'))
			i = 0;
	}
	else
	{
		if (ft_strlen(str) > MAXINT_LEN ||
		(ft_strlen(str) == MAXINT_LEN && str[MAXINT_LEN - 1] > '7'))
			i = 0;
	}
	return (i ? 1 : 0);
}
