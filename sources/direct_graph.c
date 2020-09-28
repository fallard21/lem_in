/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direct_graph.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 17:13:02 by user              #+#    #+#             */
/*   Updated: 2020/09/29 01:33:50 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_parser.h"
#include "struct.h"

//  edge_size = 0 (для дублей), 1 (для остальных)

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

int			check_skiping(t_room *room, int no_links)
{
	if (no_links)
		if (!room->links || room->level == INT_MAX || room->level == 0)
			return (1);
	if (!no_links)
		if (room->level == INT_MAX || room->level == 0)
			return (1);
	return (0);
}

void		skip_room(t_frame *stor, t_room **map, int frst)
{
	t_room		*tmp;
	t_room		*copy;

	tmp = frst ? (*map) : (*map)->next;
	while(tmp && check_skiping(tmp, 1))
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

void		*duplicate_rooms(t_frame *stor)
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
	if (head->level != 0)
		stor->start->next = head;
	stor->map = stor->start;
	stor->end->next = NULL;
	stor->num_rooms = (stor->num_rooms * 2) - 2;
}

void		redirect_start(t_frame *stor)
{
	t_link		*link;
	t_link		*tmp;

	stor->start->output = stor->start->links;
	stor->start->output_links = stor->start->num_links;
	link = stor->start->links;
	while (link)
	{
		if (!link->room->input)
			link->room->input = create_link(stor->start, stor, 1);
		else
		{
			tmp = link->room->input;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = create_link(stor->start, stor, 1);
		}
		link->room->input_links++;
		link = link->next;
	}
}

void		redirect_end(t_frame *stor)
{
	t_link		*link;
	t_link		*inp_head;
	t_link		*tmp;

	stor->end->input_links = stor->end->num_links;
	link = stor->end->links;
	while (link)
	{
		if (!stor->end->input)
		{
			stor->end->input = create_link(link->room->next, stor, 1);
			inp_head = stor->end->input;
		}
		else
		{
			stor->end->input->next = create_link(link->room->next, stor, 1);
			stor->end->input = stor->end->input->next;
		}
		if (!link->room->next->output)
			link->room->next->output = create_link(stor->end, stor, 1);
		else
		{
			tmp = link->room->next->output;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = create_link(stor->end, stor, 1);
		}
		link->room->next->output_links++;
		link = link->next;
	}
	stor->end->input = inp_head;
}

void		redirect_output_links(t_room *room, t_frame *stor)
{
	t_link		*link;
	t_link		*head_out;
	t_room		*out;

	out = room->next;
	link = room->links;
	out->input = create_link(room, stor, 0);
	out->input_links++;
	while (link)
	{
		if (!(link = check_skiping(link->room, 0) ? link->next : link))
			break ;
		if (!out->output)
		{
			out->output = create_link(link->room, stor, 1);
			head_out = out->output;
		}
		else
		{
			out->output->next = create_link(link->room, stor, 1);
			out->output = out->output->next;
		}
		out->output_links++;
		link = link->next;
	}
	out->output = head_out;
}

void		redirect_input_links(t_room *room, t_frame *stor)
{
	t_link		*link;
	t_link		*head_inp;

	link = room->links;
	room->output = create_link(room->next, stor, 0);
	room->output_links++;
	while (link)
	{
		if (!(link = check_skiping(link->room, 0) ? link->next : link))
			break ;
		if (!room->input)
		{
			room->input = create_link(link->room->next, stor, 1);
			head_inp = room->input;
		}
		else
		{
			room->input->next = create_link(link->room->next, stor, 1);
			room->input = room->input->next;
		}
		room->input_links++;
		link = link->next;
	}
	room->input = head_inp;
}

void		set_direct_graph(t_frame *stor)
{
	t_room		*copy;

	duplicate_rooms(stor);
	copy = stor->map->next;
	while (copy && copy->level != INT_MAX)
	{
		redirect_input_links(copy, stor);
		redirect_output_links(copy, stor);
		copy = copy->next ? copy->next->next : NULL;
	}
	redirect_start(stor);
	redirect_end(stor);
	// print_room_list(stor, stor->map);
}
