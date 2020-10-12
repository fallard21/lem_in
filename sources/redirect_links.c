/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_links.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 17:47:06 by user              #+#    #+#             */
/*   Updated: 2020/10/12 16:27:22 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "struct.h"

void		redirect_start(t_frame *stor)
{
	t_link		*link;
	t_link		*tmp;

	stor->start->output = stor->start->links;
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


	link = stor->end->links;
	while (link)
	{
		if (!(link = link->room->level == 0 ? link->next : link))
			break ;
		redirect_end_input(&head, link, stor);
		if (!link->room->next->output)
			link->room->next->output = create_link(stor->end, stor, 1);
		else if (link)
		{
			tmp = link->room->next->output;
			while (tmp && tmp->next)
				tmp = tmp->next;
			tmp->next = create_link(stor->end, stor, 1);
		}
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
		link = link->next;
	}
	room->input = head_inp;
}
