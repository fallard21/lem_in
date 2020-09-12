/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbdoogls <jbdoogls@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 19:24:32 by edoll             #+#    #+#             */
/*   Updated: 2020/06/01 18:31:10 by jbdoogls         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new_elem;
	t_list *head;

	if (!lst || !f || !(new_elem = ft_lstnew(NULL, 0)))
		return (NULL);
	new_elem = f(lst);
	head = new_elem;
	while (lst->next)
	{
		lst = lst->next;
		new_elem->next = f(lst);
		new_elem = new_elem->next;
	}
	return (head);
}
