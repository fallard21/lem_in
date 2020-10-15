/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 18:06:30 by user              #+#    #+#             */
/*   Updated: 2020/10/15 17:21:09 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lem_in.h"

int	main(int ac, char **av)
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
	lem_free(stor);
	return (0);
}
