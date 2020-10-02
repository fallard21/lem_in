/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 18:06:30 by user              #+#    #+#             */
/*   Updated: 2020/10/02 16:30:27 by fallard          ###   ########.fr       */
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
