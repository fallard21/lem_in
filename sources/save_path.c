/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 08:44:09 by fallard           #+#    #+#             */
/*   Updated: 2020/10/12 16:27:23 by user             ###   ########.fr       */
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

void	get_all_paths(t_frame *frame)
{
	t_path	**tmp;
	t_link	*links;
	t_link	*next;

	tmp = &frame->paths;
	links = frame->end->output;
	while (links)
	{
		next = links->next;
		if (!(*tmp = ft_calloc(1, sizeof(t_path))))
			lem_error(ALLOC_ERR, frame);
		if (!(links->next = ft_calloc(1, sizeof(t_link))))
			lem_error(ALLOC_ERR, frame);
		links->next->room = frame->end;
		(*tmp)->end = links;
		(*tmp)->start = links;
		if (init_link_list(links, &(*tmp)->start, &(*tmp)->len))
			lem_error(ALLOC_ERR, frame);
		tmp = &(*tmp)->next;
		links = next;
	}
	frame->paths = sort_path(frame->paths);
		//ft_print_path(frame->paths); ft_printf("\n");	// DELETE
}
