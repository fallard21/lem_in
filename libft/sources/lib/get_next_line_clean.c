/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_clean.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 22:53:01 by user              #+#    #+#             */
/*   Updated: 2020/08/25 23:03:17 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		clean_gnl_cache(t_gnl *lst)
{
	t_gnl	*copy;

	while (lst)
	{
		if (lst->content)
			ft_strdel(&(lst->content));
		copy = lst->next;
		free(lst);
		lst = copy;
	}
	return (-1);
}
