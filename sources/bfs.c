/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 00:02:26 by fallard           #+#    #+#             */
/*   Updated: 2020/10/15 01:12:28 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lem_in.h"

int		is_empty(t_link *queue)
{
	if (queue)
		return (0);
	return (1);
}

void	queue_push(t_frame *frame, t_link **queue, t_room *room)
{
	t_link	*link;
	t_link	*tmp;

	tmp = NULL;
	if (!(link = ft_calloc(1, sizeof(t_link))))
	{
		free_link(&(*queue));
		lem_error(ALLOC_ERR, frame);
	}
	link->room = room;
	if (!(*queue))
		*queue = link;
	else
	{
		tmp = *queue;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = link;
	}
}

t_room	*queue_pop(t_link **queue)
{
	t_link	*tmp;
	t_room	*room;

	tmp = *queue;
	*queue = (*queue)->next;
	room = tmp->room;
	free(tmp);
	return (room);
}

int		bfs(t_frame *frame, t_room *start)
{
	t_link	*queue;
	t_link	*tmp;
	t_room	*current;

	queue = NULL;
	queue_push(frame, &queue, start);
	while (!is_empty(queue))
	{
		current = queue_pop(&queue);
		tmp = current->links;
		while (tmp)
		{
			if (tmp->room->level == INT_MAX)
				return (free_link(&queue));
			if (tmp->room->level == -1)
			{
				tmp->room->level = current->level + 1;
				queue_push(frame, &queue, tmp->room);
			}
			tmp = tmp->next;
		}
	}
	return (0);
}
