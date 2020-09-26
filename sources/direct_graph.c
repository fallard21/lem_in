/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direct_graph.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 17:13:02 by user              #+#    #+#             */
/*   Updated: 2020/09/27 02:54:51 by user             ###   ########.fr       */
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

void		*duplicate_rooms(t_frame *stor)
{
	t_room		*tmp;
	t_room		*head;

	head = stor->map;
	while (stor->map)
	{
		if (!stor->map->next->links)
		{
			tmp = stor->map->next;
			stor->map->next = stor->map->next->next;
			del_room(tmp);
		}
		if (stor->map->level == INT_MAX || stor->map->level == 0)
			stor->map = stor->map->next;
		else
		{
			tmp = stor->map->next;
			stor->map->suur_type = IN;
			stor->map->next = create_out_room(stor->map);
			stor->map->next->next = tmp;
			stor->map = stor->map->next->next;
		}
	}
	stor->map = head;
	stor->num_rooms = (stor->num_rooms * 2) - 2;
}

void		redirect_start_end(t_frame *stor)
{
	t_link		*link;

	stor->start->output = stor->start->links;
	stor->start->output_links = stor->start->num_links;
	link = stor->start->links;
	while (link)
	{
		if (!link->room->input)
			link->room->input = create_link(stor->start, stor);
		else
			link->room->input->next = create_link(stor->start, stor);
		link->room->input_links++;
		link = link->next;
	}
	stor->end->input = stor->end->links;
	stor->end->input_links = stor->end->num_links;
	link = stor->end->links;
	while (link)
	{
		if (!link->room->next->output)
			link->room->next->output = create_link(stor->end, stor);
		else
			link->room->next->output->next = create_link(stor->end, stor);
		link->room->next->output_links++;
		link = link->next;
	}
}

void		redirect_output_links(t_room *room, t_frame *stor)
{
	t_link		*link;
	t_link		*head_out;
	t_room		*out;

	out = room->next;
	link = room->links;
	out->input = create_link(room, stor);
	out->input_links++;
	while (link)
	{
		if (!out->output)
		{
			out->output = create_link(link->room->suur_type == 0 ?
			link->room->next : link->room, stor);
			head_out = out->output;
		}
		else
		{
			out->output->next = create_link(link->room->suur_type == 0 ?
			link->room->next : link->room, stor);
			out->output = out->output->next;
		}
		out->output_links++;
		link = link->room->suur_type == 0 && link->next ? link->next->next : link->next;
	}
	out->output = head_out;

}

void		redirect_input_links(t_room *room, t_frame *stor)
{
	t_link		*link;
	t_link		*head_inp;

	link = room->links;
	room->output = create_link(room->next, stor);
	room->output_links++;
	while (link)
	{
		if (!room->input)
		{
			room->input = create_link(link->room->suur_type == 0 ?
			link->room->next->next : link->room->next, stor);
			head_inp = room->input;
		}
		else
		{
			room->input->next = create_link(link->room->suur_type == 0 ?
			link->room->next->next : link->room->next, stor);
			room->input = room->input->next;
		}
		room->input_links++;
		link = link->room->suur_type == 0 && link->next ? link->next->next : link->next;
	}
	room->input = head_inp;

}

void		set_direct_graph(t_frame *stor)
{
	t_room		*copy;

	duplicate_rooms(stor);
	copy = stor->map;
	while (copy)
	{
		if (copy->level == INT_MAX || copy->level == 0)
			copy = copy->next;
		else if (!copy->links)
			copy = copy->next ? copy->next->next : NULL;
		else
		{
			redirect_input_links(copy, stor);
			redirect_output_links(copy, stor);
			copy = copy->next ? copy->next->next : NULL;
		}
	}
	redirect_start_end(stor);
	print_room_list(stor, stor->map);
}
