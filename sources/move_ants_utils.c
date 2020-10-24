/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 20:01:42 by user              #+#    #+#             */
/*   Updated: 2020/10/24 15:42:10 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lem_in.h"

void		print_ant_action(int ant_name, char *room_name)
{
	return ;
	ft_printf("L%d-%s ", ant_name, room_name);
}

/*
**	Simple path containing only 2 room: start & end
*/

void		move_simple_path(t_path *path, t_frame *stor)
{
	print_ant_action(stor->ant_name, stor->end->name);
	stor->ant_name++;
	path->ants_pass++;
	stor->end->ants++;
	path->on_work++;
}

void		move_from_start(t_path *path, t_frame *stor)
{
	t_link		*link;

	link = path->start;
	if (!link->next->room->ants && path->on_work < path->ants_togo)
	{
		link->next->room->ants = 1;
		link->next->room->ant_name = stor->ant_name;
		print_ant_action(stor->ant_name, link->next->room->name);
		stor->ant_name++;
		link->room->ants--;
		path->on_work++;
	}
}

void		move_by_mid(t_link *link)
{
	link->next->room->ants = 1;
	link->next->room->ant_name = link->room->ant_name;
	print_ant_action(link->room->ant_name, link->next->room->name);
	link->room->ants = 0;
	link->room->ant_name = 0;
}

void		move_to_end(t_link *link, t_path *path, t_frame *stor)
{
	print_ant_action(link->room->ant_name, link->next->room->name);
	link->room->ants = 0;
	link->room->ant_name = 0;
	path->ants_pass++;
	stor->end->ants++;
}
