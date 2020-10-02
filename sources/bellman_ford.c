/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bellman_ford.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 14:15:38 by user              #+#    #+#             */
/*   Updated: 2020/10/02 14:16:22 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lem_parser.h"

static int global = 1;

t_recovery	*free_prev_list(t_recovery **head)
{
	t_recovery	*next;

	while (*head)
	{
		next = (*head)->next;
		free(*head);
		*head = next;
	}
	return (NULL);
}

int		insert_recovery(t_recovery **head, t_room *room)
{
	t_recovery	*tmp;

	if (*head == NULL)
	{
		if (!(*head = ft_calloc(1, sizeof(t_recovery))))
			return (1);
		(*head)->room = room;
	}
	else
	{
		if (!(tmp = ft_calloc(1, sizeof(t_recovery))))
			return (1);
		tmp->room = room;
		tmp->next = *head;
		*head = tmp;
	}
	return (0);
}

t_recovery	*restore_path(t_room *end)
{
	t_room *tmp;
	t_recovery *p;
	
	p = NULL;
	tmp = end;
	while (tmp)
	{
		if (insert_recovery(&p, tmp) == 1)
			return (free_prev_list(&p));
		tmp = tmp->prev;
	}

	return (p);
}

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

void	reverse_path(t_recovery *p, t_room *current) //
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
	t_recovery	*p;

	p = NULL;
	while (bellman_ford(frame, frame->start) == 0)
	{
		if (!(p = restore_path(frame->end)))
			lem_error(ALLOC_ERR, frame);
		reverse_path(p,  frame->start);
		reinit_sizes(frame->map);
		free_prev_list(&p);
	}
	//print_suurb(frame->map);
	//print_patchs(frame->end);
	get_path(frame);
	
	return ;
}


// 1) Цикл Беллмана-Форда, пока есть пути // DONE ?
	// 1.1) Восстановление пути после Б-Ф // DONE ?
	// 1.2) Реверс ребер (отрицательная стоимость + status link = 1) // DONE ??
	// 1.3) Обновление prev и vertex_size // DONE ??
// 2) Поиск и удаление встречных ребер // NOT
// 3) Восстановление всех путей по status = 1 линкам. // NOT
