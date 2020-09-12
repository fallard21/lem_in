/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 18:49:46 by user              #+#    #+#             */
/*   Updated: 2020/09/11 20:54:33 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lem_parser.h"

void		lem_error(char *str, t_frame *stor)
{
	lem_free(stor);
	if (!ft_strcmp(str, NOT_ENOUGH_ERR))
		ft_putendl_fd(str, 0);
	else if (errno == 0)
		perror(str);
	else
		ft_putendl_fd(str, 2);
	exit(EXIT_FAILURE);
}

void		free_map(t_room *room)
{
	t_room		*tmp_room;
	t_link		*tmp_link;

	while (room)
	{
		free(room->name);
		tmp_room = room;
		while (room->links)
		{
			tmp_link = room->links;
			room->links = room->links->next;
			free(tmp_link);
		}
		room = room->next;
		free(tmp_room);
	}
	ft_memdel((void*)room);
}

void		free_stor(t_frame *stor)
{
	free(stor->start);
	free(stor->end);
	stor->input = NULL;
	stor->map = NULL;
	stor->map_copy = NULL;
	free(stor);
}

void		free_input(t_input *input)
{
	t_input		*tmp;

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
	if (stor)
	{
		if (stor->input)
			free_input(stor->input);
		if (stor->map)
			free_map(stor->map_copy);
		free_stor(stor);
	}
}
