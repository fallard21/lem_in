/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 03:35:44 by fallard           #+#    #+#             */
/*   Updated: 2020/09/12 00:46:59 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lem_parser.h"

void	print_rooms(t_room *room)
{
	t_room *tmp;

	tmp = room;
	while (tmp)
	{
		ft_printf("{3}[%2s]{0}: ", tmp->name);
		print_links(tmp->links);
		tmp = tmp->next;
	}
	ft_printf("\n\n");
}

void print_links(t_link *links)
{
	t_link *tmp;

	tmp = links;
	while (tmp)
	{
		if (!tmp->next)
			ft_printf("{2}%s{0}", tmp->room->name);
		else
			ft_printf("{2}%s{0} -> ", tmp->room->name);
		tmp = tmp->next;
	}
	ft_printf("\n");
}

void	print_all_info(t_room *room)
{
	t_room *tmp;
	t_link *tmp_1;

	tmp = room;
	while (tmp)
	{
		tmp_1 = tmp->links;
		ft_printf("{3}[%2s]{1}(%10d){0}  ({6}in: %d, out: %d{0}): ", tmp->name, tmp->level, tmp->input_links, tmp->output_links);
		while (tmp_1)
		{
			if (!tmp_1->next)
				ft_printf("{2}%s{1}(%10d){0}", tmp_1->room->name, tmp_1->room->level);
			else
				ft_printf("{2}%s{1}(%10d){0} -> ", tmp_1->room->name, tmp_1->room->level);
			tmp_1 = tmp_1->next;
		}
		tmp = tmp->next;
		ft_printf("\n");
	}
	ft_printf("{4}----------------------- END -----------------------{0}\n\n");
}
