/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 17:48:37 by fallard           #+#    #+#             */
/*   Updated: 2020/10/12 16:27:08 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lem_in.h"

int		free_link(t_link **link)
{
	t_link	*next;

	while (*link)
	{
		next = (*link)->next;
		free(*link);
		*link = next;
	}
	return (1);
}

/*
void	free_room(t_room **room)
{
	t_room	*next;

	while (*room)
	{
		next = (*room)->next;
		free((*room)->name);
		free(*room);
		*room = next;
	}
}
*/

t_find	*free_prev_list(t_find **head)
{
	t_find	*next;

	while (*head)
	{
		next = (*head)->next;
		free(*head);
		*head = next;
	}
	return (NULL);
}

void	free_flow(t_flow **flow)
{
	if (*flow)
	{
		ft_memdel((void**)&(*flow)->ants);
		ft_memdel((void**)&(*flow)->path);
		ft_memdel((void**)&(*flow)->diff);
	}
	ft_memdel((void**)&(*flow));
}
