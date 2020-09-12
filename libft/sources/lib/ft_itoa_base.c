/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbdoogls <jbdoogls@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 18:06:46 by jbdoogls          #+#    #+#             */
/*   Updated: 2020/05/27 12:43:26 by jbdoogls         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(unsigned long int nbr, unsigned int base)
{
	char	*res;
	char	*base_nums;
	int		size;

	base_nums = ft_strdup("0123456789abcdef");
	res = NULL;
	size = ft_itoa_base_count(nbr, base);
	if (!(res = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	res[size--] = '\0';
	while (size >= 0)
	{
		res[size--] = base_nums[nbr % base];
		nbr /= base;
	}
	free(base_nums);
	return (res);
}

int		ft_itoa_base_count(unsigned long int nbr, unsigned int base)
{
	size_t	ct;

	if (nbr == 0)
		return (1);
	ct = 0;
	while (nbr)
	{
		nbr /= base;
		ct++;
	}
	return (ct);
}
