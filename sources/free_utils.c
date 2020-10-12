/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 18:49:46 by user              #+#    #+#             */
/*   Updated: 2020/10/12 18:29:46 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lem_in.h"

void		lem_error(char *str, t_frame *stor)
{
	if (stor)
		lem_free(stor);
	if (!ft_strcmp(str, NOT_ENOUGH_ERR))
		ft_putendl_fd(str, 2);
	else if (errno == 0)
		perror(str);
	else
		ft_putendl_fd(str, 2);
	exit(EXIT_FAILURE);
}

void		free_map(t_room *room)
{
	t_room		*tmp_room;

	if (!room)
		lem_error(MEM_FREE_ERR, NULL);
	while (room)
	{
		free(room->name);
		tmp_room = room;
		free_link(&room->links);
		free_link(&room->input);
		free_link(&room->output);
		room = room->next;
		free(tmp_room);
	}
	ft_memdel((void*)room);
}

void		free_stor(t_frame *stor)
{
	if (!stor)
		lem_error(MEM_FREE_ERR, NULL);
	free(stor->start);
	free(stor->end);
	stor->input = NULL;
	stor->map = NULL;
	stor->paths = NULL;
	stor->find_way = NULL;
	stor->flow = NULL;
	free(stor);
}

void		free_input(t_input *input)
{
	t_input		*tmp;

	if (!input)
		lem_error(MEM_FREE_ERR, NULL);
	while (input)
	{
		free(input->line);
		tmp = input;
		input = input->next;
		free(tmp);
	}
	ft_memdel((void*)input);
}

void		lem_free(t_frame *stor)
{
	if (!stor)
		lem_error(MEM_FREE_ERR, NULL);
	if (stor->input)
		free_input(stor->input);
	if (stor->map)
		free_map(stor->map);
	if (stor->paths)
		free_paths(stor->paths);
	if (stor->flow)
		free_flow(&stor->flow);
	if (stor->find_way)
		free_prev_list(&stor->find_way);
	free_stor(stor);
}
