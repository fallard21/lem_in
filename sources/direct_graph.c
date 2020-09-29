/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direct_graph.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 17:13:02 by user              #+#    #+#             */
/*   Updated: 2020/09/29 17:38:50 by user             ###   ########.fr       */
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

void		redirect_start(t_frame *stor)
{
	t_link		*link;
	t_link		*tmp;

	stor->start->output = stor->start->links;
	stor->start->output_links = stor->start->num_links;
	link = stor->start->links;
	while (link)
	{
		if (!link->room->input || link->room->num_links == 1)
			link->room->input = create_link(stor->start, stor, 1);
		else
		{				
			tmp = link->room->input;
			while (tmp && tmp->next)
				tmp = tmp->next;
			tmp->next = create_link(stor->start, stor, 1);
		}
		link->room->input_links++;
		link = link->next;
	}
}

void		redirect_end_input(t_link **head, t_link *link, t_frame *stor)
{
	if (!stor->end->input &&
	(stor->end->input = create_link(link->room->next, stor, 1)))
		(*head) = stor->end->input;
	else
	{
		if (stor->end->input->room->level == 0)
			(*head) = stor->end->input;
		stor->end->input->next = create_link(link->room->next, stor, 1);
		stor->end->input = stor->end->input->next;
	}
}

void		redirect_end(t_frame *stor)
{
	t_link		*link;
	t_link		*head;
	t_link		*tmp;

	stor->end->input_links = stor->end->num_links;
	link = stor->end->links;
	while (link)
	{
		if (!(link = link->room->level == 0 ? link->next : link))
			break ;
		redirect_end_input(&head, link, stor);
		if (!link->room->next->output || link->room->next->output_links == 1)
			link->room->next->output = create_link(stor->end, stor, 1);
		else if (link)
		{
			tmp = link->room->next->output;
			while (tmp && tmp->next)
				tmp = tmp->next;
			tmp->next = create_link(stor->end, stor, 1);
		}
		link->room->next->output_links++;
		link = link->next;
	}
	stor->end->input = head;
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
	if (check_only_start_end(room))
		return ;
	while (link)
	{
		if (!(link = check_skiping(link->room, 0) ? link->next : link))
			break ;
		if (!out->output && (out->output = create_link(link->room, stor, 1)))
			head_out = out->output;
		else if (out->output->next = create_link(link->room, stor, 1))
			out->output = out->output->next;
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
	if (check_only_start_end(room))
		return ;
	while (link)
	{
		if (!(link = check_skiping(link->room, 0) ? link->next : link))
			break ;
		if (!room->input &&(room->input = create_link(link->room->next, stor, 1)))
			head_inp = room->input;
		else if (room->input->next = create_link(link->room->next, stor, 1))
			room->input = room->input->next;
		room->input_links++;
		link = link->next;
	}
	room->input = head_inp;
}

// Обработать случай для графа из двух комнат start-end. Сразу отправляем в печать

void		set_direct_graph(t_frame *stor)
{
	t_room		*copy;

	duplicate_rooms(stor);
	if (stor->num_rooms == 2)
		return ;
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
