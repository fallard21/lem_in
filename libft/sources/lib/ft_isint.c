/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 20:28:54 by user              #+#    #+#             */
/*   Updated: 2020/10/25 15:54:19 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
	if (ft_strlen(str) > INT_MAX_LEN ||
		(ft_strlen(str) == INT_MAX_LEN && ft_atoi_long(str) > INT_MAX))
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
		if (ft_strlen(str) > INT_MIN_LEN ||
		(ft_strlen(str) == INT_MIN_LEN && ft_atoi_long(str) < INT_MIN))
			i = 0;
	}
	else
	{
		if (ft_strlen(str) > INT_MAX_LEN ||
		(ft_strlen(str) == INT_MAX_LEN && ft_atoi_long(str) > INT_MAX))
			i = 0;
	}
	return (i ? 1 : 0);
}
