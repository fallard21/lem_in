/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bellman_ford.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 20:02:05 by fallard           #+#    #+#             */
/*   Updated: 2020/10/01 23:50:19 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lem_parser.h"

static int global = 1;

void	insert_p(t_prev **head, t_room *room)
{
	t_prev	*tmp;

	if (*head == NULL)
	{
		*head = ft_calloc(1, sizeof(t_prev));
		(*head)->room = room;
	}
	else
	{
		tmp = ft_calloc(1, sizeof(t_prev));
		tmp->room = room;
		tmp->next = *head;
		*head = tmp;
	}
}

t_prev	*restore_path(t_room *end)
{
	t_room *tmp;
	t_prev *p;
	
	p = NULL;
	tmp = end;
	while (tmp)
	{
		insert_p(&p, tmp);
		tmp = tmp->prev;
	}

	/////////////////////
	/*
	t_prev *tmp_p = p;
	ft_printf("\npath %d: ", global);
	global++;
	while (tmp_p)
	{
		if (tmp_p->room->suur_type == 1)
			ft_printf("{3}%s -> {0}", tmp_p->room->name);
		else if (tmp_p->room->suur_type == 2)
			ft_printf("{2}%s' -> {0}", tmp_p->room->name);
		else
			ft_printf("{1}%s -> {0}", tmp_p->room->name);
		tmp_p = tmp_p->next;
	}
	ft_printf("\n\n");
	*/
	///////////////////////
	return (p);
}

// void	add_rev_edge(t_room *from, t_room *to, int size)
// {
// 	t_link	*tmp;

// 	if (!from->output)
// 	{
// 		from->output = ft_calloc(1,sizeof(t_link));
// 		from->output->room = to;
// 		from->output->edge_size = size * -1;;
// 		from->output->status = 1;
// 	}
// 	else
// 	{
// 		tmp = from->output;
// 		while (tmp && tmp->next)
// 			tmp = tmp->next;
// 		tmp->next = ft_calloc(1,sizeof(t_link));
// 		tmp->next->room = to;
// 		tmp->next->edge_size = size * -1;
// 		tmp->next->status = 1;
// 	}
// }

void	out_to_in(t_room *current, char *name)
{
	t_link	*tmp;
	t_link	*prev;

	tmp = current->output;
	prev = NULL;
	while (tmp)
	{
		if (ft_strcmp(name, tmp->room->name) == 0)
			break ;
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp->status)
	{
		tmp->status = 0;
		return ;
	}

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
	
	tmp->next  = NULL;
	tmp->edge_size = tmp->edge_size * -1;
	tmp->status = 1;
}

void	in_to_out(t_room *current, char *name)
{
	t_link	*tmp;
	t_link	*prev;

	tmp = current->input;
	prev = NULL;
	while (tmp)
	{
		if (ft_strcmp(name, tmp->room->name) == 0)
			break ;
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp->status)
	{
		tmp->status = 0;
		return ;
	}
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
	tmp->status = 1;
}

void	reverse_path(t_prev *p, t_room *current) //
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

int		bellman_ford(t_frame *frame, t_room *start)
{
	t_room	*current;
	t_link	*tmp;
	int		i;
	int		flag;

	i = 0;
	current = start;
	while (i++ < (frame->num_rooms - 1))
	{
		flag = 0;
		current = start;
		while (current)
		{
			tmp = current->output;
			while (tmp)
			{
				if (current->vertex_size == INT_MAX)
					break ;
				if (current->vertex_size + tmp->edge_size < tmp->room->vertex_size)
				{
					tmp->room->vertex_size = current->vertex_size + tmp->edge_size;
					tmp->room->prev = current;
					flag = 1;
				}
				tmp = tmp->next;
			}
			current = current->next;
		}
		if (!flag)
			break ;
	}
	if (frame->end->vertex_size == INT_MAX)
		return (1);
	return (0);
}

void	reinit_sizes(t_room *start)
{
	t_room *tmp;

	tmp = start;
	while (tmp)
	{
		tmp->vertex_size = INT_MAX;
		tmp->prev = NULL;
		tmp = tmp->next;
	}
	start->vertex_size = 0;
}

void	suurballe(t_frame *frame)
{
	t_prev	*p;
	int i = 0;

	//ft_printf("KEK\n");
	// print_suurb(frame->map);
	while (bellman_ford(frame, frame->start) == 0)
	{
		i++;
		p = restore_path(frame->end);
		reverse_path(p,  frame->start);
		reinit_sizes(frame->map);
		// free (p);
	}
	print_suurb(frame->map);
	print_patchs(frame->end);
	ft_printf("LINES: %d\n", i);
	get_path(frame);
	return ;
}


// 1) Цикл Беллмана-Форда, пока есть пути // DONE ?
	// 1.1) Восстановление пути после Б-Ф // DONE ?
	// 1.2) Реверс ребер (отрицательная стоимость + status link = 1) // DONE ??
	// 1.3) Обновление prev и vertex_size // DONE ??
// 2) Поиск и удаление встречных ребер // NOT
// 3) Восстановление всех путей по status = 1 линкам. // NOT
