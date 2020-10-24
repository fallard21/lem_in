/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 01:52:24 by user              #+#    #+#             */
/*   Updated: 2020/10/24 18:07:03 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lem_in.h"

void		set_ants_on_paths(t_frame *stor)
{
	t_path		*tmp;
	int			ants_ct;

	ants_ct = stor->start->ants;
	while (ants_ct != 0)
	{
		tmp = stor->paths;
		while (tmp)
		{
			if (!tmp->next)
				break ;
			if (tmp->next->len + tmp->next->ants_togo >
					tmp->len + tmp->ants_togo)
				break ;
			tmp = tmp->next;
		}
		tmp->ants_togo++;
		ants_ct--;
	}
}

int			move_through_path(t_path *path, t_frame *stor)
{
	t_link		*link;

	link = path->end;
	if (link->room->level == INT_MAX || !path->len)
	{
		!path->len ? move_simple_path(path, stor) :
		move_from_start(path, stor);
		return (1);
	}
	while (link)
	{
		if (link->room->level == 0 && link->room->ants)
			move_from_start(path, stor);
		else if (link->room->ants)
		{
			if (link->next->room->level == INT_MAX)
				move_to_end(link, path, stor);
			else if (!link->next->room->ants)
				move_by_mid(link, stor);
		}
		link = link->prev;
	}
	return (1);
}

void		handle_ants_move(t_frame *stor)
{
	t_path		*tmp;
	int			is_used;

	tmp = stor->paths;
	set_ants_on_paths(stor);
	if (stor->stat.key_stat)
		put_stat(stor);
	while (stor->end->ants < stor->num_ants)
	{
		is_used = 0;
		if (tmp->ants_togo != 0 && tmp->ants_pass != tmp->ants_togo)
			is_used = move_through_path(tmp, stor);
		if (tmp->next)
			tmp = tmp->next;
		else
		{
			if (is_used == 0 && tmp->ants_togo != 0)
				move_through_path(tmp, stor);
			tmp = stor->paths;
			if (stor->stat.key_move)
				ft_printf("\n");
		}
	}
}
