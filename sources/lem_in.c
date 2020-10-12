/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 18:06:30 by user              #+#    #+#             */
/*   Updated: 2020/10/12 21:06:33 by fallard          ###   ########.fr       */
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
	int			key_p;

	key_p = 0;
	if (ac == 2)
		ft_parse_flags(&key_p, av[1]);
	stor = create_map();
	stor->key_p = key_p;
	set_direct_graph(stor);
	suurballe(stor);
	handle_ants_move(stor);
	// else
	// 	lem_error(SMTH_HERE)
	//lem_free(stor);
	return (0);
}
