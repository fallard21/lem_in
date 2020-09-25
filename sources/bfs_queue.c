/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_queue.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 00:02:26 by fallard           #+#    #+#             */
/*   Updated: 2020/09/25 07:08:29 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lem_parser.h"

int		is_empty(t_link *queue)
{
	if (queue)
		return (0);
	return (1);
}

void	queue_push(t_link **queue, t_room *room)
{
	t_link	*link;
	t_link	*tmp;

	tmp = NULL;

	link = ft_calloc(1, sizeof(t_link));
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

int	bfs_queue(t_room *start)
{
	t_link	*queue;
	t_link	*tmp;
	t_room	*current;
	int		count;

	queue = NULL;
	count = 0;
	queue_push(&queue, start);
		ft_printf("BFS\n");
	while (!is_empty(queue))
	{
			ft_printf("%s\t", queue->room->name); // DELETE
			ft_printf("%d: q = (", count++); print_links(queue);	// DELETE
		current = queue_pop(&queue);
		tmp = current->links;
		while (tmp)
		{
			if (tmp->room->level == INT_MAX)
				return (1);
			if (tmp->room->level == -1)
			{
				tmp->room->level = current->level + 1;
				queue_push(&queue, tmp->room);
			}
			tmp = tmp->next;
		}
	}
		ft_printf("\n");
	return (0);
}
