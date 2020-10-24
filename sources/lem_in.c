/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 18:06:30 by user              #+#    #+#             */
/*   Updated: 2020/10/24 16:15:13 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lem_in.h"

int	main(int ac, char **av)
{
	t_frame	*stor;
	t_stat	stat;

	ft_memset(&stat, 0, sizeof(t_stat));
	ft_parse_flags(&stat, ac, av);
	// ft_printf("map: %d\n", stat.key_map);
	// ft_printf("move: %d\n", stat.key_move);
	// ft_printf("stat: %d\n", stat.key_stat);
	// ft_printf("all: %d\n", stat.key_all);
	if (!(stor = create_map()))
		lem_error(ALLOC_ERR, stor);
	stor->stat = stat;
	set_direct_graph(stor);
	suurballe(stor);
	handle_ants_move(stor);
	lem_free(stor);
	return (0);
}
