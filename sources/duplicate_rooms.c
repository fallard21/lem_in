/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicate_rooms.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 17:44:55 by user              #+#    #+#             */
/*   Updated: 2020/10/01 21:45:10 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_parser.h"
#include "struct.h"

void		set_out_room_params(t_room *new, t_room *room)
{
	new->ants = room->ants;
	new->ant_name = room->ant_name;
	new->level = room->level;
	new->vertex_size = room->vertex_size;
	new->num_links = 0;
	new->input_links = 0;
	new->output_links = 0;
	new->visit = room->visit;
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
	new->name = room->name;
	new->coord[0] = room->coord[0];
	new->coord[1] = room->coord[1];
	set_out_room_params(new, room);
	return (new);
}

void		skip_room(t_frame *stor, t_room **map, int frst)
{
	t_room		*tmp;
	t_room		*copy;

	printf("skip start map = %s\n", (*map) ? (*map)->name : NULL);
	tmp = frst ? (*map) : (*map)->next;
	printf("\nskip before | tmp = %s\n", tmp ? tmp->name : NULL);
	while(tmp && check_skiping(tmp, 1))
	{
		printf("skip in loop | tmp = %s\n", tmp ? tmp->name : NULL);
		if (tmp && !tmp->links)
		{
			printf("{ 1 }\n");
			copy = tmp;
			tmp = tmp->next;
			del_room(&copy);
			stor->num_rooms--;
		}
		if (tmp && (tmp->level == INT_MAX || tmp->level == 0))
		{
			printf("{ 2 }\n");
			tmp = tmp->next;
		}
	}
	printf("skip after | tmp = %s\n", tmp ? tmp->name : NULL);
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
	{
		printf("skip first room\n");
		skip_room(stor, &stor->map, 1);
		
	}
	head = stor->map;
	while (stor->map)
	{
		printf("start loop | name = %s\n", stor->map ? stor->map->name : NULL);
		if (stor->map->next && check_skiping(stor->map->next, 1))
			skip_room(stor, &stor->map, 0);
		else if (stor->map && split_room(stor, &stor->map))
			break ;
		printf("end loop | name = %s\n", stor->map ? stor->map->name : NULL);
	}
	printf("head = %s\n", head ? head->name : NULL);
	stor->num_rooms = (stor->num_rooms * 2) - 2;
	if (stor->num_rooms == 2)
		return ;
	if (head->level != 0)
		stor->start->next = head;
	stor->map = stor->start;
	stor->end->next = NULL;
}
