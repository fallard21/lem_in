/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbdoogls <jbdoogls@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 13:42:31 by jbdoogls          #+#    #+#             */
/*   Updated: 2020/05/27 12:47:44 by jbdoogls         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strsdup(char *src, char *src2)
{
	char	*dst;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(dst = (char*)malloc(sizeof(char) *
		(ft_strlen(src) + ft_strlen(src2) + 1))))
		return (NULL);
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	while (src2[j])
	{
		dst[i + j] = src2[j];
		j++;
	}
	dst[i + j] = '\0';
	ft_strdel(&src);
	ft_strdel(&src2);
	return (dst);
}
