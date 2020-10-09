/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_flow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 18:56:58 by fallard           #+#    #+#             */
/*   Updated: 2020/10/09 21:08:30 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lem_parser.h"

int		get_num_paths(t_link *output)
{
	int count;

	count = 0;
	while (output)
	{
		if (output->status)
			count++;
		output = output->next;
	}
	return (count);
}

int		find_max(int *arr, int size)
{
	int i;
	int max;

	i = 0;
	max = arr[0];
	while (i < size)
	{
		if (arr[i] > max)
			max = arr[i];
		i++;
	}
	return (max);
}

int		calculate_max_step(t_frame *frame, t_flow *flow)
{
	int num_ants;
	int i;
	int step;

	num_ants = frame->num_ants;
	while (num_ants != 0)
	{
		i = 0;
		while (i < flow->size)
		{
			if (i + 1 == flow->size)
				break ;
			if (flow->path[i + 1] + flow->ants[i + 1] > 
					flow->path[i] + flow->ants[i])
				break ;
			i++;
		}
		flow->ants[i] = flow->ants[i] + 1;
		flow->diff[i] = flow->path[i] + flow->ants[i];
		num_ants--;
	}
	step = find_max(flow->diff, flow->size);
	if (step > frame->current_steps)
		return (1);
	frame->current_steps = step;
	return (0);
}

int		calculate_path_len(t_flow *flow, t_link *link)
{
	t_room	*current;
	t_link	*tmp;
	int		i;
	int		j;

	i = 0;
	while (link)
	{
		j = 0;
		if (link->status)
		{
			current = link->room;
			while (1)
			{
				if (!(tmp = get_status_link(current->output)))
					break ;
				current = tmp->room;
				j++;
			}
			flow->path[i] = j / 2;
			i++;
		}
		link = link->next;
	}
}

int		calculate_steps(t_frame *frame)
{
	t_flow	*flow;
	int		flag;

	flag = 0;
	
	if (!(frame->flow = ft_calloc(1, sizeof(t_flow))))
		lem_error(ALLOC_ERR, frame);
	flow = frame->flow;
	if (!(flow->size = get_num_paths(frame->end->output)))
		return (0);
	//ft_printf("Numbers of path: %d\n", flow.size);
	if (!(flow->path = ft_calloc(flow->size, sizeof(int))))
		lem_error(ALLOC_ERR, frame);
	if (!(flow->ants = ft_calloc(flow->size, sizeof(int))))
		lem_error(ALLOC_ERR, frame);
	if (!(flow->diff = ft_calloc(flow->size, sizeof(int))))
		lem_error(ALLOC_ERR, frame);
	calculate_path_len(flow, frame->end->output);
	//bubble_sort(flow->path, flow->size);	// CHANGE TO QS
	ft_quick_sort(flow->path, 0, flow->size - 1);
	if (calculate_max_step(frame, flow))
		flag = 1;
	free_flow(&frame->flow);
	return (flag);
}
