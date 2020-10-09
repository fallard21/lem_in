/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 14:17:39 by user              #+#    #+#             */
/*   Updated: 2020/10/09 17:45:50 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lem_parser.h"

/*
**	TODO:
**		1. Написать буфферизированный вывод?
**		
**		
**
*/

int			main(int ac, char **av)
{
	t_frame		*stor;
	t_path		*path;

	// ft_memset(&stor, 0, sizeof(stor));
	errno = 0;
	//  if (ac >= 2) 	// Here is to handle possible bonus-flags
	//  {				// --help, --verbose, --debug, etc
	//  }
	 if (ac == 1)
	{		
		stor = create_map();
		set_direct_graph(stor);
		suurballe(stor);


		// ft_printf("\n"); print_patchs(stor->start);
		// path = create_paths(stor);
		// print_path_list(stor);

		handle_ants_move(stor);

		// t_link *l = stor->paths->start;
		// while(l)
		// {
		// 	printf("room = %s\t next = %s\t prev = %s\n",
		// 	l->room->name, l->next ? l->next->room->name : NULL,
		// 	l->prev ? l->prev->room->name : NULL);
		// 	l = l->next;
		// }
	}
	// else
	// 	lem_error(SMTH_HERE)
	lem_free(stor);
	
	return (0);
}
