/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_charcount.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 18:23:05 by user              #+#    #+#             */
/*   Updated: 2020/10/15 18:30:22 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_str_charcount(const char *str, char c)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			j++;
		i++;
	}
	return (j);
}
