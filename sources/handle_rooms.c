/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_rooms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 23:58:45 by user              #+#    #+#             */
/*   Updated: 2020/10/19 16:21:46 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lem_in.h"

static int		is_room_duplicates(t_room *room, t_room *new_room)
{
	if (!ft_strcmp(new_room->name, room->name) ||
		(new_room->coord[0] == room->coord[0] &&
		new_room->coord[1] == room->coord[1]))
		return (1);
	return (0);
}

static void		get_start_end_room(t_frame *stor, t_room *room)
{
	if (stor->cmd == START_SIG)
	{
		stor->start = room;
		room->ants = stor->num_ants;
		room->level = 0;
		room->vertex_size = 0;
		stor->cmd = NO_SIG;
	}
	if (stor->cmd == END_SIG)
	{
		stor->end = room;
		room->level = INT_MAX;
		stor->cmd = NO_SIG;
	}
}

static void		set_room_params(t_room *room, char **split)
{
	room->coord[0] = ft_atoi(split[1]);
	room->coord[1] = ft_atoi(split[2]);
	room->ants = 0;
	room->ant_name = 0;
	room->level = -1;
	room->num_links = 0;
	room->suur_type = 0;
	room->vertex_size = INT_MAX;
	room->next = NULL;
	room->prev = NULL;
	room->links = NULL;
	room->input = NULL;
	room->output = NULL;
}

t_room			*create_room(t_frame *stor, char *line)
{
	t_room	*room;
	char	**split;

	if (!line || !(room = ft_calloc(1, sizeof(t_room))))
		lem_error(ROOM_ADD_ERR, stor);
	if (!(split = ft_strsplit(line, ' ')) ||
	!(room->name = ft_strdup(split[0])))
	{
		ft_free_splited(split);
		lem_error(ROOM_ADD_ERR, stor);
	}
	set_room_params(room, split);
	get_start_end_room(stor, room);
	ft_free_splited(split);
	stor->num_rooms++;
	return (room);
}

t_room			*add_room(t_room *room, t_room *new_room, t_frame *stor)
{
	t_room	*tmp;

	if (!new_room)
		lem_error(ROOM_ADD_ERR, stor);
	if (!room)
		return (new_room);
	tmp = room;
	while (tmp)
	{
		if (is_room_duplicates(tmp, new_room))
		{
			del_room(&new_room);
			lem_error(ROOM_DUPL_ERR, stor);
		}
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	tmp->next = new_room;
	return (room);
}
