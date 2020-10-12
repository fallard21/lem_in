/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 20:36:04 by user              #+#    #+#             */
/*   Updated: 2020/10/12 20:37:15 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "struct.h"

void		input_print_and_free(t_frame *stor)
{
	t_input		*input;

	input = stor->input;
	while (input)
	{
		ft_putendl_fd(input->line, 1);
		input = input->next;
	}
	ft_putchar_fd('\n', 1);
	free_input(stor->input);
	stor->input = NULL;
}

int			is_valid_map(t_frame *stor)
{
	if (!stor)
		return (0);
	if (!stor->start || !stor->end || stor->start->num_links == 0 ||
	stor->end->num_links == 0 || !stor->map || stor->num_rooms == 1 ||
	stor->num_ants == 0)
		return (0);
	return (1);
}
