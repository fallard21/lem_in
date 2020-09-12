/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 17:48:37 by fallard           #+#    #+#             */
/*   Updated: 2020/09/12 00:36:42 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lem_parser.h"

void	ft_exit(char *error)
{
	perror(error);
	exit(EXIT_FAILURE);
}

void	free_link(t_link **link)
{
	t_link	*next;

	while (*link)
	{
		next = (*link)->next;
		free((*link)->room->name);
		free((*link)->room);
		free(*link);
		*link = next;
	}
}

void	free_room(t_room **room)
{
	t_room	*next;

	while (*room)
	{
		next = (*room)->next;
		free((*room)->name);
		free(*room);
		*room = next;
	}
}
