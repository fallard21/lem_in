/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicate_rooms.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 17:44:55 by user              #+#    #+#             */
/*   Updated: 2020/10/12 18:58:10 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "struct.h"

void		set_out_room_params(t_room *new, t_room *room)
{
	new->ants = room->ants;
	new->ant_name = room->ant_name;
	new->level = room->level;
	new->vertex_size = room->vertex_size;
	new->num_links = 0;
	new->suur_type = OUT;
	new->prev = NULL;
	new->links = NULL;
	new->output = NULL;
	new->input = NULL;
	new->next = NULL;
}

t_room		*create_out_room(t_room *room)
{
	t_room		*new;

	if (!(new = ft_calloc(1, sizeof(t_room))))
		return (NULL);
	new->name = ft_strdup(room->name);
	new->coord[0] = room->coord[0];
	new->coord[1] = room->coord[1];
	set_out_room_params(new, room);
	return (new);
}

void		skip_room(t_frame *stor, t_room **map, int frst)
{
	t_room		*tmp;
	t_room		*copy;

	tmp = frst ? (*map) : (*map)->next;
	while (tmp && check_skiping(tmp, 1))
	{
		if (tmp && !tmp->links)
		{
			copy = tmp;
			tmp = tmp->next;
			del_room(&copy);
			stor->num_rooms--;
		}
		if (tmp && (tmp->level == INT_MAX || tmp->level == 0))
			tmp = tmp->next;
	}
	if (frst)
		(*map) = tmp;
	else
		(*map)->next = tmp;
}

int			split_room(t_frame *stor, t_room **map)
{
	t_room		*tmp;

	tmp = (*map)->next;
	(*map)->suur_type = IN;
	(*map)->next = create_out_room((*map));
	(*map)->next->next = tmp ? tmp : stor->end;
	(*map) = (*map)->next->next;
	if ((*map)->level == INT_MAX)
		return (1);
	return (0);
}

void		duplicate_rooms(t_frame *stor)
{
	t_room		*head;

	if (stor->map && check_skiping(stor->map, 1))
		skip_room(stor, &stor->map, 1);
	head = stor->map;
	while (stor->map)
	{
		if (stor->map->next && check_skiping(stor->map->next, 1))
			skip_room(stor, &stor->map, 0);
		else if (stor->map && split_room(stor, &stor->map))
			break ;
	}
	stor->num_rooms = (stor->num_rooms * 2) - 2;
	if (stor->num_rooms == 2)
		return ;
	if (head->level != 0)
		stor->start->next = head;
	stor->map = stor->start;
	stor->end->next = NULL;
}
