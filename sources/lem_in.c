/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 18:06:30 by user              #+#    #+#             */
/*   Updated: 2020/10/12 16:27:10 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lem_in.h"

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

	errno = 0;
	//  if (ac >= 2) 	// Here is to handle possible bonus-flags
	//  {				// --help, --verbose, --debug, etc
	//  }
	 if (ac == 1)
	{
		
		stor = create_map();
		set_direct_graph(stor);

		suurballe(stor);
		handle_ants_move(stor);
	}
	// else
	// 	lem_error(SMTH_HERE)
	//lem_free(stor);
	
	return (0);
}
