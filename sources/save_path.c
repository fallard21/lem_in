/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 08:44:09 by fallard           #+#    #+#             */
/*   Updated: 2020/10/13 16:12:39 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lem_in.h"

t_link	*get_status_link(t_link *link)
{
	t_link	*res;

	res = NULL;
	while (link)
	{
		if (link->status == 1)
		{
			res = link;
			break ;
		}
		link = link->next;
	}
	return (res);
}

int		insert_link(t_link **head, t_room *room)
{
	t_link	*tmp;

	if (*head == NULL)
	{
		if (!(*head = ft_calloc(1, sizeof(t_link))))
			return (1);
		(*head)->room = room;
	}
	else
	{
		if (!(tmp = ft_calloc(1, sizeof(t_link))))
			return (1);
		tmp->room = room;
		tmp->next = *head;
		*head = tmp;
	}
	return (0);
}

int		init_link_list(t_link *link, t_link **path, int *len)
{
	t_room *current;
	t_link *tmp;
	t_link *prev;

	prev = *path;
	current = link->room;
	while (1)
	{
		if (!(tmp = get_status_link(current->output)))
			break ;
		if (ft_strcmp(tmp->room->name, (*path)->room->name) == 0)
		{
			current = tmp->room;
			continue ;
		}
		if (insert_link(path, tmp->room))
			return (free_link(path));
		(*len)++;
		prev->prev = *path;
		prev = *path;
		current = tmp->room;
	}
	return (0);
}

void	init_start(t_frame *frame, t_link **start, t_link *links)
{
	if (!(*start = ft_calloc(1, sizeof(t_link))))
		lem_error(ALLOC_ERR, frame);
	(*start)->room = links->room;
	if (!((*start)->next = ft_calloc(1, sizeof(t_link))))
	{
		ft_memdel((void**)&(*start));
		lem_error(ALLOC_ERR, frame);
	}
	(*start)->next->room = frame->end;
}

void	get_all_paths(t_frame *frame)
{
	t_path	**tmp;
	t_link	*links;
	t_link	*next;
	t_link	*start;

	tmp = &frame->paths;
	links = frame->end->output;
	while (links)
	{
		next = links->next;
		if (!(*tmp = ft_calloc(1, sizeof(t_path))))
			lem_error(ALLOC_ERR, frame);
		init_start(frame, &start, links);
		(*tmp)->end = start;
		(*tmp)->start = start;
		if (init_link_list(links, &(*tmp)->start, &(*tmp)->len))
			lem_error(ALLOC_ERR, frame);
		tmp = &(*tmp)->next;
		links = next;
	}
	frame->paths = sort_path(frame->paths);
	if (frame->key_p)
		ft_print_path(frame, frame->paths);
}
