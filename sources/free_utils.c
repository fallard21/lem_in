/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 18:49:46 by user              #+#    #+#             */
/*   Updated: 2020/10/13 21:47:26 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lem_in.h"

void		lem_error(char *str, t_frame *stor)
{
	if (stor)
		lem_free(stor);
	ft_putendl_fd(str, 2);
	exit(EXIT_FAILURE);
}

void		free_map(t_room *room)
{
	t_room		*next;

	while (room)
	{
		next = room->next;
		ft_memdel((void**)&room->name);
		if (room->links)
			free_link(&room->links);
		if (room->input)
			free_link(&room->input);
		if (room->output)
			free_link(&room->output);
		ft_memdel((void**)&room);
		room = next;
	}
}

void		free_input(t_input *input)
{
	t_input		*tmp;

	if (!input)
		return ;
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
	ft_memdel((void**)&stor);
}
