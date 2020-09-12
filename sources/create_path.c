/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 18:38:39 by user              #+#    #+#             */
/*   Updated: 2020/09/11 20:54:24 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lem_parser.h"

void		set_levels(t_frame *stor)	// tmp funcs to set bfs levels	**** DELETE
{
	t_room		*start;
	t_link		*r_link;
	int 		i;

	start = stor->start;
	while (start->links)
	{
		i = 1;
		r_link = start->links;
		printf("in fst loop r_copy = %s\n", r_link->room->name);
		while (r_link && r_link->room->level != INT_MAX)
		{
			r_link->room->level = i;
			i++;
			r_link = r_link->room->links;
		}
		start->links = start->links ? start->links->next : NULL;
	}
	printf("\n***** IN SET LEVELS*****\n");
	print_room_list(stor, stor->map);
}

t_path		*create_path(t_frame *stor)
{
	set_levels(stor);		// tmp funcs to set bfs levels	**** DELETE

	t_path		*path;
	path = NULL;
	return (path);
}
