/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 18:06:30 by user              #+#    #+#             */
/*   Updated: 2020/10/27 22:08:06 by user             ###   ########.fr       */
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
	if (!(stor = create_map()))
		lem_error(ALLOC_ERR, stor);
	stor->stat = stat;
	input_print_and_free(stor);
	set_direct_graph(stor);
	suurballe(stor);
	handle_ants_move(stor);
	ft_printf("\n");
	lem_free(stor);
	return (0);
}
