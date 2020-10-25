/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_long.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 15:13:07 by user              #+#    #+#             */
/*   Updated: 2020/10/25 15:13:26 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long		ft_atoi_long(const char *pt)
{
	long		rs;
	int			sn;

	sn = 1;
	rs = 0;
	while (*pt && (*pt == ' ' || *pt == '\n' || *pt == '\t' ||
			*pt == '\v' || *pt == '\f' || *pt == '\r'))
		pt++;
	if (*pt == '-')
		sn = -1;
	if (*pt == '-' || *pt == '+')
		pt++;
	while (*pt && *pt >= '0' && *pt <= '9')
	{
		rs = rs * 10 + (*pt - '0');
		pt++;
	}
	if ((rs * sn < 0) && sn > 0)
		return (-1);
	else if ((rs * sn > 0) && sn < 0)
		return (0);
	else
		return (rs * sn);
}
