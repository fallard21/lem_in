/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 08:44:09 by fallard           #+#    #+#             */
/*   Updated: 2020/10/02 00:23:12 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lem_parser.h"

t_link	*get_status_link(t_link *link)
{
	t_link	*res;

	res = NULL;
	while (link)
	{
		if (link->status == 1)
			res = link;
		link = link ->next;
	}
	return (res);
}

int	insert_link(t_link **head, t_room *room, t_link *prev)
{
	t_link	*tmp;

	if (*head == NULL)
	{
		if (!(*head = ft_calloc(1, sizeof(t_link))))
			return (1);
		(*head)->room = room;
		(*head)->prev = prev;
	}
	else
	{
		if (!(tmp = ft_calloc(1, sizeof(t_link))))
			return (1);
		tmp->room = room;
		tmp->prev = prev;
		tmp->next = *head;
		*head = tmp;
	}
	return (0);
}

t_link	*get_link_list(t_frame *frame, t_link *link)
{
	t_link *res;
	t_room *current;
	t_link *tmp;
	t_link *prev;

	res = NULL;
	prev = NULL;
	current = link->room;
	while (1)
	{
		if (!(tmp = get_status_link(current->output)))
			break ;
		if (res && ft_strcmp(tmp->room->name, res->room->name) == 0)
		{
			current = tmp->room;
			continue ;
		}
		if (insert_link(&res, tmp->room, prev))
			return (free_link(&res));
		prev = res;
		current = tmp->room;
	}
	return (res);
}

void	get_path(t_frame *frame)
{
	t_path **tmp;
	t_link	*links;

	tmp = &frame->paths;
	links = frame->end->output;
	while (links)
	{
		if (!(*tmp = ft_calloc(1, sizeof(t_path))))
			lem_error(ALLOC_ERR, frame);
		(*tmp)->end = links;
			ft_printf("{1}%s{0}\n", links->room->name); // DEL

		if (!((*tmp)->start = get_link_list(frame, links)))
			lem_error(ALLOC_ERR, frame);

			print_links((*tmp)->start);	// DEL
		tmp = &(*tmp)->next;
		links = links->next;
	}
}
