/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 17:48:37 by fallard           #+#    #+#             */
/*   Updated: 2020/10/09 18:08:05 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lem_parser.h"

int		free_link(t_link **link)
{
	t_link	*next;

	while (*link)
	{
		next = (*link)->next;
		free((*link)->room->name);
		free((*link)->room);
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
