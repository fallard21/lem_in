/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bellman_ford.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 20:02:05 by fallard           #+#    #+#             */
/*   Updated: 2020/10/09 18:22:51 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lem_parser.h"

void	reinit_sizes(t_room *start)
{
	t_room *tmp;

	tmp = start;
	while (tmp)
	{
		tmp->vertex_size = INT_MAX;
		tmp->prev = NULL;
		tmp = tmp->next;
	}
	start->vertex_size = 0;
}

int		insert_recovery(t_find **head, t_room *room)
{
	t_find	*tmp;

	if (*head == NULL)
	{
		if (!(*head = ft_calloc(1, sizeof(t_find))))
			return (1);
		(*head)->room = room;
	}
	else
	{
		if (!(tmp = ft_calloc(1, sizeof(t_find))))
			return (1);
		tmp->room = room;
		tmp->next = *head;
		*head = tmp;
	}
	return (0);
}

t_find	*restore_path(t_room *end)
{
	t_room	*tmp;
	t_find	*way;

	way = NULL;
	tmp = end;
	while (tmp)
	{
		if (insert_recovery(&way, tmp) == 1)
			return (free_prev_list(&way));
		tmp = tmp->prev;
	}
	//print_recovery(way);
	return (way);
}

void	bellman_ford_2(t_link **tmp, t_room **current, int *flag)
{
	int n;

	n = 0;
	while (*tmp)
	{
		if ((*current)->vertex_size == INT_MAX)
			break ;
		n = (*current)->vertex_size + (*tmp)->edge_size;
		if (n < (*tmp)->room->vertex_size)
		{
			(*tmp)->room->vertex_size = n;
			(*tmp)->room->prev = *current;
			*flag = 1;
		}
		*tmp = (*tmp)->next;
	}
}

int		bellman_ford(t_frame *frame, t_room *start)
{
	t_room	*current;
	t_link	*tmp;
	int		i;
	int		flag;

	i = 0;
	current = start;
	while (i++ < (frame->num_rooms - 1))
	{
		flag = 0;
		current = start;
		while (current)
		{
			tmp = current->output;
			bellman_ford_2(&tmp, &current, &flag);
			current = current->next;
		}
		if (!flag)
			break ;
	}
	if (frame->end->vertex_size == INT_MAX)
		return (1);
	return (0);
}
