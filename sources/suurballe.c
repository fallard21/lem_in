/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurballe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 17:14:32 by fallard           #+#    #+#             */
/*   Updated: 2020/10/09 19:54:22 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lem_parser.h"

void	find_link(t_link **tmp, t_link **prev, char *name)
{
	while (*tmp)
	{
		if (ft_strcmp(name, (*tmp)->room->name) == 0)
			break ;
		*prev = *tmp;
		*tmp = (*tmp)->next;
	}
}

void	out_to_in(t_room *current, char *name)
{
	t_link	*tmp;
	t_link	*prev;

	tmp = current->output;
	prev = NULL;
	find_link(&tmp, &prev, name);
	if (!prev)
		current->output = tmp->next;
	else
		prev->next = tmp->next;
	prev = current->input;
	while (prev && prev->next)
		prev = prev->next;
	if (!prev)
		current->input = tmp;
	else
		prev->next = tmp;
	tmp->next = NULL;
	tmp->edge_size = tmp->edge_size * -1;
	tmp->status = (tmp->status) ? 0 : 1;
}

void	in_to_out(t_room *current, char *name)
{
	t_link	*tmp;
	t_link	*prev;

	tmp = current->input;
	prev = NULL;
	find_link(&tmp, &prev, name);
	if (!prev)
		current->input = tmp->next;
	else
		prev->next = tmp->next;
	prev = current->output;
	while (prev && prev->next)
		prev = prev->next;
	if (!prev)
		current->output = tmp;
	else
		prev->next = tmp;
	tmp->next = NULL;
	tmp->edge_size = tmp->edge_size * -1;
	tmp->status = (tmp->status) ? 0 : 1;
}

void	reverse_path(t_find *p, t_room *current)
{
	t_link *tmp;
	t_room *next;

	while (p && p->next)
	{
		out_to_in(p->room, p->next->room->name);
		in_to_out(p->next->room, p->room->name);
		p = p->next;
	}
}

void	suurballe(t_frame *frame)
{
	frame->current_steps = INT_MAX;
	while (bellman_ford(frame, frame->start) == 0)
	{
		if (!(frame->find_way = restore_path(frame->end)))
			lem_error(ALLOC_ERR, frame);
		reverse_path(frame->find_way, frame->start);
			//print_patchs(frame->end); ft_printf("\n");
		if (calculate_steps(frame) == 1)
		{
			frame->find_way = ft_reverse_list(frame->find_way);
			reverse_path(frame->find_way, frame->start);
			break ;
		}
		reinit_sizes(frame->map);
		free_prev_list(&frame->find_way);
	}
		//print_suurb(frame->map);
		//print_patchs(frame->end);
		//ft_printf("FINAL:\n");calculate_flow(frame);
	get_all_paths(frame);
	//test_move_ants(frame, i);
	return ;
}
