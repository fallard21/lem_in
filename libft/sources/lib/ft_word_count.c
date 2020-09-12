/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word_count.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbdoogls <jbdoogls@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 00:16:19 by jbdoogls          #+#    #+#             */
/*   Updated: 2020/06/01 00:16:37 by jbdoogls         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_word_count(char const *s, char c)
{
	int		ct;

	ct = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			ct++;
			while (*s && *s != c)
				s++;
		}
	}
	return (ct);
}
