/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 18:06:30 by user              #+#    #+#             */
/*   Updated: 2020/10/15 14:43:30 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lem_in.h"

int			main(int ac, char **av)
{
	t_frame	*stor;
	int		key_p;

	key_p = 0;
	if (ac > 1)
		ft_parse_flags(&key_p, ac, av[1]);
	stor = create_map();
	stor->key_p = key_p;
	set_direct_graph(stor);
	suurballe(stor);
	handle_ants_move(stor);
	if (stor->end->ants != stor->num_ants)
		lem_error(MOVE_RES_ERR, stor);
	lem_free(stor);
	return (0);
}
