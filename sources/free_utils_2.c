/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 18:31:01 by user              #+#    #+#             */
/*   Updated: 2020/10/12 18:31:35 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lem_in.h"

int		free_link(t_link **link)
{
	t_link	*next;

	while (*link)
	{
		next = (*link)->next;
		free(*link);
		*link = next;
	}
	return (1);
}

t_find	*free_prev_list(t_find **head)
{
	t_find	*next;

	while (*head)
	{
		next = (*head)->next;
		free(*head);
		*head = next;
	}
	return (NULL);
}

void	free_flow(t_flow **flow)
{
	if (*flow)
	{
		ft_memdel((void**)&(*flow)->ants);
		ft_memdel((void**)&(*flow)->path);
		ft_memdel((void**)&(*flow)->diff);
	}
	ft_memdel((void**)&(*flow));
}

void		del_room(t_room **room)
{
	if (!(*room))
		lem_error(MEM_FREE_ERR, NULL);
	if ((*room)->links)
	free((*room)->name);
	(*room)->next = NULL;
	(*room)->prev = NULL;
	if ((*room)->links)
		free_link(&(*room)->links);
	(*room)->links = NULL;
	(*room)->input = NULL;
	(*room)->output = NULL;
	free(*room);
}

void		free_paths(t_path *paths)
{
	t_link		*lev1;
	t_path		*path_copy;

	if (!paths)
		lem_error(MEM_FREE_ERR, NULL);
	while (paths)
	{
		path_copy = paths;
		lev1 = path_copy->start;
		free_link(&lev1);
		paths = paths->next;
		free(path_copy);
	}
}
