/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 23:29:39 by user              #+#    #+#             */
/*   Updated: 2020/10/01 23:29:43 by user             ###   ########.fr       */
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
		//path = create_paths(stor);
		//handle_ants_move(stor);

	}
	// else
	// 	lem_error(SMTH_HERE)
	//lem_free(stor);
	
	return (0);
}
