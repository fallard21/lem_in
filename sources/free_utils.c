/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 18:49:46 by user              #+#    #+#             */
/*   Updated: 2020/10/09 14:38:56 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lem_parser.h"

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

void		free_paths(t_path *paths)
{
	t_link		*lev1;
	t_path		*path_copy;
	t_link		*lev1_copy;

	if (!paths)
		lem_error(MEM_FREE_ERR, NULL);
	while (paths)
	{
		path_copy = paths;
		lev1 = path_copy->start;
		while (lev1)
		{
			lev1_copy = lev1;
			lev1 = lev1->next;
			free(lev1_copy);
		}
		paths = paths->next;
		free(path_copy);
	}
}

void		del_links_list(t_link *link)
{
	t_link	*tmp;

	while (link)
	{
		tmp = link;
		link = link->next;
		free(link);
	}
}

void		del_room(t_room **room)
{
	t_link		*tmp_link;

	if (!(*room))
		lem_error(MEM_FREE_ERR, NULL);
	if ((*room)->links)
	free((*room)->name);
	(*room)->next = NULL;
	(*room)->prev = NULL;
	while((*room)->links)
	{
		tmp_link = (*room)->links;
		(*room)->links = (*room)->links->next;
		free(tmp_link);
	}
	(*room)->links = NULL;
	(*room)->input = NULL;
	(*room)->output = NULL;
	free(*room);
}

void		free_map(t_room *room)
{
	t_room		*tmp_room;
	t_link		*tmp_link;

	// printf("{ 3.1 }\n");

	// t_room	*pr = room;
	// while (pr)
	// {
	// 	printf("name = %s\t suur =%d\n", pr->name, pr->suur_type);
	// 	pr = pr->next;
	// }
	
	if (!room)
		lem_error(MEM_FREE_ERR, NULL);
	while (room)
	{
		// printf("in free | room->name = %s\t suur =%d\n", room->name, room->suur_type);
		// if (room->suur_type == IN || room->suur_type == 0)
		free(room->name);
		tmp_room = room;
		if (room->links)
			del_links_list(room->links);
		if (room->input)
			del_links_list(room->input);
		if (room->output)
			del_links_list(room->output);
		// while (room->links)
		// {
		// 	tmp_link = room->links;
		// 	room->links = room->links->next;
		// 	free(tmp_link);
		// 	// printf("{ 3.2 }\n");
		// }
		// printf("{ 3.3 }\n");
		room = room->next;
		free(tmp_room);
	}
	// printf("{ 3.10 }\n");
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
	stor->map_copy = NULL;
	stor->paths = NULL;
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
	// printf("{ 1 }\n");
	if (stor->input)
		free_input(stor->input);
	// printf("{ 2 }\n");
	if (stor->map)
		free_map(stor->map);
	// printf("{ 3 }\n");
	if (stor->paths)
		free_paths(stor->paths);
	// printf("{ 4 }\n");
	free_stor(stor);
	// printf("{ 5 }\n");
}
