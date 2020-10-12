/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallard <fallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 19:43:44 by fallard           #+#    #+#             */
/*   Updated: 2020/10/12 21:23:03 by fallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lem_in.h"

void	ft_parse_flags(int *key_p, char *av)
{
	if (ft_strcmp(av, "-p") == 0)
		*key_p = 1;
	else
	{
		write(2, "Invalid key: '", 15);
		write(2, av, ft_strlen(av));
		write(2, "'.\nUsage:\n", 11);
		write(2, "\t./lem_in < map\n\t./lem_in -p < map\n", 36);
		write(2, "\t-p\tprint all path's\n", 22);
		exit(1);
	}
}

void	ft_print_path(t_path *p)
{
	t_link	*tmp;
	int		i;

	i = 0;
	while (p)
	{
		ft_printf("%d) Path size: %d\n\t", i + 1, p->len);
		tmp = p->start;
		while (tmp)
		{
			if (!tmp->next)
				ft_printf("%s", tmp->room->name);
			else
				ft_printf("%s -> ", tmp->room->name);
			tmp = tmp->next;
		}
		p = p->next;
		i++;
		ft_printf("\n");
	}
	ft_printf("\n");
}

void	ft_print_color_path(t_path *p)
{
	t_link	*tmp;
	int		i;

	i = 0;
	while (p)
	{
		ft_printf("{3}%d) Path size: %d{0}\n\t", i + 1, p->len);
		tmp = p->start;
		while (tmp)
		{
			if (!tmp->next)
				ft_printf("{2}%s{0}", tmp->room->name);
			else
				ft_printf("{2}%s -> {0}", tmp->room->name);
			tmp = tmp->next;
		}
		p = p->next;
		i++;
		ft_printf("\n");
	}
	ft_printf("\n");
}
