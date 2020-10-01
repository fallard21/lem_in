/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direct_graph.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 17:13:02 by user              #+#    #+#             */
/*   Updated: 2020/10/01 21:54:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_parser.h"
#include "struct.h"

int			check_only_start_end(t_room *room)
{
	t_link	*link;

	link = room->links;
	if (room->num_links == 2 &&
	(link->room->level == 0 || link->room->level == INT_MAX) &&
	(link->next->room->level == 0 || link->next->room->level == INT_MAX))
		return (1);
	return (0);
}

int			check_skiping(t_room *room, int check_links)
{
	if (check_links)
		if (!room->num_links || room->level == INT_MAX || room->level == 0)
			return (1);
	if (!check_links)
		if (room->level == INT_MAX || room->level == 0)
			return (1);
	return (0);
}

void		set_simplest_grapth(t_frame *stor)
{
	stor->start->output = create_link(stor->end, stor, 1);
	stor->start->output_links++;
	stor->end->input = create_link(stor->start, stor, 1);
	stor->end->input_links++;
	stor->end->next = NULL;
	stor->map = stor->start;
	stor->map->next = stor->end;
}

// Обработать случай для графа из двух комнат start-end. Сразу отправляем в печать

void		set_direct_graph(t_frame *stor)
{
	t_room		*copy;

	duplicate_rooms(stor);
	if (stor->num_rooms == 2)
	{
		set_simplest_grapth(stor);
		return ;
	}
	copy = stor->map->next;
	while (copy && copy->level != INT_MAX)
	{
		redirect_input_links(copy, stor);
		redirect_output_links(copy, stor);
		copy = copy->next ? copy->next->next : NULL;
	}
	redirect_start(stor);
	redirect_end(stor);
	print_room_list(stor, stor->map);
}
