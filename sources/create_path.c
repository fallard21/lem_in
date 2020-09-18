/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 18:38:39 by user              #+#    #+#             */
/*   Updated: 2020/09/15 15:26:13 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lem_parser.h"

t_path		*create_path_node(t_frame *stor)
{
	t_path		*path;

	if (!(path = ft_calloc(1, sizeof(t_path))))
		lem_error(PATH_ERR, stor);
	path->start = create_link(stor->start, stor);
	path->end = NULL;
	path->next = NULL;
	path->on_work = 0;
	path->len = 0;
	path->ants_togo = 0;
	path->ants_pass = 0;
	return (path);
}

void		add_path(t_path *path, t_frame *stor)
{
	t_path		*cur;
	t_path		*prev;

	if (!path || !stor)
		lem_error(PATH_ERR, stor);
	cur = stor->paths;
	prev = NULL;
	if (cur)
	{
		while (cur && path->len > cur->len)
		{
			prev = cur;
			cur = cur->next;
		}
		if (!prev)
			stor->paths = path;
		else
			prev->next = path;
		path->next = cur;
	}
	else
		stor->paths = path;
}

/*
**	Path->len var include only 'mid' level-rooms and exclude start & end rooms
**	Path->end is the last 'mid' room of the path
**	(in path contained only 2 room: start & end - path->end = end)
*/

void		construct_path(t_path *path, t_link *lev1, t_frame *stor)
{
	t_link		*deep_link;
	t_link		*path_link;


	path_link = path->start;
	path_link->next = create_link(lev1->room, stor);
	path_link->next->prev = path_link;
	path_link = path_link->next;
	deep_link = path_link->room->links->next;
	while (deep_link && deep_link->room->level != INT_MAX)
	{
		path_link->next = create_link(deep_link->room, stor);
		path->len++;
		path_link->next->prev = path_link;
		path_link = path_link->next;
		deep_link = deep_link->room->links->next;
	}
	if (deep_link)
		path_link->next = create_link(deep_link->room, stor);
	path_link->next ? path_link->next->prev = path_link : NULL;
	path->end = path_link;
	path->len++;
}

t_path		*create_paths(t_frame *stor)
{
	t_path		*path;
	t_link		*lev1;
	int			paths_ct;

	paths_ct = -1;
	path = NULL;
	if (!stor)
		lem_error(PATH_ERR, NULL);
	set_levels(stor);		// tmp func to set bfs levels	**** DELETE
	lev1 = stor->start->links;
	while (lev1 && ++paths_ct < stor->start->num_links)
	{
		path = create_path_node(stor);
		construct_path(path, lev1, stor);
		add_path(path, stor);
		lev1 = lev1->next;
	}
	if (!path)
		lem_error(NO_PATHS_ERR, stor);
	return (path);
}
