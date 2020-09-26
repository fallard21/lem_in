/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 03:35:44 by fallard           #+#    #+#             */
/*   Updated: 2020/09/26 18:51:56 by user             ###   ########.fr       */
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
				ft_printf("{2}%s{1}(%d){0}", tmp_1->room->name, tmp_1->room->level);
			else
				ft_printf("{2}%s{1}(%d){0} -> ", tmp_1->room->name, tmp_1->room->level);
			tmp_1 = tmp_1->next;
		}
		tmp = tmp->next;
		ft_printf("\n");
	}
	ft_printf("{4}----------------------- END -----------------------{0}\n\n");
}

void	print_patchs(t_room *start)
{
	t_link *link;
	t_link	*tmp;
	t_room	*room;
	int i = 0;
	tmp = start->links;
	while (tmp)
	{
		(i++ % 2) ? ft_printf("{3}") : ft_printf("{2}");
		ft_printf("%s -> %s -> ", start->name, tmp->room->name);
		room = tmp->room;
		while (room->level != INT_MAX)
		{
			link = room->links;
			while (link)
			{
				if (link->room->level > room->level)
					break;
				link = link->next;
			}
			ft_printf("%s -> ", link->room->name);
			room = link->room;
		}
		tmp = tmp->next;
		ft_printf("{0}\n\n");
	}
}

// void	print_suurb(t_room *start)
// {
// 	t_link *tmp;

// 	while (start)
// 	{
// 		if (ft_strcmp(start->name, "0") == 0)
// 			ft_printf("(%2d){1}[%2s] : {0}", start->vertex_size, start->name);
// 		else if (ft_strcmp(start->name, "99") == 0)
// 			ft_printf("(%2d){1}[%2s] : {0}", start->vertex_size, start->name);
// 		else
// 		{
// 			if (start->in)
// 				ft_printf("(%2d){3}[%2s] : {0}", start->vertex_size, start->name);
// 			else
// 				ft_printf("(%2d){2}[%2s]': {0}", start->vertex_size, start->name);
// 		}
// 		tmp = start->links;
// 		while (tmp)
// 		{
// 			if (tmp->room->in)
// 				ft_printf("{3}[%s]{0}(%d) -> ", tmp->room->name, tmp->edge_size);
// 			else
// 				ft_printf("{2}[%s']{0}(%d) -> ", tmp->room->name, tmp->edge_size);
// 			tmp = tmp->next;
// 		}
// 		ft_printf("\n");
// 		start = start->next;
// 	}
// }