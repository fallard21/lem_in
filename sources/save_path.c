/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 08:44:09 by fallard           #+#    #+#             */
/*   Updated: 2020/10/01 14:21:29 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lem_parser.h"

t_link	*get_status_link(t_link *link)
{
	t_link	*res;

	res = NULL;
	while (link)
	{
		if (link->status == 1)
			res = link;
		link = link ->next;
	}
	return (res);
}

int	insert_link(t_link **head, t_room *room, t_link *prev)
{
	t_link	*tmp;

	if (*head == NULL)
	{
		if (!(*head = ft_calloc(1, sizeof(t_link))))
			return (1);
		(*head)->room = room;
		(*head)->prev = prev;
	}
	else
	{
		if (!(tmp = ft_calloc(1, sizeof(t_link))))
			return (1);
		tmp->room = room;
		tmp->prev = prev;
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

	prev = NULL;
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
		if (insert_link(path, tmp->room, prev))
			return (free_link(path));
		(*len)++;
		prev = *path;
		current = tmp->room;
	}
	return (0);
}

void	get_path(t_frame *frame)
{
	t_path **tmp;
	t_link	*links;
	t_link *next;

	tmp = &frame->paths;
	links = frame->end->output;
	while (links)
	{
		next = links->next;
		if (!(*tmp = ft_calloc(1, sizeof(t_path))))
			lem_error(ALLOC_ERR, frame);
		links->next = NULL;
		(*tmp)->end = links;
		(*tmp)->start = links;
			ft_printf("{1}%s{0}\n", links->room->name); // DEL

		if (init_link_list(links, &(*tmp)->start, &(*tmp)->len))
			lem_error(ALLOC_ERR, frame);
			ft_printf("len: %d\n", (*tmp)->len); // DEL
			print_links((*tmp)->start);	// DEL
		tmp = &(*tmp)->next;
		links = next;
	}
}
