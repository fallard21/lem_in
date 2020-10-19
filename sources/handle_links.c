/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_links.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 19:42:43 by user              #+#    #+#             */
/*   Updated: 2020/10/16 19:05:07 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lem_in.h"

t_link		*create_link(t_room *room, t_frame *stor, int weight)
{
	t_link	*link;

	link = NULL;
	if (!(link = ft_calloc(1, sizeof(t_link))))
		lem_error(LINKS_ERR, stor);
	link->room = room;
	link->next = NULL;
	link->prev = NULL;
	link->edge_size = weight;
	link->status = 0;
	return (link);
}

int			set_links(t_room *room1, t_room *room2, t_frame *stor)
{
	t_link		*link;

	if (!(link = room1->links))
	{
		if (!(room1->links = create_link(room2,
		stor, room1->level == 0 ? 1 : 0)))
			lem_error(LINKS_ERR, stor);
		room1->num_links++;
		return (0);
	}
	while (link)
	{
		if (!ft_strcmp(link->room->name, room1->name) ||
		!ft_strcmp(link->room->name, room2->name))
			return (2);
		if (link->next)
			link = link->next;
		else
			break ;
	}
	room1->num_links++;
	if (!(link->next = create_link(room2, stor, room1->level == 0 ? 1 : 0)))
		lem_error(LINKS_ERR, stor);
	return (0);
}

int			find_rooms(t_room *room, char *r1, char *r2, t_frame *stor)
{
	t_room		*copy;
	t_room		*room1;
	t_room		*room2;

	room1 = NULL;
	room2 = NULL;
	copy = room;
	while (copy && (!room1 || !room2))
	{
		if (!ft_strcmp(copy->name, r1))
			room1 = copy;
		else if (!ft_strcmp(copy->name, r2))
			room2 = copy;
		copy = copy->next;
	}
	if (!room1 || !room2)
		return (1);
	if (set_links(room1, room2, stor) || set_links(room2, room1, stor))
		return (2);
	return (0);
}

int			handle_links(t_room *room, char *line, t_frame *stor)
{
	char		*room1;
	char		*room2;
	int			res;

	if (!(stor->split = ft_strsplit(line, '-')))
		lem_error(ALLOC_ERR, stor);
	if (!(room1 = stor->split[0]) ||
	!(room2 = stor->split[1]) ||
	(res = find_rooms(room, room1, room2, stor)))
	{
		res == 1 ? lem_error(LINKS_ERR, stor) :
		lem_error(LINKS_DUPL_ERR, stor);
	}
	ft_free_splited(stor->split);
	stor->split = NULL;
	return (1);
}
